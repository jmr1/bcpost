#pragma once

#include <boost/spirit/include/karma.hpp>

#include "interface/CLData.h"

namespace pp {
namespace fanuc {

std::string generate_goto(const interface::Goto& value, uint32_t precision);

} // namespace fanuc
} // namespace pp
