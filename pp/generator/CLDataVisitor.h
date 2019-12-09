#pragma once

#include <string>

#include "GeneratorData.h"
#include "interface/CLData.h"

namespace pp {
namespace fanuc {

class CLDataVisitor : public boost::static_visitor<bool>
{
public:
    CLDataVisitor(GeneratorData& data, uint32_t& line, const uint32_t step, uint32_t precision, bool& was_G0,
                  bool& in_cycle, bool& first_goto_in_cycle, std::vector<std::string>& generated)
        : data(data)
        , generated(generated)
        , line(line)
        , step(step)
        , precision(precision)
        , was_G0(was_G0)
        , in_cycle(in_cycle)
        , first_goto_in_cycle(first_goto_in_cycle)
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
    bool operator()(const interface::CycleDrill& value) const;
    bool operator()(const interface::SpindlRpm& value) const;
    bool operator()(const interface::Rapid& value) const;

private:
    GeneratorData&            data;
    std::vector<std::string>& generated;
    uint32_t&                 line;
    const uint32_t            step;
    const uint32_t            precision;
    bool&                     was_G0;
    bool&                     in_cycle;
    bool&                     first_goto_in_cycle;
};

} // namespace fanuc
} // namespace pp
