﻿//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "LoadToolGrammar.h"

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
    pp::interface::LoadTool,
    (int, tool_number)
)

// clang-format on

namespace pp {
namespace cldata {

load_tool_grammar::load_tool_grammar()
    : load_tool_grammar::base_type(load_tool_attribute)
{
    // LOAD/TOOL,5
    load_tool_attribute = qi::lit("LOAD") > qi::lit("/") > qi::lit("TOOL") > qi::lit(",") > qi::int_ > qi::eoi;
    BOOST_SPIRIT_DEBUG_NODES((load_tool_attribute));
}

} // namespace cldata
} // namespace pp
