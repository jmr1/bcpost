//#include "stdafx.h"

#include <iostream>

#include "CLDataAttributesVisitor.h"

#include <boost/variant.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace cldata_test {

struct CheckTypeVisitor : public boost::static_visitor<>
{
    template <typename T>
    void operator()(const T& value) const
    {
        std::cout << "Type: " << boost::typeindex::type_id<T>().pretty_name() << std::endl;
    }
};

void FloatValueComparer::operator()(const interface::FloatValue& value_expected, const interface::FloatValue& value)
{
    if (value_expected.sign == boost::none)
        EXPECT_TRUE(value.sign == boost::none);
    else
        EXPECT_EQ(*value_expected.sign, *value.sign);

    if (value_expected.value == boost::none)
        EXPECT_TRUE(value.value == boost::none);
    else
        EXPECT_EQ(*value_expected.value, *value.value);

    if (value_expected.dot == boost::none)
        EXPECT_TRUE(value.dot == boost::none);
    else
        EXPECT_EQ(*value_expected.dot, *value.dot);

    if (value_expected.value2 == boost::none)
        EXPECT_TRUE(value.value2 == boost::none);
    else
        EXPECT_EQ(*value_expected.value2, *value.value2);
}

void FloatValueComparer::operator()(const boost::optional<interface::FloatValue>& value_expected,
                                    const boost::optional<interface::FloatValue>& value)
{
    if (value_expected == boost::none)
    {
        EXPECT_TRUE(value == boost::none);
    }
    else
    {
        EXPECT_TRUE(value != boost::none);
        operator()(*value_expected, *value);
    }
}

bool CLDataAttributesVisitor::operator()(const interface::Nil& value) const
{
    abort();
    return false;
}

bool CLDataAttributesVisitor::operator()(const interface::Goto& value) const
{
    auto value_expected = boost::get<interface::Goto>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    FloatValueComparer()(value_expected->x, value.x);
    FloatValueComparer()(value_expected->y, value.y);
    FloatValueComparer()(value_expected->z, value.z);
    FloatValueComparer()(value_expected->i, value.i);
    FloatValueComparer()(value_expected->j, value.j);
    FloatValueComparer()(value_expected->k, value.k);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::Circle& value) const
{
    auto value_expected = boost::get<interface::Circle>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    FloatValueComparer()(value_expected->x, value.x);
    FloatValueComparer()(value_expected->y, value.y);
    FloatValueComparer()(value_expected->z, value.z);
    FloatValueComparer()(value_expected->i, value.i);
    FloatValueComparer()(value_expected->j, value.j);
    FloatValueComparer()(value_expected->k, value.k);
    FloatValueComparer()(value_expected->r, value.r);
    FloatValueComparer()(value_expected->t, value.t);
    FloatValueComparer()(value_expected->f, value.f);
    FloatValueComparer()(value_expected->d, value.d);
    FloatValueComparer()(value_expected->e, value.e);

    if (value_expected->n == boost::none)
        EXPECT_TRUE(value.n == boost::none);
    else
        EXPECT_EQ(*value_expected->n, *value.n);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::EndOfPath& value) const
{
    auto value_expected = boost::get<interface::EndOfPath>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::Ignored& value) const
{
    auto value_expected = boost::get<interface::Ignored>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::ToolPath& value) const
{
    auto value_expected = boost::get<interface::ToolPath>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    EXPECT_EQ(value_expected->operation_name, value.operation_name);
    EXPECT_EQ(value_expected->tool_name, value.tool_name);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::TldataDrill& value) const
{
    auto value_expected = boost::get<interface::TldataDrill>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    EXPECT_EQ(value_expected->module_type, value.module_type);
    FloatValueComparer()(value_expected->corner_radius, value.corner_radius);
    FloatValueComparer()(value_expected->diameter, value.diameter);
    FloatValueComparer()(value_expected->flute_length, value.flute_length);
    FloatValueComparer()(value_expected->length, value.length);
    FloatValueComparer()(value_expected->point_angle, value.point_angle);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::TldataMill& value) const
{
    auto value_expected = boost::get<interface::TldataMill>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    FloatValueComparer()(value_expected->diameter, value.diameter);
    FloatValueComparer()(value_expected->lower_radius, value.lower_radius);
    FloatValueComparer()(value_expected->length, value.length);
    FloatValueComparer()(value_expected->taper_angle, value.taper_angle);
    FloatValueComparer()(value_expected->tip_angle, value.tip_angle);
    FloatValueComparer()(value_expected->x_center_r1, value.x_center_r1);
    FloatValueComparer()(value_expected->y_center_r1, value.y_center_r1);
    FloatValueComparer()(value_expected->upper_radius, value.upper_radius);
    FloatValueComparer()(value_expected->x_center_r2, value.x_center_r2);
    FloatValueComparer()(value_expected->y_center_r2, value.y_center_r2);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::LoadTool& value) const
{
    auto value_expected = boost::get<interface::LoadTool>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    EXPECT_EQ(value_expected->tool_number, value.tool_number);

    if (value_expected->adjust == boost::none)
        EXPECT_TRUE(value.adjust == boost::none);
    else
        EXPECT_EQ(*value_expected->adjust, *value.adjust);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::SelectTool& value) const
{
    auto value_expected = boost::get<interface::SelectTool>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    EXPECT_EQ(value_expected->tool_number, value.tool_number);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::Msys& value) const
{
    auto value_expected = boost::get<interface::Msys>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    FloatValueComparer()(value_expected->shift_x, value.shift_x);
    FloatValueComparer()(value_expected->shift_y, value.shift_y);
    FloatValueComparer()(value_expected->shift_z, value.shift_z);
    FloatValueComparer()(value_expected->col1_x, value.col1_x);
    FloatValueComparer()(value_expected->col1_y, value.col1_y);
    FloatValueComparer()(value_expected->col1_z, value.col1_z);
    FloatValueComparer()(value_expected->col2_x, value.col2_x);
    FloatValueComparer()(value_expected->col2_y, value.col2_y);
    FloatValueComparer()(value_expected->col2_z, value.col2_z);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::CycleOff& value) const
{
    auto value_expected = boost::get<interface::CycleOff>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::CycleDrill& value) const
{
    auto value_expected = boost::get<interface::CycleDrill>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    FloatValueComparer()(value_expected->rapto, value.rapto);
    FloatValueComparer()(value_expected->fedto, value.fedto);
    FloatValueComparer()(value_expected->rtrcto, value.rtrcto);
    EXPECT_EQ(value_expected->retraction_type, value.retraction_type);
    EXPECT_EQ(value_expected->fedrate_type, value.fedrate_type);
    FloatValueComparer()(value_expected->fedrate, value.fedrate);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::Fedrat& value) const
{
    auto value_expected = boost::get<interface::Fedrat>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    EXPECT_EQ(value_expected->fedrate_type, value.fedrate_type);
    FloatValueComparer()(value_expected->units_number, value.units_number);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::SpindlRpm& value) const
{
    auto value_expected = boost::get<interface::SpindlRpm>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    FloatValueComparer()(value_expected->rpm, value.rpm);
    EXPECT_EQ(value_expected->rotation_direction, value.rotation_direction);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::Rapid& value) const
{
    auto value_expected = boost::get<interface::Rapid>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::Cutcom& value) const
{
    auto value_expected = boost::get<interface::Cutcom>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    EXPECT_TRUE(value_expected);

    EXPECT_EQ(value_expected->cutter_compensation, value.cutter_compensation);

    if (value_expected->register_number == boost::none)
        EXPECT_TRUE(value.register_number == boost::none);
    else
        EXPECT_EQ(*value_expected->register_number, *value.register_number);

    return true;
}

} // namespace cldata_test
