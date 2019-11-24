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

/*BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::EndOfPath,
    ()
)*/

// clang-format on

namespace pp {
namespace cldata {

template <typename Iterator>
class end_of_path_grammar : public qi::grammar<Iterator, interface::EndOfPath()>
{
public:
    end_of_path_grammar()
        : end_of_path_grammar::base_type(attribute)
    {
        attribute = qi::lit("END-OF-PATH")[phx::construct<interface::EndOfPath>()];
        BOOST_SPIRIT_DEBUG_NODES((attribute));
    }

private:
    qi::rule<Iterator, interface::EndOfPath()> attribute;
};

struct ignored_operations : qi::symbols<char, std::string>
{
    ignored_operations()
    {
        add("$$", "$$")("PAINT", "PAINT");
    }
};

template <typename Iterator>
class ignored_value_grammar : public qi::grammar<Iterator, void()>
{
public:
    ignored_value_grammar()
        : ignored_value_grammar::base_type(attribute)
    {
        attribute = qi::omit[ignored] > qi::omit[*(qi::char_ - qi::eol)];
        BOOST_SPIRIT_DEBUG_NODES((attribute));
    }

private:
    ignored_operations         ignored;
    qi::rule<Iterator, void()> attribute;
};

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
    all_attributes_grammar(std::string& message)
        : all_attributes_grammar::base_type(line_attribute_vec)
    {
        line_attribute     = (ignored_rule | goto_rule | end_of_path_rule);
        line_attribute_vec = /*-line_number_rule >*/ +line_attribute > qi::eoi;
        BOOST_SPIRIT_DEBUG_NODES((line_attribute)(line_attribute_vec));
    }

private:
    goto_grammar<Iterator>                                                         goto_rule;
    end_of_path_grammar<Iterator>                                                  end_of_path_rule;
    ignored_value_grammar<Iterator>                                                ignored_rule;
    qi::rule<Iterator, interface::AttributeVariant(), qi::blank_type>              line_attribute;
    qi::rule<Iterator, std::vector<interface::AttributeVariant>(), qi::blank_type> line_attribute_vec;
};

using pos_iterator_type = boost::spirit::classic::position_iterator2<boost::spirit::istream_iterator>;
extern template class all_attributes_grammar<pos_iterator_type>;

} // namespace cldata
} // namespace pp
