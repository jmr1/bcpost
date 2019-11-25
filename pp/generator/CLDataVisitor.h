#pragma once

#include <string>

#include "interface/CLData.h"

namespace pp {
namespace fanuc {

class CLDataVisitor : public boost::static_visitor<bool>
{
public:
    CLDataVisitor(uint32_t precision, std::vector<std::string>& generated)
        : generated(generated)
        , precision(precision)
    {
    }

    bool operator()(const interface::Goto& value) const;
    bool operator()(const interface::EndOfPath& value) const;
    bool operator()(const interface::ToolPath& value) const;
    bool operator()(const interface::TldataDrill& value) const;
    bool operator()(const interface::LoadTool& value) const;
    bool operator()(const interface::SelectTool& value) const;

private:
    std::vector<std::string>& generated;
    const uint32_t            precision;
};

} // namespace fanuc
} // namespace pp
