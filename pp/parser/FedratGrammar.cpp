//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "FedratGrammar.h"

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

fedrat_grammar::fedrat_grammar()
    : fedrat_grammar::base_type(fedrat_attribute)
{
    fedrate_type.add("IPM", interface::FedrateType::IPM)("IPR", interface::FedrateType::IPR)(
        "MMPM", interface::FedrateType::MMPM)("MMPR", interface::FedrateType::MMPM);

    // FEDRAT/MMPM,250.0000
    fedrat_attribute = qi::lit("FEDRAT") > qi::lit("/") > fedrate_type > qi::lit(",") > attr_value_float;
    BOOST_SPIRIT_DEBUG_NODES((fedrat_attribute));
}

} // namespace cldata
} // namespace pp
