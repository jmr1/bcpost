#pragma once

#include <boost/spirit/include/karma.hpp>

#include "GeneratorData.h"
#include "interface/CLData.h"

namespace pp {
namespace fanuc {

std::string generate_goto(GeneratorData& data, uint32_t& line, uint32_t step, const interface::Goto& value,
                          uint32_t precision, bool in_cycle, bool first_goto_in_cycle);

} // namespace fanuc
} // namespace pp
