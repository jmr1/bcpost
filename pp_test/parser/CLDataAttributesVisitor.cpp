//#include "stdafx.h"

#include <iostream>

#include "CLDataAttributesVisitor.h"

#include <boost/variant.hpp>
#include <cppunit/TestAssert.h>

namespace cldata_test {

struct CheckTypeVisitor : public boost::static_visitor<>
{
    template <typename T>
    void operator()(const T& value) const
    {
        std::cout << "Type: " << boost::typeindex::type_id<T>().pretty_name() << std::endl;
    }
};

struct FloatValueComparer
{
    void operator()(const interface::FloatValue& value_expected, const interface::FloatValue& value)
    {
        if (value_expected.sign == boost::none)
            CPPUNIT_ASSERT(value.sign == boost::none);
        else
            CPPUNIT_ASSERT_EQUAL(*value_expected.sign, *value.sign);

        if (value_expected.value == boost::none)
            CPPUNIT_ASSERT(value.value == boost::none);
        else
            CPPUNIT_ASSERT_EQUAL(*value_expected.value, *value.value);

        if (value_expected.dot == boost::none)
            CPPUNIT_ASSERT(value.dot == boost::none);
        else
            CPPUNIT_ASSERT_EQUAL(*value_expected.dot, *value.dot);

        if (value_expected.value2 == boost::none)
            CPPUNIT_ASSERT(value.value2 == boost::none);
        else
            CPPUNIT_ASSERT_EQUAL(*value_expected.value2, *value.value2);
    }

    void operator()(const boost::optional<interface::FloatValue>& value_expected,
                    const boost::optional<interface::FloatValue>& value)
    {
        if (value_expected == boost::none)
        {
            CPPUNIT_ASSERT(value == boost::none);
        }
        else
        {
            CPPUNIT_ASSERT(value != boost::none);
            operator()(*value_expected, *value);
        }
    }
};

bool CLDataAttributesVisitor::operator()(const interface::Goto& value) const
{
    auto value_expected = boost::get<interface::Goto>(&v_expected);
    if (!value_expected)
        boost::apply_visitor(CheckTypeVisitor(), v_expected);
    CPPUNIT_ASSERT(value_expected);

    FloatValueComparer()(value_expected->x, value.x);
    FloatValueComparer()(value_expected->y, value.y);
    FloatValueComparer()(value_expected->z, value.z);
    FloatValueComparer()(value_expected->i, value.i);
    FloatValueComparer()(value_expected->j, value.j);
    FloatValueComparer()(value_expected->k, value.k);

    return true;
}

} // namespace cldata_test
