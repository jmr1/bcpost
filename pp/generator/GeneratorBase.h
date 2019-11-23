#pragma once

#include "pp_export.h"

#include <string>

namespace pp {

namespace interface {
class AttributeVariantData;
}

class PARSER_API GeneratorBase
{
public:
    virtual ~GeneratorBase()
    {
    }

    virtual bool generate(int line, const interface::AttributeVariantData& value, std::string& generated,
                          std::string& message, bool single_line_msg) = 0;
};

} // namespace pp
