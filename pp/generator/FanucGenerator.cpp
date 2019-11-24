//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "FanucGenerator.h"
#include "CLDataVisitor.h"

namespace pp {
namespace fanuc {

bool FanucGenerator::generate(int line, const interface::AttributeVariantData& value,
                              std::vector<std::string>& generated, std::string& message, bool single_line_msg)
{
    return generate(line, static_cast<const interface::CLDAtaAttributeData&>(value).value, generated, message,
                    single_line_msg);
}

bool FanucGenerator::generate(int line, const std::vector<interface::AttributeVariant>& value,
                              std::vector<std::string>& generated, std::string& message, bool single_line_msg)
{
    try
    {
        for (size_t x = 0; x < value.size(); ++x)
            generated.emplace_back(boost::apply_visitor(CLDataVisitor(precision), value[x]));
    }
#ifdef THROW_WHEN_ERROR
    catch (const float_value_exception& e)
    {
        message = e.what();
        return false;
    }
#endif
    catch (const std::runtime_error& e)
    {
        message = e.what();
        return false;
    }
    catch (const std::out_of_range& e)
    {
        message = e.what();
        return false;
    }

    return true;
}

} // namespace fanuc
} // namespace pp
