#pragma once

#include <string>

#include "interface/CLData.h"

namespace pp {
namespace fanuc {

class CLDataVisitor : public boost::static_visitor<bool>
{
public:
    CLDataVisitor(uint32_t& line, const uint32_t step, uint32_t precision, std::vector<std::string>& generated)
        : generated(generated)
        , line(line)
        , step(step)
        , precision(precision)
    {
    }

    bool operator()(const interface::Nil& value) const;
    bool operator()(const interface::Goto& value) const;
    bool operator()(const interface::EndOfPath& value) const;
    bool operator()(const interface::Ignored& value) const;
    bool operator()(const interface::ToolPath& value) const;
    bool operator()(const interface::TldataDrill& value) const;
    bool operator()(const interface::LoadTool& value) const;
    bool operator()(const interface::SelectTool& value) const;
    bool operator()(const interface::Msys& value) const;
    bool operator()(const interface::CycleOff& value) const;

private:
    std::vector<std::string>& generated;
    uint32_t&                 line;
    const uint32_t            step;
    const uint32_t            precision;
};

} // namespace fanuc
} // namespace pp
