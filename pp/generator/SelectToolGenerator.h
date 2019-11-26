#pragma once

#include <boost/spirit/include/karma.hpp>

#include "interface/CLData.h"

namespace pp {
namespace fanuc {

std::string generate_selectTool(uint32_t& line, uint32_t step, const interface::SelectTool& value);

} // namespace fanuc
} // namespace pp
