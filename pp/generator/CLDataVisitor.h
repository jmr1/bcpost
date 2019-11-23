#pragma once

#include <string>

#include "interface/CLData.h"

namespace pp {
namespace fanuc {

class CLDataVisitor : public boost::static_visitor<std::string>
{
public:
    CLDataVisitor(uint32_t precision)
        : precision(precision)
    {
    }

    std::string operator()(const interface::Goto& value) const;

private:
    const uint32_t precision;
};

} // namespace fanuc
} // namespace pp
