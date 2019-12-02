//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "TldataDrillGrammar.h"

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
    pp::interface::TldataDrill,
    (std::string, module_type)
    (pp::interface::FloatValue, diameter)
    (pp::interface::FloatValue, corner_radius)
    (pp::interface::FloatValue, length)
    (pp::interface::FloatValue, point_angle)
    (pp::interface::FloatValue, flute_length)
)

// clang-format on

namespace pp {
namespace cldata {

tldata_drill_grammar::tldata_drill_grammar()
    : tldata_drill_grammar::base_type(tldata_drill_attribute)
{
    // TLDATA/DRILL,MILL,10.0000,0.0000,80.0000,118.0000,35.0000
    tldata_drill_attribute = qi::lit("TLDATA") > qi::lit("/") > qi::lit("DRILL") >
                             (qi::lit(",") > qi::lexeme[+qi::char_("a-zA-Z0-9_")]) > (qi::lit(",") > attr_value_float) >
                             (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                             (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) > qi::eoi;
    BOOST_SPIRIT_DEBUG_NODES((tldata_drill_attribute));
}

} // namespace cldata
} // namespace pp
