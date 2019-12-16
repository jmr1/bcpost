#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "interface/CLData.h"

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Circle,
    (auto, x)
    (auto, y)
    (auto, z)
    (auto, i)
    (auto, j)
    (auto, k)
    (auto, r)
    (auto, t)
    (auto, f)
    (auto, d)
    (auto, e)
    (auto, n)
)

// clang-format on

