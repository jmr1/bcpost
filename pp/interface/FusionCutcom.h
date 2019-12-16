#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "interface/CLData.h"

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Cutcom,
    (auto, cutter_compensation)
    (auto, register_number)
)

// clang-format on

