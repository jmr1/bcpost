//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "SpindlRpmGrammar.h"

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

std::ostream& operator<<(std::ostream& ostr, const interface::RotationDirection& value)
{
    switch (value)
    {
    case interface::RotationDirection::CLW:
        ostr << "CLW";
        break;
    case interface::RotationDirection::CCLW:
        ostr << "CCLW";
        break;
    }
    return ostr;
}

} // namespace interface

namespace cldata {

spindl_rpm_grammar::spindl_rpm_grammar()
    : spindl_rpm_grammar::base_type(spindl_rpm_attribute)
{
    rotation_direction.add("CLW", interface::RotationDirection::CLW)("CCLW", interface::RotationDirection::CCLW);

    // SPINDL/RPM,800,CLW
    spindl_rpm_attribute = qi::lit("SPINDL") > qi::lit("/") > qi::lit("RPM") > qi::lit(",") > attr_value_float >
                           qi::lit(",") > rotation_direction;
    BOOST_SPIRIT_DEBUG_NODES((spindl_rpm_attribute));
}

} // namespace cldata
} // namespace pp
