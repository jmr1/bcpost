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
    pp::interface::Nil
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::FloatValue,
    (boost::optional<char>, sign)
    (boost::optional<std::string>, value)
    (boost::optional<char>, dot)
    (boost::optional<std::string>, value2)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Goto,
    (pp::interface::FloatValue, x)
    (pp::interface::FloatValue, y)
    (pp::interface::FloatValue, z)
    (boost::optional<pp::interface::FloatValue>, i)
    (boost::optional<pp::interface::FloatValue>, j)
    (boost::optional<pp::interface::FloatValue>, k)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::EndOfPath
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Ignored
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::ToolPath,
    (std::string, operation_name)
    (std::string, tool_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::TldataDrill,
    (std::string, module_type)
    (pp::interface::FloatValue, diameter)
    (pp::interface::FloatValue, corner_radius)
    (pp::interface::FloatValue, length)
    (pp::interface::FloatValue, point_angle)
    (pp::interface::FloatValue, flute_length)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::LoadTool,
    (int, tool_number)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::SelectTool,
    (int, tool_number)
)

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

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::CycleDrill,
    (pp::interface::FloatValue, rapto)
    (pp::interface::FloatValue, fedto)
    (boost::optional<pp::interface::FloatValue>, rtrcto)
    (pp::interface::RetractionType, retraction_type)
    (pp::interface::FedrateType, fedrate_type)
    (pp::interface::FloatValue, fedrate)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::CycleOff
)

// clang-format on

namespace pp {
namespace interface {

extern std::ostream& operator<<(std::ostream& ostr, const interface::RetractionType& value);
extern std::ostream& operator<<(std::ostream& ostr, const interface::FedrateType& value);

} // namespace interface

namespace cldata {

all_attributes_grammar::all_attributes_grammar(std::string& message)
    : all_attributes_grammar::base_type(line_attribute_vec)
{
    line_attribute     = (ignored_rule | goto_rule | cycle_drill_rule | cycle_off_rule | tool_path_rule |
                      tldata_drill_rule | load_tool_rule | select_tool_rule | msys_rule | end_of_path_rule);
    line_attribute_vec = /*-line_number_rule >*/ +line_attribute > qi::eoi;
    BOOST_SPIRIT_DEBUG_NODES((line_attribute)(line_attribute_vec));
}

} // namespace cldata
} // namespace pp
