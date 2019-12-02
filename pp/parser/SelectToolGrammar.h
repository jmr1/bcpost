#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

namespace qi = boost::spirit::qi;

namespace pp {
namespace cldata {

class select_tool_grammar : public qi::grammar<pos_iterator_type, interface::SelectTool(), qi::blank_type>
{
public:
    select_tool_grammar();

private:
    qi::rule<pos_iterator_type, interface::SelectTool(), qi::blank_type> select_tool_attribute;
};

} // namespace cldata
} // namespace pp
