#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"
#include "interface/FusionCycleOff.h"

#include "PosIteratorType.h"

namespace qi = boost::spirit::qi;

namespace pp {
namespace cldata {

using pos_iterator_type = boost::spirit::classic::position_iterator2<boost::spirit::istream_iterator>;

class cycle_off_grammar : public qi::grammar<pos_iterator_type, interface::CycleOff(), qi::blank_type>
{
public:
    cycle_off_grammar();

private:
    qi::rule<pos_iterator_type, interface::CycleOff(), qi::blank_type> cycle_off_attribute;
};

} // namespace cldata
} // namespace pp
