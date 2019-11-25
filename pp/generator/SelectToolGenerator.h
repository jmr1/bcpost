#pragma once

#include <boost/spirit/include/karma.hpp>

#include "interface/CLData.h"

namespace pp {
namespace fanuc {

std::string generate_selectTool(const interface::SelectTool& value);

} // namespace fanuc
} // namespace pp
