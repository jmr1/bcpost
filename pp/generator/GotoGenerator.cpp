//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "GotoGenerator.h"

#include <iomanip>
#include <string>

//#define BOOST_SPIRIT_USE_PHOENIX_V3

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/phoenix/bind.hpp>
//#include <boost/bind.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp> // construct
#include <boost/spirit/include/phoenix_operator.hpp>
//#include <boost/spirit/include/qi_symbols.hpp>
//#include <boost/spirit/include/support_multi_pass.hpp>
//#include <boost/phoenix/object/dynamic_cast.hpp>
//#include <boost/phoenix/operator/self.hpp>

//#include "MessageTextImpl.h"

#include "interface/CLData.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

// using word_symbols = qi::symbols<char, std::string>;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::FloatValue,
    (boost::optional<char>, sign)
    (boost::optional<std::string>, value)
    (boost::optional<char>, dot)
    (boost::optional<std::string>, value2)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Goto,
    (pp::interface::FloatValue, x)
    (pp::interface::FloatValue, y)
    (pp::interface::FloatValue, z)
    (boost::optional<pp::interface::FloatValue>, i)
    (boost::optional<pp::interface::FloatValue>, j)
    (boost::optional<pp::interface::FloatValue>, k)
)

// clang-format on

namespace pp {
namespace fanuc {

class float_rounder
{
public:
    float_rounder(uint32_t precision)
        : precision(precision)
    {
    }

    void exec(std::string& value) const
    {
        std::string tmp = value;
        if (tmp.size() > precision)
            tmp = tmp.substr(0, precision);
        auto ret = std::find_if(tmp.rbegin(), tmp.rend(), [](const auto& v) { return v != '0' ? true : false; });
        if (ret != tmp.rbegin())
            tmp.erase(ret.base(), tmp.end());
        value = tmp;
    }

private:
    const uint32_t precision;
};

template <typename Iterator>
class float_value_grammar : public karma::grammar<Iterator, interface::FloatValue()>
{
public:
    float_value_grammar(uint32_t precision)
        : float_value_grammar::base_type(float_value_attribute)
        , fr(precision)
    {
        float_value_attribute %= -karma::char_
                                 << -karma::string << -karma::char_
                                 << -karma::string[phx::bind(&float_rounder::exec, phx::cref(fr), karma::_1)];
    }

private:
    float_rounder                                  fr;
    karma::rule<Iterator, interface::FloatValue()> float_value_attribute;
};

#ifdef THROW_WHEN_ERROR

struct float_value_exception : std::runtime_error
{
    float_value_exception(const std::string& message)
        : std::runtime_error(message.c_str())
    {
    }
};

inline bool verify_throw(const interface::FloatValue& value)
{
    if (!value.sign && !value.value && !value.dot && !value.value2)
        throw float_value_exception("Brak wartości.");
    return true;
}

template <typename Iterator>
class goto_grammar : public karma::grammar<Iterator, interface::Goto()>
{
public:
    goto_grammar(uint32_t precision)
        : goto_grammar::base_type(goto_attribute)
        , attr_value_float_throw(precision)
    {
        // G94 G90 X-24.585 Y-115. Z100.
        attr_value_float %= attr_value_float_throw[karma::_pass = phx::bind(&verify_throw, karma::_1)];
        goto_attribute %= karma::lit("G94")
                          << ' ' << karma::lit("G90") << ' ' << karma::lit("X") << attr_value_float << ' '
                          << karma::lit("Y") << attr_value_float << ' ' << karma::lit("Z") << attr_value_float;
    }

private:
    float_value_grammar<Iterator>                  attr_value_float_throw;
    karma::rule<Iterator, interface::FloatValue()> attr_value_float;
    karma::rule<Iterator, interface::Goto()>       goto_attribute;
};

#else

inline bool verify(const interface::FloatValue& value)
{
    if (!value.sign && !value.value && !value.dot && !value.value2)
        return false;
    if (!value.dot && value.value2)
        return false;
    return true;
}

template <typename Iterator>
class goto_grammar : public karma::grammar<Iterator, interface::Goto()>
{
public:
    goto_grammar(uint32_t precision)
        : goto_grammar::base_type(goto_attribute)
        , attr_value_float_check(precision)
    {
        // G94 G90 X-24.585 Y-115. Z100.
        attr_value_float %=
            (attr_value_float_check[karma::_pass = phx::bind(&verify, karma::_1)] | karma::lit("<error>"));
        goto_attribute %= karma::lit("G94")
                          << ' ' << karma::lit("G90") << ' ' << karma::lit("X") << attr_value_float << ' '
                          << karma::lit("Y") << attr_value_float << ' ' << karma::lit("Z") << attr_value_float;
    }

private:
    float_value_grammar<Iterator>                  attr_value_float_check;
    karma::rule<Iterator, interface::FloatValue()> attr_value_float;
    karma::rule<Iterator, interface::Goto()>       goto_attribute;
};

#endif

template <typename Iterator>
bool generate_goto(Iterator& sink, const interface::Goto& v, uint32_t precision)
{
    goto_grammar<Iterator> goto_g(precision);
    return karma::generate(sink, goto_g, v);
}

std::string generate_goto(const interface::Goto& value, uint32_t precision)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_goto(sink, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp
