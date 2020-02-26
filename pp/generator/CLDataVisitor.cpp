//#include "stdafx.h"

#include "CLDataVisitor.h"

#include <boost/variant.hpp>

#include "CircleGenerator.h"
#include "CutcomGenerator.h"
#include "CycleOffGenerator.h"
#include "EndOfPathGenerator.h"
#include "FedratGenerator.h"
#include "GotoGenerator.h"
#include "LoadToolGenerator.h"
#include "MsysGenerator.h"
#include "RapidGenerator.h"
#include "SpindlRpmGenerator.h"
#include "TldataDrillGenerator.h"
#include "TldataMillGenerator.h"
#include "ToolPathGenerator.h"

namespace pp {
namespace fanuc {

bool CLDataVisitor::operator()(const interface::Nil& value) const
{
    return false;
}

bool CLDataVisitor::operator()(const interface::Goto& value) const
{
    generated.emplace_back(
        generate_goto(data, line, step, value, precision, fanuc_params.in_cycle, fanuc_params.first_goto_in_cycle));
    fanuc_params.first_goto_in_cycle = false;
    return true;
}

bool CLDataVisitor::operator()(const interface::Circle& value) const
{
    generated.emplace_back(generate_circle(line, step, value, precision));
    return true;
}

bool CLDataVisitor::operator()(const interface::EndOfPath& value) const
{
    generated.emplace_back(generate_endOfPath(line, step));
    return true;
}

bool CLDataVisitor::operator()(const interface::Ignored& value) const
{
    return true;
}

bool CLDataVisitor::operator()(const interface::ToolPath& value) const
{
    generated.emplace_back(generate_toolPath(line, step, value));
    return true;
}

bool CLDataVisitor::operator()(const interface::TldataDrill& value) const
{
    generated.emplace_back(generate_tldataDrill(line, step, value, precision));
    fanuc_params.was_G0 = true;
    return true;
}
bool CLDataVisitor::operator()(const interface::TldataMill& value) const
{
    generated.emplace_back(generate_tldataMill(line, step, value, precision));
    fanuc_params.was_G0 = true;
    return true;
}

bool CLDataVisitor::operator()(const interface::LoadTool& value) const
{
    generated.emplace_back(generate_loadTool(line, step, value));
    return true;
}

bool CLDataVisitor::operator()(const interface::SelectTool& value) const
{
    return true;
}

bool CLDataVisitor::operator()(const interface::Msys& value) const
{
    generated.emplace_back(generate_msys(line, step, value, precision));
    return true;
}

bool CLDataVisitor::operator()(const interface::CycleOff& value) const
{
    fanuc_params.in_cycle            = false;
    fanuc_params.first_goto_in_cycle = false;
    generated.emplace_back(generate_cycleOff(line, step));
    return true;
}

bool CLDataVisitor::operator()(const interface::CycleDrill& value) const
{
    fanuc_params.in_cycle            = true;
    fanuc_params.first_goto_in_cycle = true;
    data.rapto                       = value.rapto;
    data.fedrate                     = value.fedrate;
    return true;
}

bool CLDataVisitor::operator()(const interface::Fedrat& value) const
{
    generated.emplace_back(generate_fedrat(line, step, value, precision));
    return true;
}

bool CLDataVisitor::operator()(const interface::SpindlRpm& value) const
{
    generated.emplace_back(generate_spindlRpm(line, step, value, precision));
    return true;
}

bool CLDataVisitor::operator()(const interface::Rapid& value) const
{
    if (!fanuc_params.was_G0)
    {
        generated.emplace_back(generate_rapid(line, step));
        fanuc_params.was_G0 = true;
    }
    return true;
}

bool CLDataVisitor::operator()(const interface::Cutcom& value) const
{
    generated.emplace_back(generate_cutcom(line, step, value, precision));
    return true;
}

} // namespace fanuc
} // namespace pp
