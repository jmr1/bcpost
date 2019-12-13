#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace cldata_test {

class CLDataParserTest : public CPPUNIT_NS::TestFixture
{
public:
    CLDataParserTest(){};

    CPPUNIT_TEST_SUITE(CLDataParserTest);
    CPPUNIT_TEST(gotoTest);
    CPPUNIT_TEST(ignoredValueTest);
    CPPUNIT_TEST(endOfPathTest);
    CPPUNIT_TEST(toolPathTest);
    CPPUNIT_TEST(tldataDrillTest);
    CPPUNIT_TEST(tldataMillTest);
    CPPUNIT_TEST(loadToolTest);
    CPPUNIT_TEST(selectToolTest);
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
    void ignoredValueTest();
    void endOfPathTest();
    void toolPathTest();
    void tldataDrillTest();
    void tldataMillTest();
    void loadToolTest();
    void selectToolTest();
    void msysTest();
    void cycleOffTest();
    void cycleDrillTest();
    void spindlRpmTest();
    void rapidTest();
    void cutcomTest();
};

} // namespace cldata_test
