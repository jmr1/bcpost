//#include "stdafx.h"

#include "CLDataVisitor.h"

#include <boost/variant.hpp>

#include "EndOfPathGenerator.h"
#include "GotoGenerator.h"
#include "TldataDrillGenerator.h"
#include "ToolPathGenerator.h"
#include "SelectToolGenerator.h"

namespace pp {
namespace fanuc {

bool CLDataVisitor::operator()(const interface::Goto& value) const
{
    generated.emplace_back(generate_goto(value, precision));
    return true;
}

bool CLDataVisitor::operator()(const interface::EndOfPath& value) const
{
    generated.emplace_back(generate_endOfPath());
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
    generated.emplace_back(generate_selectTool(value));
    return true;
}

} // namespace fanuc
} // namespace pp
