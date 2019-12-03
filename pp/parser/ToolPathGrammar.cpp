//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "ToolPathGrammar.h"

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
    pp::interface::ToolPath,
    (std::string, operation_name)
    (std::string, tool_name)
)

// clang-format on

namespace pp {
namespace cldata {

tool_path_grammar::tool_path_grammar()
    : tool_path_grammar::base_type(tool_path_attribute)
{
    // TOOL PATH/DRILLING_1,TOOL,STD_DRILL_D10
    tool_path_attribute = qi::lexeme[qi::lit("TOOL") > qi::omit[+qi::space]] > qi::lit("PATH") > qi::lit("/") >
                          qi::lexeme[+qi::char_("a-zA-Z0-9_")] > qi::lit(",") > qi::lit("TOOL") > qi::lit(",") >
                          qi::lexeme[+qi::char_("a-zA-Z0-9_")] > qi::eoi;
    BOOST_SPIRIT_DEBUG_NODES((tool_path_attribute));
}

} // namespace cldata
} // namespace pp
