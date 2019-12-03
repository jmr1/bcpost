#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::ToolPath,
    (std::string, operation_name)
    (std::string, tool_name)
)

// clang-format on

namespace pp {
namespace cldata {

class tool_path_grammar : public qi::grammar<pos_iterator_type, interface::ToolPath(), qi::blank_type>
{
public:
    tool_path_grammar();

private:
    qi::rule<pos_iterator_type, interface::ToolPath(), qi::blank_type> tool_path_attribute;
};

} // namespace cldata
} // namespace pp
