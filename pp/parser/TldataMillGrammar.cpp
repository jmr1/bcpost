//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "TldataMillGrammar.h"

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

tldata_mill_grammar::tldata_mill_grammar()
    : tldata_mill_grammar::base_type(tldata_mill_attribute)
{
    // TLDATA/MILL,80.0000,0.0000,75.0000,0.0000,0.0000
    tldata_mill_attribute = &(qi::lit("TLDATA") >> qi::lit("/") >> qi::lit("MILL")) > qi::lit("TLDATA") > qi::lit("/") >
                            qi::lit("MILL") > (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                            (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                            (qi::lit(",") > attr_value_float) > -(qi::lit(",") > attr_value_float) >
                            -(qi::lit(",") > attr_value_float) > -(qi::lit(",") > attr_value_float) >
                            -(qi::lit(",") > attr_value_float) > -(qi::lit(",") > attr_value_float) > qi::eoi;
    BOOST_SPIRIT_DEBUG_NODES((tldata_mill_attribute));
}

} // namespace cldata
} // namespace pp
