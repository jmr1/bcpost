﻿#pragma once

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

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::EndOfPath
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Ignored
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::CycleOff
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::ToolPath,
    (std::string, operation_name)
    (std::string, tool_name)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::TldataDrill,
    (std::string, module_type)
    (pp::interface::FloatValue, diameter)
    (pp::interface::FloatValue, corner_radius)
    (pp::interface::FloatValue, length)
    (pp::interface::FloatValue, point_angle)
    (pp::interface::FloatValue, flute_length)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::LoadTool,
    (int, tool_number)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::SelectTool,
    (int, tool_number)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Msys,
    (pp::interface::FloatValue, shift_x)
    (pp::interface::FloatValue, shift_y)
    (pp::interface::FloatValue, shift_z)
    (pp::interface::FloatValue, col1_x)
    (pp::interface::FloatValue, col1_y)
    (pp::interface::FloatValue, col1_z)
    (pp::interface::FloatValue, col2_x)
    (pp::interface::FloatValue, col2_y)
    (pp::interface::FloatValue, col2_z)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Nil
)

//enum class RetractionType
//{
//    AUTO   = 98,
//    MANUAL = 99
//};
//
//enum class FedrateType
//{
//    IPM,
//    IPR,
//    MMPM,
//    MMPR
//};
//
//struct CycleDrill
//{
//    FloatValue                  rapto;
//    FloatValue                  fedto;
//    boost::optional<FloatValue> rtrcto;
//    RetractionType              retraction_type;
//    FedrateType                 fedrate_type;
//    FloatValue                  fedrate;
//};

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::CycleDrill,
    (pp::interface::FloatValue, rapto)
    (pp::interface::FloatValue, fedto)
    (boost::optional<pp::interface::FloatValue>, rtrcto)
    (pp::interface::RetractionType, retraction_type)
    (pp::interface::FedrateType, fedrate_type)
    (pp::interface::FloatValue, fedrate)
)

// clang-format on

namespace pp {
namespace cldata {

template <typename Iterator>
class float_value_grammar : public qi::grammar<Iterator, interface::FloatValue()>
{
public:
    float_value_grammar()
        : float_value_grammar::base_type(float_value_attribute)
    {
        attr_value            = +qi::char_("0-9");
        attr_value2           = +qi::char_("0-9");
        float_value_attribute = (-qi::char_("-+") > attr_value > -qi::char_(".") > -attr_value2) |
                                (-qi::char_("-+") > -attr_value > qi::char_(".") > attr_value2);
        BOOST_SPIRIT_DEBUG_NODES((float_value_attribute));
    }

private:
    qi::rule<Iterator, std::string()>           attr_value;
    qi::rule<Iterator, std::string()>           attr_value2;
    qi::rule<Iterator, interface::FloatValue()> float_value_attribute;
};

template <typename Iterator>
class load_tool_grammar : public qi::grammar<Iterator, interface::LoadTool(), qi::blank_type>
{
public:
    load_tool_grammar()
        : load_tool_grammar::base_type(load_tool_attribute)
    {
        // LOAD/TOOL,5
        load_tool_attribute = qi::lit("LOAD") > qi::lit("/") > qi::lit("TOOL") > qi::lit(",") > qi::int_ > qi::eoi;
        BOOST_SPIRIT_DEBUG_NODES((load_tool_attribute));
    }

private:
    qi::rule<Iterator, interface::LoadTool(), qi::blank_type> load_tool_attribute;
};

template <typename Iterator>
class select_tool_grammar : public qi::grammar<Iterator, interface::SelectTool(), qi::blank_type>
{
public:
    select_tool_grammar()
        : select_tool_grammar::base_type(select_tool_attribute)
    {
        // SELECT/TOOL,5
        select_tool_attribute = qi::lit("SELECT") > qi::lit("/") > qi::lit("TOOL") > qi::lit(",") > qi::int_ > qi::eoi;
        BOOST_SPIRIT_DEBUG_NODES((select_tool_attribute));
    }

private:
    qi::rule<Iterator, interface::SelectTool(), qi::blank_type> select_tool_attribute;
};

template <typename Iterator>
class end_of_path_grammar : public qi::grammar<Iterator, interface::EndOfPath()>
{
public:
    end_of_path_grammar()
        : end_of_path_grammar::base_type(end_of_path_attribute)
    {
        end_of_path_attribute = qi::lit("END-OF-PATH")[phx::construct<interface::EndOfPath>()];
        BOOST_SPIRIT_DEBUG_NODES((end_of_path_attribute));
    }

private:
    qi::rule<Iterator, interface::EndOfPath()> end_of_path_attribute;
};

std::ostream& operator<<(std::ostream& ostr, const interface::RetractionType& value);
std::ostream& operator<<(std::ostream& ostr, const interface::FedrateType& value);

template <typename Iterator>
class cycle_drill_grammar : public qi::grammar<Iterator, interface::CycleDrill(), qi::blank_type>
{
public:
    cycle_drill_grammar()
        : cycle_drill_grammar::base_type(cycle_drill_attribute)
    {
        retraction_type.add("AUTO", interface::RetractionType::AUTO)("MANUAL", interface::RetractionType::MANUAL);
        fedrate_type.add("IPM", interface::FedrateType::IPM)("IPR", interface::FedrateType::IPR)(
            "MMPM", interface::FedrateType::MMPM)("MMPR", interface::FedrateType::MMPM);

        // CYCLE/DRILL,RAPTO,3.0000,FEDTO,-33.0043,RTRCTO,AUTO,MMPM,250.0000
        // RTRCO may have value defined, if not then the RAPTO value is taken
        cycle_drill_attribute = qi::lit("CYCLE") > qi::lit("/") > qi::lit("DRILL") > qi::lit(",") > qi::lit("RAPTO") >
                                qi::lit(",") > attr_value_float > qi::lit(",") > qi::lit("RAPTO") > qi::lit(",") >
                                attr_value_float > -(qi::lit(",") > qi::lit("RTRCTO")) >
                                -(qi::lit(",") > attr_value_float) > qi::lit(",") > retraction_type > qi::lit(",") >
                                fedrate_type > qi::lit(",") > attr_value_float;
        BOOST_SPIRIT_DEBUG_NODES((cycle_drill_attribute));
    }

private:
    qi::symbols<char, interface::RetractionType>                retraction_type;
    qi::symbols<char, interface::FedrateType>                   fedrate_type;
    float_value_grammar<Iterator>                               attr_value_float;
    qi::rule<Iterator, interface::CycleDrill(), qi::blank_type> cycle_drill_attribute;
};

template <typename Iterator>
class cycle_off_grammar : public qi::grammar<Iterator, interface::CycleOff(), qi::blank_type>
{
public:
    cycle_off_grammar()
        : cycle_off_grammar::base_type(cycle_off_attribute)
    {
        cycle_off_attribute = qi::lit("CYCLE") > qi::lit("/") > qi::lit("OFF")[phx::construct<interface::CycleOff>()];
        BOOST_SPIRIT_DEBUG_NODES((cycle_off_attribute));
    }

private:
    qi::rule<Iterator, interface::CycleOff(), qi::blank_type> cycle_off_attribute;
};

template <typename Iterator>
class tool_path_grammar : public qi::grammar<Iterator, interface::ToolPath(), qi::blank_type>
{
public:
    tool_path_grammar()
        : tool_path_grammar::base_type(tool_path_attribute)
    {
        // TOOL PATH/DRILLING_1,TOOL,STD_DRILL_D10
        tool_path_attribute = qi::lexeme[qi::lit("TOOL") > qi::omit[+qi::space]] > qi::lit("PATH") > qi::lit("/") >
                              qi::lexeme[+qi::char_("a-zA-Z0-9_")] > qi::lit(",") > qi::lit("TOOL") > qi::lit(",") >
                              qi::lexeme[+qi::char_("a-zA-Z0-9_")] > qi::eoi;
        BOOST_SPIRIT_DEBUG_NODES((tool_path_attribute));
    }

private:
    qi::rule<Iterator, interface::ToolPath(), qi::blank_type> tool_path_attribute;
};

template <typename Iterator>
class msys_grammar : public qi::grammar<Iterator, interface::Msys(), qi::blank_type>
{
public:
    msys_grammar()
        : msys_grammar::base_type(msys_attribute)
    {
        // MSYS/0.0000,0.0000,180.0000,0.5000000,0.0000000,0.8660254,0.8660254,0.0000000,-0.5000000
        msys_attribute = qi::lit("MSYS") > qi::lit("/") > attr_value_float > (qi::lit(",") > attr_value_float) >
                         (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                         (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                         (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                         (qi::lit(",") > attr_value_float) > qi::eoi;
        BOOST_SPIRIT_DEBUG_NODES((msys_attribute));
    }

private:
    float_value_grammar<Iterator>                         attr_value_float;
    qi::rule<Iterator, interface::Msys(), qi::blank_type> msys_attribute;
};

template <typename Iterator>
class tldata_drill_grammar : public qi::grammar<Iterator, interface::TldataDrill(), qi::blank_type>
{
public:
    tldata_drill_grammar()
        : tldata_drill_grammar::base_type(tldata_drill_attribute)
    {
        // TLDATA/DRILL,MILL,10.0000,0.0000,80.0000,118.0000,35.0000
        tldata_drill_attribute = qi::lit("TLDATA") > qi::lit("/") > qi::lit("DRILL") >
                                 (qi::lit(",") > qi::lexeme[+qi::char_("a-zA-Z0-9_")]) >
                                 (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                                 (qi::lit(",") > attr_value_float) > (qi::lit(",") > attr_value_float) >
                                 (qi::lit(",") > attr_value_float) > qi::eoi;
        BOOST_SPIRIT_DEBUG_NODES((tldata_drill_attribute));
    }

private:
    float_value_grammar<Iterator>                                attr_value_float;
    qi::rule<Iterator, interface::TldataDrill(), qi::blank_type> tldata_drill_attribute;
};

struct ignored_operations : qi::symbols<char, std::string>
{
    ignored_operations()
    {
        add("$$", "$$")("PAINT", "PAINT");
    }
};

template <typename Iterator>
class ignored_value_grammar : public qi::grammar<Iterator, interface::Ignored()>
{
public:
    ignored_value_grammar()
        : ignored_value_grammar::base_type(ignored_value_attribute)
    {
        ignored_value_attribute = qi::omit[ignored] > qi::omit[*(qi::char_ - qi::eol)];
        BOOST_SPIRIT_DEBUG_NODES((ignored_value_attribute));
    }

private:
    ignored_operations                       ignored;
    qi::rule<Iterator, interface::Ignored()> ignored_value_attribute;
};

template <typename Iterator>
class goto_grammar : public qi::grammar<Iterator, interface::Goto(), qi::blank_type>
{
public:
    goto_grammar()
        : goto_grammar::base_type(goto_attribute)
    {
        // GOTO/-24.5855,-115.0000,100.0000,0.0000000,0.0000000,1.0000000
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
        line_attribute     = (ignored_rule | goto_rule | cycle_off_rule | tool_path_rule | tldata_drill_rule |
                          load_tool_rule | select_tool_rule | msys_rule | end_of_path_rule);
        line_attribute_vec = /*-line_number_rule >*/ +line_attribute > qi::eoi;
        BOOST_SPIRIT_DEBUG_NODES((line_attribute)(line_attribute_vec));
    }

private:
    goto_grammar<Iterator>                                                         goto_rule;
    msys_grammar<Iterator>                                                         msys_rule;
    cycle_off_grammar<Iterator>                                                    cycle_off_rule;
    cycle_drill_grammar<Iterator>                                                  cycle_drill_rule;
    end_of_path_grammar<Iterator>                                                  end_of_path_rule;
    ignored_value_grammar<Iterator>                                                ignored_rule;
    tool_path_grammar<Iterator>                                                    tool_path_rule;
    load_tool_grammar<Iterator>                                                    load_tool_rule;
    select_tool_grammar<Iterator>                                                  select_tool_rule;
    tldata_drill_grammar<Iterator>                                                 tldata_drill_rule;
    qi::rule<Iterator, interface::AttributeVariant(), qi::blank_type>              line_attribute;
    qi::rule<Iterator, std::vector<interface::AttributeVariant>(), qi::blank_type> line_attribute_vec;
};

using pos_iterator_type = boost::spirit::classic::position_iterator2<boost::spirit::istream_iterator>;
extern template class all_attributes_grammar<pos_iterator_type>;

} // namespace cldata
} // namespace pp
