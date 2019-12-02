#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

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
