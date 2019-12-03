#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::EndOfPath
)

// clang-format on

namespace pp {
namespace cldata {

class end_of_path_grammar : public qi::grammar<pos_iterator_type, interface::EndOfPath()>
{
public:
    end_of_path_grammar();

private:
    qi::rule<pos_iterator_type, interface::EndOfPath()> end_of_path_attribute;
};

} // namespace cldata
} // namespace pp
