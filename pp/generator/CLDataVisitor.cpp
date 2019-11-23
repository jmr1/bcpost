//#include "stdafx.h"

#include "CLDataVisitor.h"

#include <boost/variant.hpp>

#include "GotoGenerator.h"

namespace pp {
namespace fanuc {

std::string CLDataVisitor::operator()(const interface::Goto& value) const
{
    return generate_goto(value, precision);
}

} // namespace fanuc
} // namespace pp