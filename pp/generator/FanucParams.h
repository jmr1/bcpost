#pragma once

namespace pp {
namespace fanuc {

struct FanucParams
{
    bool was_G0{};
    bool in_cycle{};
    bool first_goto_in_cycle{};
};

} // namespace fanuc
} // namespace pp
