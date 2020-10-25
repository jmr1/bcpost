//#include "stdafx.h"

#include <iostream>

#include "CLDataAttributesVisitor.h"

#include <boost/optional/optional_io.hpp>
#include <boost/variant.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace pp {
namespace interface {

std::ostream& operator<<(std::ostream& ostr, const FloatValue& v)
{
    ostr << "FloatValue["
         << "sign" << v.sign << " value:" << v.value << " dot:" << v.dot << " value2:" << v.value2 << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const Nil& v)
{
    ostr << "Nil[]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const Goto& v)
{
    ostr << "Goto[x:" << v.x << " y:" << v.y << " z:" << v.z << " i:" << v.i << " j:" << v.j << " k:" << v.k << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const Circle& v)
{
    ostr << "Circle[x:" << v.x << " y:" << v.y << " z:" << v.z << " i:" << v.i << " j:" << v.j << " k:" << v.k
         << " r:" << v.r << " t:" << v.t << " f:" << v.f << " d:" << v.d << " e:" << v.e << " n:" << v.n << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const EndOfPath& v)
{
    ostr << "EndOfPath[]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const Ignored& v)
{
    ostr << "Ignored[]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const ToolPath& v)
{
    ostr << "ToolPath[operation_name:" << v.operation_name << " tool_name:" << v.tool_name << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const TldataDrill& v)
{
    ostr << "TldataDrill[module_type:" << v.module_type << " diameter:" << v.diameter
         << " corner_radius:" << v.corner_radius << " length:" << v.length << " point_angle:" << v.point_angle
         << " flute_length:" << v.flute_length << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const TldataMill& v)
{
    ostr << "TldataMill[diameter:" << v.diameter << " lower_radius:" << v.lower_radius << " length:" << v.length
         << " taper_angle:" << v.taper_angle << " tip_angle:" << v.tip_angle << " x_center_r1:" << v.x_center_r1
         << " y_center_r1:" << v.y_center_r1 << " upper_radius:" << v.upper_radius << " x_center_r2:" << v.x_center_r2
         << " y_center_r2:" << v.y_center_r2 << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const LoadTool& v)
{
    ostr << "LoadTool[tool_number:" << v.tool_number << " adjust:" << v.adjust << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const SelectTool& v)
{
    ostr << "SelectTool[tool_number:" << v.tool_number << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const Msys& v)
{
    ostr << "Msys[shift_x:" << v.shift_x << " shift_y:" << v.shift_y << " shift_z:" << v.shift_z
         << " col1_x:" << v.col1_x << " col1_y:" << v.col1_y << " col1_z:" << v.col1_z << " col2_x:" << v.col2_x
         << " col2_y:" << v.col2_y << " col2_z:" << v.col2_z << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const CycleDrill& v)
{
    ostr << "CycleDrill[rapto:" << v.rapto << " fedto:" << v.fedto << " rtrcto:" << v.rtrcto
         << " retraction_type:" << v.retraction_type << " fedrate_type:" << v.fedrate_type << " fedrate:" << v.fedrate
         << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const CycleOff& v)
{
    ostr << "CycleOff[]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const SpindlRpm& v)
{
    ostr << "SpindlRpm[rpm:" << v.rpm << " rotation_direction:" << v.rotation_direction << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const Rapid& v)
{
    ostr << "Rapid[]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const Cutcom& v)
{
    ostr << "Cutcom[cutter_compensation:" << v.cutter_compensation << " register_number:" << v.register_number << "]";
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const Fedrat& v)
{
    ostr << "Fedrat[fedrate_type:" << v.fedrate_type << " units_number:" << v.units_number << "]";
    return ostr;
}

} // namespace interface
} // namespace pp

namespace cldata_test {

struct CheckTypeVisitor : public boost::static_visitor<>
{
    template <typename T>
    void operator()(const T& value) const
    {
        std::cout << "Type: " << boost::typeindex::type_id<T>().pretty_name() << std::endl;
    }
};

MATCHER_P2(IsValueExpected, value_expected, v_expected, "Unsupported type")
{
    if (!value_expected)
    {
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
        return false;
    }

    return true;
}

void FloatValueComparer::operator()(const interface::FloatValue& value_expected, const interface::FloatValue& value)
{
    EXPECT_THAT(value_expected.sign, value.sign);
    EXPECT_THAT(value_expected.value, value.value);
    EXPECT_THAT(value_expected.dot, value.dot);
    EXPECT_THAT(value_expected.value2, value.value2);
}

void FloatValueComparer::operator()(const boost::optional<interface::FloatValue>& value_expected,
                                    const boost::optional<interface::FloatValue>& value)
{
    EXPECT_THAT(value_expected, value);
}

bool CLDataAttributesVisitor::operator()(const interface::Nil& value) const
{
    abort();
    return false;
}

bool CLDataAttributesVisitor::operator()(const interface::Goto& value) const
{
    auto value_expected = boost::get<interface::Goto>(&v_expected);
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

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
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

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

    EXPECT_THAT(value_expected->n, value.n);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::EndOfPath& value) const
{
    auto value_expected = boost::get<interface::EndOfPath>(&v_expected);
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::Ignored& value) const
{
    auto value_expected = boost::get<interface::Ignored>(&v_expected);
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::ToolPath& value) const
{
    auto value_expected = boost::get<interface::ToolPath>(&v_expected);
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

    EXPECT_EQ(value_expected->operation_name, value.operation_name);
    EXPECT_EQ(value_expected->tool_name, value.tool_name);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::TldataDrill& value) const
{
    auto value_expected = boost::get<interface::TldataDrill>(&v_expected);
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

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
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

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
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

    EXPECT_EQ(value_expected->tool_number, value.tool_number);
    EXPECT_THAT(value_expected->adjust, value.adjust);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::SelectTool& value) const
{
    auto value_expected = boost::get<interface::SelectTool>(&v_expected);
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

    EXPECT_EQ(value_expected->tool_number, value.tool_number);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::Msys& value) const
{
    auto value_expected = boost::get<interface::Msys>(&v_expected);
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

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
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::CycleDrill& value) const
{
    auto value_expected = boost::get<interface::CycleDrill>(&v_expected);
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

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
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

    EXPECT_EQ(value_expected->fedrate_type, value.fedrate_type);
    FloatValueComparer()(value_expected->units_number, value.units_number);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::SpindlRpm& value) const
{
    auto value_expected = boost::get<interface::SpindlRpm>(&v_expected);
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

    FloatValueComparer()(value_expected->rpm, value.rpm);
    EXPECT_EQ(value_expected->rotation_direction, value.rotation_direction);

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::Rapid& value) const
{
    auto value_expected = boost::get<interface::Rapid>(&v_expected);
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

    return true;
}

bool CLDataAttributesVisitor::operator()(const interface::Cutcom& value) const
{
    auto value_expected = boost::get<interface::Cutcom>(&v_expected);
    EXPECT_THAT(true, IsValueExpected(value_expected, v_expected));

    EXPECT_EQ(value_expected->cutter_compensation, value.cutter_compensation);
    EXPECT_THAT(value_expected->register_number, value.register_number);

    return true;
}

} // namespace cldata_test
