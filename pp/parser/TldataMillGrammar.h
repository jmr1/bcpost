#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::TldataMill,
    (pp::interface::FloatValue, diameter)
    (pp::interface::FloatValue, lower_radius)
    (pp::interface::FloatValue, length)
    (pp::interface::FloatValue, taper_angle)
    (pp::interface::FloatValue, tip_angle)
    (boost::optional<pp::interface::FloatValue>, x_center_r1)
    (boost::optional<pp::interface::FloatValue>, y_center_r1)
    (boost::optional<pp::interface::FloatValue>, upper_radius)
    (boost::optional<pp::interface::FloatValue>, x_center_r2)
    (boost::optional<pp::interface::FloatValue>, y_center_r2)
)

// clang-format on

namespace pp {
namespace cldata {

class tldata_mill_grammar : public qi::grammar<pos_iterator_type, interface::TldataMill(), qi::blank_type>
{
public:
    tldata_mill_grammar();

private:
    float_value_grammar                                                  attr_value_float;
    qi::rule<pos_iterator_type, interface::TldataMill(), qi::blank_type> tldata_mill_attribute;
};

} // namespace cldata
} // namespace pp
