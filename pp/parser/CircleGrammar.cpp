//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "CircleGrammar.h"

#include <iomanip>

#include <boost/config/warning_disable.hpp>
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

circle_grammar::circle_grammar()
    : circle_grammar::base_type(circle_attribute)
{
    // CIRCLE/206.4575,-30.0000,0.0000,0.0000000,0.0000000,1.0000000,30.0000,0.0600,0.5000,30.0000,0.0000
    circle_attribute = qi::lit("CIRCLE") > qi::lit("/") > attr_value_float > (qi::lit(",") > attr_value_float) >
                       (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                       (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                       (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                       (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                       (qi::lit(",") > attr_value_float) > -(qi::lit(",") > qi::uint_);

    BOOST_SPIRIT_DEBUG_NODES((circle_attribute));
}

} // namespace cldata
} // namespace pp
