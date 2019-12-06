//#include "stdafx.h"

#include "CLDataVisitor.h"

#include <boost/variant.hpp>

#include "CycleDrillGenerator.h"
#include "CycleOffGenerator.h"
#include "EndOfPathGenerator.h"
#include "GotoGenerator.h"
#include "MsysGenerator.h"
#include "RapidGenerator.h"
#include "SelectToolGenerator.h"
#include "SpindlRpmGenerator.h"
#include "TldataDrillGenerator.h"
#include "ToolPathGenerator.h"

namespace pp {
namespace fanuc {

bool CLDataVisitor::operator()(const interface::Nil& value) const
{
    return false;
}

bool CLDataVisitor::operator()(const interface::Goto& value) const
{
    generated.emplace_back(generate_goto(data, line, step, value, precision));
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
    return true;
}

bool CLDataVisitor::operator()(const interface::LoadTool& value) const
{
    return true;
}

bool CLDataVisitor::operator()(const interface::SelectTool& value) const
{
    generated.emplace_back(generate_selectTool(line, step, value));
    return true;
}

bool CLDataVisitor::operator()(const interface::Msys& value) const
{
    generated.emplace_back(generate_msys(line, step, value, precision));
    return true;
}

bool CLDataVisitor::operator()(const interface::CycleOff& value) const
{
    generated.emplace_back(generate_cycleOff(line, step));
    return true;
}

bool CLDataVisitor::operator()(const interface::CycleDrill& value) const
{
    generated.emplace_back(generate_cycleDrill(data, line, step, value, precision));
    return true;
}

bool CLDataVisitor::operator()(const interface::SpindlRpm& value) const
{
    generated.emplace_back(generate_spindlRpm(line, step, value, precision));
    return true;
}

bool CLDataVisitor::operator()(const interface::Rapid& value) const
{
    generated.emplace_back(generate_rapid(line, step));
    return true;
}

} // namespace fanuc
} // namespace pp
