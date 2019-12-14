#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Circle,
    (pp::interface::FloatValue, x)
    (pp::interface::FloatValue, y)
    (pp::interface::FloatValue, z)
    (pp::interface::FloatValue, i)
    (pp::interface::FloatValue, j)
    (pp::interface::FloatValue, k)
    (pp::interface::FloatValue, r)
    (pp::interface::FloatValue, t)
    (pp::interface::FloatValue, f)
    (pp::interface::FloatValue, d)
    (pp::interface::FloatValue, e)
    (boost::optional<uint32_t>, n)
)

// clang-format on

namespace pp {
namespace cldata {

class circle_grammar : public qi::grammar<pos_iterator_type, interface::Circle(), qi::blank_type>
{
public:
    circle_grammar();

private:
    float_value_grammar                                              attr_value_float;
    qi::rule<pos_iterator_type, interface::Circle(), qi::blank_type> circle_attribute;
};

} // namespace cldata
} // namespace pp
