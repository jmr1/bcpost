#pragma once

#include <boost/optional/optional.hpp>

#include "interface/CLData.h"

namespace pp {

struct GeneratorData
{
    boost::optional<interface::FloatValue> x;
    boost::optional<interface::FloatValue> y;
    boost::optional<interface::FloatValue> z;
};

} // namespace pp
