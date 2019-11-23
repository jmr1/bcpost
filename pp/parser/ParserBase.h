#pragma once

#include "pp_export.h"

#include <string>

namespace pp {

namespace interface {
class AttributeVariantData;
}

class PARSER_API ParserBase
{
public:
    virtual ~ParserBase()
    {
    }

    virtual bool parse(int line, const std::string& data, interface::AttributeVariantData& value, std::string& message,
                       bool single_line_msg)                                                          = 0;
    virtual bool parse(int line, const std::string& data, std::string& message, bool single_line_msg) = 0;
};

} // namespace pp
