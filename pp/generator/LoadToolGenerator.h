#pragma once

#include <boost/spirit/include/karma.hpp>

#include "interface/CLData.h"

namespace pp {
namespace fanuc {

std::string generate_loadTool(uint32_t& line, uint32_t step, const interface::LoadTool& value);

} // namespace fanuc
} // namespace pp
