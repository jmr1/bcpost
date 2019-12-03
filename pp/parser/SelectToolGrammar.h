#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::SelectTool,
    (int, tool_number)
)

// clang-format on

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
