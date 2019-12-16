#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "interface/CLData.h"

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::TldataDrill,
    (auto, module_type)
    (auto, diameter)
    (auto, corner_radius)
    (auto, length)
    (auto, point_angle)
    (auto, flute_length)
)

// clang-format on

