﻿#pragma once

#include <boost/spirit/include/karma.hpp>

#include "GeneratorData.h"
#include "interface/CLData.h"

namespace pp {
namespace fanuc {

std::string generate_cycleDrill(GeneratorData& data, uint32_t& line, uint32_t step, const interface::CycleDrill& value,
                                uint32_t precision);

} // namespace fanuc
} // namespace pp