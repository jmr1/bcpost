#pragma once

#include "pp_export.h"

#include <string>
#include <vector>

#include "ParserBase.h"
#include "interface/CLData.h"
#include "interface/GeneralDefines.h"

namespace pp {
namespace cldata {

class PARSER_API CLDataParser : public ParserBase
{
public:
    CLDataParser()                    = default;
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

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

} // namespace cldata
} // namespace pp
