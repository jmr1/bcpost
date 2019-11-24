﻿#pragma once

#include <string>

#include <boost/optional/optional.hpp>
#include <boost/variant.hpp>

#include "GeneralDefines.h"

// Enable this if you want generator to throw an exception instead of just writing <error> text.
//#define THROW_WHEN_ERROR

namespace pp {
namespace interface {

struct FloatValue
{
    boost::optional<char>        sign;
    boost::optional<std::string> value;
    boost::optional<char>        dot;
    boost::optional<std::string> value2;
};

struct Goto
{
    FloatValue                  x;
    FloatValue                  y;
    FloatValue                  z;
    boost::optional<FloatValue> i;
    boost::optional<FloatValue> j;
    boost::optional<FloatValue> k;
};

struct EndOfPath
{
};

struct ToolPath
{
    std::string operation_name;
    std::string tool_name;
};

struct TldataDrill
{
    std::string module_type;
    double      diameter;
    double      corner_radius;
    double      length;
    double      point_angle;
    double      flute_length;
};

using AttributeVariant = boost::variant<Goto, EndOfPath, ToolPath, TldataDrill>;

struct CLDAtaAttributeData : public AttributeVariantData
{
    std::vector<AttributeVariant> value;
};

} // namespace interface
} // namespace pp
