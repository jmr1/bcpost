#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "interface/CLData.h"

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::CycleDrill,
    (auto, rapto)
    (auto, fedto)
    (auto, rtrcto)
    (auto, retraction_type)
    (auto, fedrate_type)
    (auto, fedrate)
)

// clang-format on

