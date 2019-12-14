//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "FloatValueGrammar.h"

#include <iomanip>

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp> // construct
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_symbols.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include "interface/CLData.h"

namespace qi      = boost::spirit::qi;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

namespace pp {
namespace interface {

std::string to_string(const FloatValue& value)
{
    std::string tmp;
    if (value.sign)
        tmp += *value.sign;
    if (value.value)
        tmp += *value.value;
    if (value.dot)
        tmp += *value.dot;
    if (value.value2)
        tmp += *value.value2;
    return tmp;
}

double to_double(const FloatValue& value)
{
    return atof(to_string(value).c_str());
}

FloatValue operator+(const FloatValue& lhs, const FloatValue& rhs)
{
    double dlhs = std::atof(to_string(lhs).c_str());
    double drhs = std::atof(to_string(rhs).c_str());

    std::string        data(std::to_string(dlhs + drhs));
    std::istringstream input(data);
    typedef boost::spirit::classic::position_iterator2<boost::spirit::istream_iterator> pos_iterator_type;
    pos_iterator_type position_begin(boost::spirit::istream_iterator{input >> std::noskipws}, {}), position_end;

    FloatValue                  fv_ret{};
    cldata::float_value_grammar fv;

    try
    {
        if (qi::phrase_parse(position_begin, position_end, fv, qi::blank, fv_ret))
        {
            const auto precision =
                std::max(lhs.value2 ? (*lhs.value2).size() : 0, rhs.value2 ? (*rhs.value2).size() : 0);
            if (fv_ret.value2)
                interface::float_rounder(precision).exec(*fv_ret.value2);
            return fv_ret;
        }
    }
    catch (const qi::expectation_failure<pos_iterator_type>& e)
    {
        return fv_ret;
    }
    catch (const std::exception& e)
    {
        return fv_ret;
    }

    return fv_ret;
}

} // namespace interface

namespace cldata {

float_value_grammar::float_value_grammar()
    : float_value_grammar::base_type(float_value_attribute)
{
    attr_value            = +qi::char_("0-9");
    attr_value2           = +qi::char_("0-9");
    float_value_attribute = (-qi::char_("-+") > attr_value > -qi::char_(".") > -attr_value2) |
                            (-qi::char_("-+") > -attr_value > qi::char_(".") > attr_value2);
    BOOST_SPIRIT_DEBUG_NODES((float_value_attribute));
}

} // namespace cldata
} // namespace pp
