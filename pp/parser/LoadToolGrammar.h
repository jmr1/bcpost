#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::LoadTool,
    (int, tool_number)
)

// clang-format on

namespace pp {
namespace cldata {

class load_tool_grammar : public qi::grammar<pos_iterator_type, interface::LoadTool(), qi::blank_type>
{
public:
    load_tool_grammar();

private:
    qi::rule<pos_iterator_type, interface::LoadTool(), qi::blank_type> load_tool_attribute;
};

} // namespace cldata
} // namespace pp
