#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "interface/CLData.h"

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Msys,
    (auto, shift_x)
    (auto, shift_y)
    (auto, shift_z)
    (auto, col1_x)
    (auto, col1_y)
    (auto, col1_z)
    (auto, col2_x)
    (auto, col2_y)
    (auto, col2_z)
)

// clang-format on

