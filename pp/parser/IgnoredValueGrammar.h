#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

namespace qi = boost::spirit::qi;

namespace pp {
namespace cldata {

struct ignored_operations : qi::symbols<char, std::string>
{
    ignored_operations()
    {
        add("$$", "$$")("PAINT", "PAINT");
    }
};

class ignored_value_grammar : public qi::grammar<pos_iterator_type, interface::Ignored()>
{
public:
    ignored_value_grammar();

private:
    ignored_operations                                ignored;
    qi::rule<pos_iterator_type, interface::Ignored()> ignored_value_attribute;
};

} // namespace cldata
} // namespace pp
