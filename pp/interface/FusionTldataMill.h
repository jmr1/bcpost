#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "interface/CLData.h"

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::TldataMill,
    (auto, diameter)
    (auto, lower_radius)
    (auto, length)
    (auto, taper_angle)
    (auto, tip_angle)
    (auto, x_center_r1)
    (auto, y_center_r1)
    (auto, upper_radius)
    (auto, x_center_r2)
    (auto, y_center_r2)
)

// clang-format on

