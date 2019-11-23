#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace fanuc_test {

class FanucGeneratorTest : public CPPUNIT_NS::TestFixture
{
public:
    FanucGeneratorTest(){};

    CPPUNIT_TEST_SUITE(FanucGeneratorTest);
    CPPUNIT_TEST(gotoTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void gotoTest();
};

} // namespace fanuc_test
