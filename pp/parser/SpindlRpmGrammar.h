#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_symbols.hpp>

#include "interface/CLData.h"
#include "interface/FusionSpindlRpm.h"

#include "PosIteratorType.h"

#include "FloatValueGrammar.h"

namespace qi = boost::spirit::qi;

namespace pp {
namespace cldata {

class spindl_rpm_grammar : public qi::grammar<pos_iterator_type, interface::SpindlRpm(), qi::blank_type>
{
public:
    spindl_rpm_grammar();

private:
    qi::symbols<char, interface::RotationDirection>                     rotation_direction;
    float_value_grammar                                                 attr_value_float;
    qi::rule<pos_iterator_type, interface::SpindlRpm(), qi::blank_type> spindl_rpm_attribute;
};

} // namespace cldata
} // namespace pp
