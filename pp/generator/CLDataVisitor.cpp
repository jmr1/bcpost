//#include "stdafx.h"

#include "CLDataVisitor.h"

#include <boost/variant.hpp>

#include "EndOfPathGenerator.h"
#include "GotoGenerator.h"
#include "SelectToolGenerator.h"
#include "TldataDrillGenerator.h"
#include "ToolPathGenerator.h"
#include "MsysGenerator.h"
#include "CycleOffGenerator.h"

namespace pp {
namespace fanuc {

bool CLDataVisitor::operator()(const interface::Nil& value) const
{
    return false;
}

bool CLDataVisitor::operator()(const interface::Goto& value) const
{
    generated.emplace_back(generate_goto(line, step, value, precision));
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

} // namespace fanuc
} // namespace pp
