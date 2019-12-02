﻿//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "IgnoredValueGrammar.h"

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
    pp::interface::Ignored
)

// clang-format on

namespace pp {
namespace cldata {

ignored_value_grammar::ignored_value_grammar()
    : ignored_value_grammar::base_type(ignored_value_attribute)
{
    ignored_value_attribute = qi::omit[ignored] > qi::omit[*(qi::char_ - qi::eol)];
    BOOST_SPIRIT_DEBUG_NODES((ignored_value_attribute));
}

} // namespace cldata
} // namespace pp
