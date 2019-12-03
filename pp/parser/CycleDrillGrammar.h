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
    pp::interface::CycleDrill,
    (pp::interface::FloatValue, rapto)
    (pp::interface::FloatValue, fedto)
    (boost::optional<pp::interface::FloatValue>, rtrcto)
    (pp::interface::RetractionType, retraction_type)
    (pp::interface::FedrateType, fedrate_type)
    (pp::interface::FloatValue, fedrate)
)

// clang-format on

namespace pp {
namespace cldata {

class cycle_drill_grammar : public qi::grammar<pos_iterator_type, interface::CycleDrill(), qi::blank_type>
{
public:
    cycle_drill_grammar();

private:
    qi::symbols<char, interface::RetractionType>                         retraction_type;
    qi::symbols<char, interface::FedrateType>                            fedrate_type;
    float_value_grammar                                                  attr_value_float;
    qi::rule<pos_iterator_type, interface::CycleDrill(), qi::blank_type> cycle_drill_attribute;
};

} // namespace cldata
} // namespace pp
