#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"
#include "interface/FusionTldataMill.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

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
