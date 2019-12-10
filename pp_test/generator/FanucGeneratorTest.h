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
    CPPUNIT_TEST(gotoInCircleTest);
    CPPUNIT_TEST(endOfPathTest);
    CPPUNIT_TEST(toolPathTest);
    CPPUNIT_TEST(tldataDrillTest);
    CPPUNIT_TEST(selectToolTest);
    CPPUNIT_TEST(msysTest);
    CPPUNIT_TEST(cycleOffTest);
    CPPUNIT_TEST(cycleDrillTest);
    CPPUNIT_TEST(spindlRpmTest);
    CPPUNIT_TEST(rapidTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void gotoTest();
    void gotoInCircleTest();
    void endOfPathTest();
    void toolPathTest();
    void tldataDrillTest();
    void selectToolTest();
    void msysTest();
    void cycleOffTest();
    void cycleDrillTest();
    void spindlRpmTest();
    void rapidTest();
};

} // namespace fanuc_test
