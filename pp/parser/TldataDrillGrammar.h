#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"
#include "interface/FusionTldataDrill.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

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
