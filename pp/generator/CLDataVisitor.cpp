//#include "stdafx.h"

#include "CLDataVisitor.h"

#include <boost/variant.hpp>

#include "EndOfPathGenerator.h"
#include "GotoGenerator.h"

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
    abort();
    return "";
}

std::string CLDataVisitor::operator()(const interface::TldataDrill& value) const
{
    abort();
    return "";
}

} // namespace fanuc
} // namespace pp