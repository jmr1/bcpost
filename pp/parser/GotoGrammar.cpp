//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "GotoGrammar.h"

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

goto_grammar::goto_grammar()
    : goto_grammar::base_type(goto_attribute)
{
    // GOTO/-24.5855,-115.0000,100.0000,0.0000000,0.0000000,1.0000000
    goto_attribute = qi::lit("GOTO") > qi::lit("/") > attr_value_float > (qi::lit(",") > attr_value_float) >
                     (qi::lit(",") > attr_value_float) > -(qi::lit(",") > attr_value_float) >
                     -(qi::lit(",") > attr_value_float) > -(qi::lit(",") > attr_value_float);

    BOOST_SPIRIT_DEBUG_NODES((goto_attribute));
}

} // namespace cldata
} // namespace pp
