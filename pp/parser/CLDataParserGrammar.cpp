//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "CLDataParserGrammar.h"

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

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Nil
)

// clang-format on

namespace pp {
namespace cldata {

all_attributes_grammar::all_attributes_grammar(std::string& message)
    : all_attributes_grammar::base_type(line_attribute_vec)
{
    line_attribute     = (ignored_rule | goto_rule | circle_rule | cycle_drill_rule | cycle_off_rule | tool_path_rule |
                      tldata_drill_rule | tldata_mill_rule | load_tool_rule | select_tool_rule | msys_rule |
                      end_of_path_rule | spindl_rpm_rule | rapid_rule | cutcom_rule | fedrat_rule);
    line_attribute_vec = /*-line_number_rule >*/ +line_attribute > qi::eoi;
    BOOST_SPIRIT_DEBUG_NODES((line_attribute)(line_attribute_vec));
}

} // namespace cldata
} // namespace pp
