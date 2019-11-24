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
};

} // namespace cldata_test
