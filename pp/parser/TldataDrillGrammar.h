#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::TldataDrill,
    (std::string, module_type)
    (pp::interface::FloatValue, diameter)
    (pp::interface::FloatValue, corner_radius)
    (pp::interface::FloatValue, length)
    (pp::interface::FloatValue, point_angle)
    (pp::interface::FloatValue, flute_length)
)

// clang-format on

namespace pp {
namespace cldata {

class tldata_drill_grammar : public qi::grammar<pos_iterator_type, interface::TldataDrill(), qi::blank_type>
{
public:
    tldata_drill_grammar();

private:
    float_value_grammar                                                   attr_value_float;
    qi::rule<pos_iterator_type, interface::TldataDrill(), qi::blank_type> tldata_drill_attribute;
};

} // namespace cldata
} // namespace pp
