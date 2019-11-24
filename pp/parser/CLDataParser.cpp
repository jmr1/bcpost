//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "CLDataParser.h"

#include <iomanip>

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include <boost/algorithm/string/trim.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

#include "CLDataParserGrammar.h"

namespace pp {
namespace cldata {

bool CLDataParser::parse(int line, const std::string& data, interface::AttributeVariantData& value,
                         std::string& message, bool single_line_msg)
{
    return parse(line, data, static_cast<interface::CLDAtaAttributeData&>(value).value, message, single_line_msg);
}

bool CLDataParser::parse(int line, const std::string& data, std::vector<interface::AttributeVariant>& value,
                         std::string& message, bool single_line_msg)
{
    std::istringstream                                                                  input(data);
    typedef boost::spirit::classic::position_iterator2<boost::spirit::istream_iterator> pos_iterator_type;
    pos_iterator_type position_begin(boost::spirit::istream_iterator{input >> std::noskipws}, {}), position_end;

    bool                                      ret = false;
    all_attributes_grammar<pos_iterator_type> all_attr_gr(ignored_operations(), message);

    try
    {
        ret = qi::phrase_parse(position_begin, position_end, all_attr_gr, qi::blank, value);
    }
    catch (const qi::expectation_failure<pos_iterator_type>& e)
    {
        const classic::file_position_base<std::string>& pos = e.first.get_position();
        std::stringstream                               msg;
        if (single_line_msg)
        {
            msg << pos.line << ":" << pos.column << ": " << std::string(e.first, e.last);
            if (!message.empty())
                msg << " <- " << message;
        }
        else
        {
            // if (other_settings.language == ELanguage::Polish)
            {
                msg << u8"Błąd parsowania w linii " << pos.line << u8" kolumna " << pos.column << ":" << std::endl
                    << "'" << e.first.get_currentline() << "'" << std::endl
                    << std::setw(pos.column) << " " << (message.empty() ? u8"^- tutaj" : "^- " + message) << std::endl;
            }
            /*else
            {
                msg << "Parse error at line " << pos.line << " column " << pos.column << ":" << std::endl
                    << "'" << e.first.get_currentline() << "'" << std::endl
                    << std::setw(pos.column) << " " << (message.empty() ? "^- here" : "^- " + message) << std::endl;
            }*/
        }
        message = msg.str();
    }
    catch (const std::out_of_range& e)
    {
        message = e.what();
        return false;
    }

    return ret;
}

bool CLDataParser::parse(int line, const std::string& data, std::string& message, bool single_line_msg)
{
    std::vector<interface::AttributeVariant> value;
    return parse(line, data, value, message, single_line_msg);
}

} // namespace cldata
} // namespace pp
