//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "GotoGenerator.h"

#include <iomanip>
#include <string>

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/phoenix/bind.hpp>
//#include <boost/bind.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp> // construct
#include <boost/spirit/include/phoenix_operator.hpp>
//#include <boost/phoenix/object/dynamic_cast.hpp>
//#include <boost/phoenix/operator/self.hpp>

//#include "MessageTextImpl.h"

#include "FloatValueGenerator.h"
#include "interface/CLData.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

// clang-format off

// must be in global namespace

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

#ifdef THROW_WHEN_ERROR

template <typename Iterator>
class goto_grammar : public karma::grammar<Iterator, interface::Goto()>
{
public:
    goto_grammar(uint32_t& line, uint32_t step, uint32_t precision)
        : goto_grammar::base_type(goto_attribute)
        , attr_value_float_throw(precision)
    {
        // G94 G90 X-24.585 Y-115. Z100.
        attr_value_float %= attr_value_float_throw[karma::_pass = phx::bind(&verify_throw, karma::_1)];
        goto_attribute %= "N" << karma::lit(phx::ref(line) += step) << " G94 G90 X" << attr_value_float << " Y"
                              << attr_value_float << " Z" << attr_value_float;
    }

private:
    float_value_grammar<Iterator>                  attr_value_float_throw;
    karma::rule<Iterator, interface::FloatValue()> attr_value_float;
    karma::rule<Iterator, interface::Goto()>       goto_attribute;
};

#else

template <typename Iterator>
class goto_grammar : public karma::grammar<Iterator, interface::Goto()>
{
public:
    goto_grammar(uint32_t& line, uint32_t step, uint32_t precision)
        : goto_grammar::base_type(goto_attribute)
        , attr_value_float_check(precision)
    {
        // G94 G90 X-24.585 Y-115. Z100.
        attr_value_float %=
            (attr_value_float_check[karma::_pass = phx::bind(&verify, karma::_1)] | karma::lit("<error>"));
        goto_attribute = "N" << karma::lit(phx::ref(line) += step) << " G94 G90 X" << attr_value_float << " Y"
                             << attr_value_float << " Z" << attr_value_float;
    }

private:
    float_value_grammar<Iterator>                attr_value_float_check;
    karma::rule<Iterator, interface::FloatValue> attr_value_float;
    karma::rule<Iterator, interface::Goto()>     goto_attribute;
};

#endif

template <typename Iterator>
bool generate_goto(Iterator& sink, uint32_t& line, uint32_t step, const interface::Goto& v, uint32_t precision)
{
    goto_grammar<Iterator> goto_g(line, step, precision);
    return karma::generate(sink, goto_g, v);
}

std::string generate_goto(uint32_t& line, uint32_t step, const interface::Goto& value, uint32_t precision)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_goto(sink, line, step, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp
