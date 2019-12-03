#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Msys,
    (pp::interface::FloatValue, shift_x)
    (pp::interface::FloatValue, shift_y)
    (pp::interface::FloatValue, shift_z)
    (pp::interface::FloatValue, col1_x)
    (pp::interface::FloatValue, col1_y)
    (pp::interface::FloatValue, col1_z)
    (pp::interface::FloatValue, col2_x)
    (pp::interface::FloatValue, col2_y)
    (pp::interface::FloatValue, col2_z)
)

// clang-format on

namespace pp {
namespace cldata {

class msys_grammar : public qi::grammar<pos_iterator_type, interface::Msys(), qi::blank_type>
{
public:
    msys_grammar();

private:
    float_value_grammar                                            attr_value_float;
    qi::rule<pos_iterator_type, interface::Msys(), qi::blank_type> msys_attribute;
};

} // namespace cldata
} // namespace pp
