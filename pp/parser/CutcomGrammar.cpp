//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "CutcomGrammar.h"

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

std::ostream& operator<<(std::ostream& ostr, const interface::CutterCompensation& value)
{
    switch (value)
    {
    case interface::CutterCompensation::ON:
        ostr << "ON";
        break;
    case interface::CutterCompensation::OFF:
        ostr << "OFF";
        break;
    case interface::CutterCompensation::LEFT:
        ostr << "LEFT";
        break;
    case interface::CutterCompensation::RIGHT:
        ostr << "RIGHT";
        break;
    }
    return ostr;
}

} // namespace interface

namespace cldata {

cutcom_grammar::cutcom_grammar()
    : cutcom_grammar::base_type(cutcom_attribute)
{
    cutter_compensation.add("ON", interface::CutterCompensation::ON)("OFF", interface::CutterCompensation::OFF)(
        "LEFT", interface::CutterCompensation::LEFT)("RIGHT", interface::CutterCompensation::RIGHT);

    // CUTCOM/RIGHT,1
    cutcom_attribute = qi::lit("CUTCOM") > qi::lit("/") > cutter_compensation > -(qi::lit(",") > qi::uint_);
    BOOST_SPIRIT_DEBUG_NODES((cutcom_attribute));
}

} // namespace cldata
} // namespace pp
