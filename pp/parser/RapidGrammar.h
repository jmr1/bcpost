#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Rapid
)

// clang-format on

namespace pp {
namespace cldata {

class rapid_grammar : public qi::grammar<pos_iterator_type, interface::Rapid()>
{
public:
    rapid_grammar();

private:
    qi::rule<pos_iterator_type, interface::Rapid()> rapid_attribute;
};

} // namespace cldata
} // namespace pp
