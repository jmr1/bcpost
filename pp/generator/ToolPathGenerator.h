﻿#pragma once

#include <boost/spirit/include/karma.hpp>

#include "interface/CLData.h"

namespace pp {
namespace fanuc {

std::string generate_toolPath(const interface::ToolPath& value);

} // namespace fanuc
} // namespace pp
