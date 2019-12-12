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
    CPPUNIT_TEST(loadToolTest);
    CPPUNIT_TEST(msysTest);
    CPPUNIT_TEST(cycleOffTest);
    CPPUNIT_TEST(cycleDrillTest);
    CPPUNIT_TEST(spindlRpmTest);
    CPPUNIT_TEST(rapidTest);
    CPPUNIT_TEST(cutcomTest);
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
    void loadToolTest();
    void msysTest();
    void cycleOffTest();
    void cycleDrillTest();
    void spindlRpmTest();
    void rapidTest();
    void cutcomTest();
};

} // namespace fanuc_test
