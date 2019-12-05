#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_symbols.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::SpindlRpm,
    (pp::interface::FloatValue, rpm)
    (pp::interface::RotationDirection, rotation_direction)
)

// clang-format on

namespace pp {
namespace cldata {

class spindl_rpm_grammar : public qi::grammar<pos_iterator_type, interface::SpindlRpm(), qi::blank_type>
{
public:
    spindl_rpm_grammar();

private:
    qi::symbols<char, interface::RotationDirection>                     rotation_direction;
    float_value_grammar                                                 attr_value_float;
    qi::rule<pos_iterator_type, interface::SpindlRpm(), qi::blank_type> spindl_rpm_attribute;
};

} // namespace cldata
} // namespace pp
