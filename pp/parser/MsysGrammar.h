#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"
#include "interface/FusionMsys.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

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
