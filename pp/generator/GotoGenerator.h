#pragma once

#include <boost/spirit/include/karma.hpp>

#include "interface/CLData.h"

namespace pp {

struct GeneratorData;

namespace fanuc {

std::string generate_goto(GeneratorData& data, uint32_t& line, uint32_t step, const interface::Goto& value,
                          uint32_t precision, bool in_cycle, bool first_goto_in_cycle, bool was_goto);

} // namespace fanuc
} // namespace pp
