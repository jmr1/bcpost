#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Goto,
    (pp::interface::FloatValue, x)
    (pp::interface::FloatValue, y)
    (pp::interface::FloatValue, z)
    (boost::optional<pp::interface::FloatValue>, i)
    (boost::optional<pp::interface::FloatValue>, j)
    (boost::optional<pp::interface::FloatValue>, k)
)

// clang-format on

namespace pp {
namespace cldata {

class goto_grammar : public qi::grammar<pos_iterator_type, interface::Goto(), qi::blank_type>
{
public:
    goto_grammar();

private:
    float_value_grammar                                            attr_value_float;
    qi::rule<pos_iterator_type, interface::Goto(), qi::blank_type> goto_attribute;
};

} // namespace cldata
} // namespace pp
