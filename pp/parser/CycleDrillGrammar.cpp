//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "CycleDrillGrammar.h"

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
namespace interface {

std::ostream& operator<<(std::ostream& ostr, const interface::RetractionType& value)
{
    switch (value)
    {
    case interface::RetractionType::AUTO:
        ostr << "AUTO";
        break;
    case interface::RetractionType::MANUAL:
        ostr << "MANUAL";
        break;
    }
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const interface::FedrateType& value)
{
    switch (value)
    {
    case interface::FedrateType::IPM:
        ostr << "IPM";
        break;
    case interface::FedrateType::IPR:
        ostr << "IPR";
        break;
    case interface::FedrateType::MMPM:
        ostr << "MMPM";
        break;
    case interface::FedrateType::MMPR:
        ostr << "MMPR";
        break;
    }
    return ostr;
}

} // namespace interface

namespace cldata {

cycle_drill_grammar::cycle_drill_grammar()
    : cycle_drill_grammar::base_type(cycle_drill_attribute)
{
    retraction_type.add("AUTO", interface::RetractionType::AUTO)("MANUAL", interface::RetractionType::MANUAL);
    fedrate_type.add("IPM", interface::FedrateType::IPM)("IPR", interface::FedrateType::IPR)(
        "MMPM", interface::FedrateType::MMPM)("MMPR", interface::FedrateType::MMPM);

    // CYCLE/DRILL,RAPTO,3.0000,FEDTO,-33.0043,RTRCTO,AUTO,MMPM,250.0000
    // RTRCO may have value defined, if not then the RAPTO value is taken
    cycle_drill_attribute = &(qi::lit("CYCLE") >> qi::lit("/") >> qi::lit("DRILL")) > qi::lit("CYCLE") > qi::lit("/") >
                            qi::lit("DRILL") > qi::lit(",") > qi::lit("RAPTO") > qi::lit(",") > attr_value_float >
                            qi::lit(",") > qi::lit("FEDTO") > qi::lit(",") > attr_value_float > qi::lit(",") >
                            -((qi::lit("RTRCTO") - retraction_type) > qi::lit(",")) > -((attr_value_float - retraction_type) > qi::lit(",")) >
                            retraction_type > qi::lit(",") > fedrate_type > qi::lit(",") > attr_value_float;
    BOOST_SPIRIT_DEBUG_NODES((cycle_drill_attribute));
}

} // namespace cldata
} // namespace pp
