#pragma once

#include "pp_export.h"

#include <string>
#include <vector>

#include <boost/spirit/include/qi_symbols.hpp>

#include "ParserBase.h"
#include "interface/CLData.h"
#include "interface/GeneralDefines.h"

namespace qi = boost::spirit::qi;

using word_symbols = qi::symbols<char, std::string>;

namespace pp {
namespace cldata {

class PARSER_API CLDataParser : public ParserBase
{
public:
    CLDataParser();

    virtual ~CLDataParser()           = default;
    CLDataParser(const CLDataParser&) = delete;
    CLDataParser(CLDataParser&&)      = default;
    CLDataParser& operator=(const CLDataParser&) = delete;
    CLDataParser& operator=(CLDataParser&&) = default;

    virtual bool parse(int line, const std::string& data, interface::AttributeVariantData& value, std::string& message,
                       bool single_line_msg) override;
    virtual bool parse(int line, const std::string& data, std::string& message, bool single_line_msg) override;

private:
    bool parse(int line, const std::string& data, std::vector<interface::AttributeVariant>& value, std::string& message,
               bool single_line_msg);

    void build_symbols();

    bool simple_parse(int line, const std::string& data, std::vector<interface::AttributeVariant>& value,
                      std::string& message, bool single_line_msg);

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#endif
    const std::vector<std::string> allowed_operations{
        "K1X", "K1Y", "K1Z", "K2X", "K2Y", "K2Z", "K3X", "K3Y", "K3Z",
        "P01", "P02", "P03", "P04", "P05", "P06", "P07", "P1X", "P1Y",
    };
    word_symbols sym;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

} // namespace cldata
} // namespace pp
