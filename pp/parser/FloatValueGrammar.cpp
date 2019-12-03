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
