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
    CPPUNIT_TEST(endOfPathTest);
    CPPUNIT_TEST(toolPathTest);
    CPPUNIT_TEST(tldataDrillTest);
    CPPUNIT_TEST(selectToolTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void gotoTest();
    void endOfPathTest();
    void toolPathTest();
    void tldataDrillTest();
    void selectToolTest();
};

} // namespace fanuc_test