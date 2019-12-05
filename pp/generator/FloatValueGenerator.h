//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include <iomanip>
#include <string>

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp> // construct
#include <boost/spirit/include/phoenix_operator.hpp>
//#include <boost/phoenix/object/dynamic_cast.hpp>
//#include <boost/phoenix/operator/self.hpp>

#include "interface/CLData.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::FloatValue,
    (boost::optional<char>, sign)
    (boost::optional<std::string>, value)
    (boost::optional<char>, dot)
    (boost::optional<std::string>, value2)
)

// clang-format on

namespace pp {
namespace fanuc {

class float_rounder
{
public:
    float_rounder(uint32_t precision);

    void exec(std::string& value) const;

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

bool verify_throw(const interface::FloatValue& value);

#else

bool verify(const interface::FloatValue& value);

#endif

template <typename Iterator>
bool generate_floatValue(Iterator& sink, const interface::FloatValue& value, uint32_t precision)
{
    float_value_grammar<Iterator> floatValue_g(precision);
    return karma::generate(sink, floatValue_g, value);
}

std::string generate_floatValue(const interface::FloatValue& value, uint32_t precision);

} // namespace fanuc
} // namespace pp
