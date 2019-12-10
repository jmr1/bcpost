//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "FloatValueGenerator.h"

#include <string>

#include "interface/CLData.h"

namespace pp {
namespace interface {

float_rounder::float_rounder(uint32_t precision)
    : precision(precision)
{
}

void float_rounder::exec(std::string& value) const
{
    std::string tmp = value;
    if (tmp.size() > precision)
        tmp = tmp.substr(0, precision);
    auto ret = std::find_if(tmp.rbegin(), tmp.rend(), [](const auto& v) { return v != '0' ? true : false; });
    if (ret != tmp.rbegin())
        tmp.erase(ret.base(), tmp.end());
    value = tmp;
}

} // namespace interface

namespace fanuc {

#ifdef THROW_WHEN_ERROR

bool verify_throw(const interface::FloatValue& value)
{
    if (!value.sign && !value.value && !value.dot && !value.value2)
        throw float_value_exception("Brak wartości.");
    return true;
}

#else

bool verify(const interface::FloatValue& value)
{
    if (!value.sign && !value.value && !value.dot && !value.value2)
        return false;
    if (!value.dot && value.value2)
        return false;
    return true;
}

#endif

std::string generate_floatValue(const interface::FloatValue& value, uint32_t precision)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_floatValue(sink, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp
