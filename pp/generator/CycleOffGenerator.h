#pragma once

#include <boost/spirit/include/karma.hpp>

#include "interface/CLData.h"

namespace pp {
namespace fanuc {

std::string generate_cycleOff(uint32_t& line, uint32_t step);

} // namespace fanuc
} // namespace pp
