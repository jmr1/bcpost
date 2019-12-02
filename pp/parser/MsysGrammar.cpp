//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "MsysGrammar.h"

#include <iomanip>

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

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

//#include "MessageTextImpl.h"

#include "interface/CLData.h"

namespace qi      = boost::spirit::qi;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Msys,
    (pp::interface::FloatValue, shift_x)
    (pp::interface::FloatValue, shift_y)
    (pp::interface::FloatValue, shift_z)
    (pp::interface::FloatValue, col1_x)
    (pp::interface::FloatValue, col1_y)
    (pp::interface::FloatValue, col1_z)
    (pp::interface::FloatValue, col2_x)
    (pp::interface::FloatValue, col2_y)
    (pp::interface::FloatValue, col2_z)
)

// clang-format on

namespace pp {
namespace cldata {

msys_grammar::msys_grammar()
    : msys_grammar::base_type(msys_attribute)
{
    // MSYS/0.0000,0.0000,180.0000,0.5000000,0.0000000,0.8660254,0.8660254,0.0000000,-0.5000000
    msys_attribute = qi::lit("MSYS") > qi::lit("/") > attr_value_float > (qi::lit(",") > attr_value_float) >
                     (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                     (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                     (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                     (qi::lit(",") > attr_value_float) > qi::eoi;
    BOOST_SPIRIT_DEBUG_NODES((msys_attribute));
}

} // namespace cldata
} // namespace pp
