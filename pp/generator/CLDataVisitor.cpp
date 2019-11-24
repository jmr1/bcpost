//#include "stdafx.h"

#include "CLDataVisitor.h"

#include <boost/variant.hpp>

#include "EndOfPathGenerator.h"
#include "GotoGenerator.h"
#include "TldataDrillGenerator.h"
#include "ToolPathGenerator.h"

namespace pp {
namespace fanuc {

std::string CLDataVisitor::operator()(const interface::Goto& value) const
{
    return generate_goto(value, precision);
}

std::string CLDataVisitor::operator()(const interface::EndOfPath& value) const
{
    return generate_endOfPath();
}

std::string CLDataVisitor::operator()(const interface::ToolPath& value) const
{
    return generate_toolPath(value);
}

std::string CLDataVisitor::operator()(const interface::TldataDrill& value) const
{
    return generate_tldataDrill(value);
}

} // namespace fanuc
} // namespace pp