#pragma once

#include <iomanip>

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp> // construct
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_symbols.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

//#include "MessageTextImpl.h"

#include "interface/CLData.h"

namespace qi      = boost::spirit::qi;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

using word_symbols = qi::symbols<char, std::string>;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::FloatValue,
    (boost::optional<char>, sign)
    (boost::optional<std::string>, value)
    (boost::optional<char>, dot)
    (boost::optional<std::string>, value2)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Goto,
    (pp::interface::FloatValue, x)
    (pp::interface::FloatValue, y)
    (pp::interface::FloatValue, z)
    (boost::optional<pp::interface::FloatValue>, i)
    (boost::optional<pp::interface::FloatValue>, j)
    (boost::optional<pp::interface::FloatValue>, k)
)

// clang-format on

namespace pp {
namespace cldata {

struct ignored_operations : qi::symbols<char, std::string>
{
    ignored_operations()
    {
        add("$$", "$$")("PAINT", "PAINT");
    }
};

/*template <typename Iterator>
class start_program_grammar : public qi::grammar<Iterator, ProgramBeginEndData()>
{
public:
    start_program_grammar()
        : start_program_grammar::base_type(start_program)
    {
        begin_end.add("BEGIN", EBeginEnd::begin)("END", EBeginEnd::end);

        unit.add("MM", EUnit::mm)("INCH", EUnit::inch);

        start_program = begin_end > qi::omit[+qi::blank] > qi::lit("PGM") > qi::omit[+qi::blank] >
                        *(qi::char_("a-zA-Z0-9_")) > qi::omit[+qi::blank] > unit > qi::omit[+qi::space | qi::eoi] >
                        !qi::char_("a-zA-Z0-9_");
        BOOST_SPIRIT_DEBUG_NODE((start_program));
    }

private:
    qi::symbols<char, cldata::EBeginEnd>  begin_end;
    qi::symbols<char, cldata::EUnit>      unit;
    qi::rule<Iterator, ProgramBeginEndData()> start_program;
};*/

template <typename Iterator>
class float_value_grammar : public qi::grammar<Iterator, interface::FloatValue()>
{
public:
    float_value_grammar()
        : float_value_grammar::base_type(float_value_attribute)
    {
        attr_value            = +qi::char_("0-9");
        attr_value2           = +qi::char_("0-9");
        float_value_attribute = -qi::char_("-+") > -attr_value > -qi::char_(".") > -attr_value2;
        BOOST_SPIRIT_DEBUG_NODES((float_value_attribute));
    }

private:
    qi::rule<Iterator, std::string()>           attr_value;
    qi::rule<Iterator, std::string()>           attr_value2;
    qi::rule<Iterator, interface::FloatValue()> float_value_attribute;
};

template <typename Iterator>
class goto_grammar : public qi::grammar<Iterator, interface::Goto(), qi::blank_type>
{
public:
    goto_grammar()
        : goto_grammar::base_type(goto_attribute)
    {
        goto_attribute = qi::lit("GOTO") > qi::lit("/") > attr_value_float > (qi::lit(",") > attr_value_float) >
                         (qi::lit(",") > attr_value_float) > -(qi::lit(",") > attr_value_float) >
                         -(qi::lit(",") > attr_value_float) > -(qi::lit(",") > attr_value_float);

        BOOST_SPIRIT_DEBUG_NODES((goto_attribute));
    }

private:
    float_value_grammar<Iterator>                         attr_value_float;
    qi::rule<Iterator, interface::Goto(), qi::blank_type> goto_attribute;
};

template <typename Iterator>
class all_attributes_grammar : public qi::grammar<Iterator, std::vector<interface::AttributeVariant>(), qi::blank_type>
{
public:
    all_attributes_grammar(const word_symbols& sym, std::string& message)
        : all_attributes_grammar::base_type(line_attribute_vec)
    {
        line_attribute     = (goto_rule /* | general_attribute_rule*/);
        line_attribute_vec = /*-line_number_rule >*/ +line_attribute > qi::eoi;
        BOOST_SPIRIT_DEBUG_NODES((line_attribute)(line_attribute_vec));
    }

private:
    goto_grammar<Iterator>                                                         goto_rule;
    qi::rule<Iterator, interface::AttributeVariant(), qi::blank_type>              line_attribute;
    qi::rule<Iterator, std::vector<interface::AttributeVariant>(), qi::blank_type> line_attribute_vec;
};

using pos_iterator_type = boost::spirit::classic::position_iterator2<boost::spirit::istream_iterator>;
extern template class all_attributes_grammar<pos_iterator_type>;

} // namespace cldata
} // namespace pp
