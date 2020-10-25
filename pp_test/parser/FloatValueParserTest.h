#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace cldata_test {

class FloatValueParserTest : public CPPUNIT_NS::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(FloatValueParserTest);
    CPPUNIT_TEST(operatorPlusTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override;
    void tearDown() override;

protected:
    void operatorPlusTest();
};

} // namespace cldata_test
