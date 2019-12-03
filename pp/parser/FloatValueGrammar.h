#pragma once

#include <boost/spirit/home/qi/stream.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::FloatValue,
    (boost::optional<char>, sign)
    (boost::optional<std::string>, value)
    (boost::optional<char>, dot)
    (boost::optional<std::string>, value2)
)

// clang-format on

namespace pp {
namespace cldata {

class float_value_grammar : public qi::grammar<pos_iterator_type, interface::FloatValue()>
{
public:
    float_value_grammar();

private:
    qi::rule<pos_iterator_type, std::string()>           attr_value;
    qi::rule<pos_iterator_type, std::string()>           attr_value2;
    qi::rule<pos_iterator_type, interface::FloatValue()> float_value_attribute;
};

} // namespace cldata
} // namespace pp
