#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"
#include "interface/FusionLoadTool.h"

#include "PosIteratorType.h"

namespace qi = boost::spirit::qi;

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
