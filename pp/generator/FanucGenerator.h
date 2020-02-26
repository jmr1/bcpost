#pragma once

#include "pp_export.h"

#include <string>
#include <vector>

#include "FanucParams.h"
#include "GeneratorBase.h"
#include "GeneratorData.h"
#include "interface/CLData.h"
#include "interface/GeneralDefines.h"

namespace pp {
namespace fanuc {

class PARSER_API FanucGenerator : public GeneratorBase
{
public:
    FanucGenerator(uint32_t step, uint32_t precision)
        : step(step)
        , precision(precision)
    {
    }

    virtual ~FanucGenerator()             = default;
    FanucGenerator(const FanucGenerator&) = delete;
    FanucGenerator(FanucGenerator&&)      = default;
    FanucGenerator& operator=(const FanucGenerator&) = delete;
    FanucGenerator& operator=(FanucGenerator&&) = default;

    virtual bool generate(uint32_t& line, const interface::AttributeVariantData& value,
                          std::vector<std::string>& generated, std::string& message, bool single_line_msg) override;

private:
    bool generate(uint32_t& line, const std::vector<interface::AttributeVariant>& value,
                  std::vector<std::string>& generated, std::string& message, bool single_line_msg);

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#endif
    GeneratorData data{};
    FanucParams   fanuc_params{};
    uint32_t      step;
    uint32_t      precision;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

} // namespace fanuc
} // namespace pp
