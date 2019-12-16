#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"
#include "interface/FusionCircle.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

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
