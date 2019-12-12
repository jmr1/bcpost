#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_symbols.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

namespace qi = boost::spirit::qi;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Cutcom,
    (pp::interface::CutterCompensation, cutter_compensation)
    (boost::optional<uint32_t>, register_number)
)

// clang-format on

namespace pp {
namespace cldata {

class cutcom_grammar : public qi::grammar<pos_iterator_type, interface::Cutcom(), qi::blank_type>
{
public:
    cutcom_grammar();

private:
    qi::symbols<char, interface::CutterCompensation>                 cutter_compensation;
    qi::rule<pos_iterator_type, interface::Cutcom(), qi::blank_type> cutcom_attribute;
};

} // namespace cldata
} // namespace pp
