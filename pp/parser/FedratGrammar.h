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
    pp::interface::Fedrat,
    (pp::interface::FedrateType, fedrate_type)
    (pp::interface::FloatValue, units_number)
)

// clang-format on

namespace pp {
namespace cldata {

class fedrat_grammar : public qi::grammar<pos_iterator_type, interface::Fedrat(), qi::blank_type>
{
public:
    fedrat_grammar();

private:
    qi::symbols<char, interface::FedrateType>                        fedrate_type;
    float_value_grammar                                              attr_value_float;
    qi::rule<pos_iterator_type, interface::Fedrat(), qi::blank_type> fedrat_attribute;
};

} // namespace cldata
} // namespace pp
