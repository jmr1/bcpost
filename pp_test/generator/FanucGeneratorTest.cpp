//#include "stdafx.h"

#include "FanucGeneratorTest.h"

//#include <boost/type_index.hpp>
#include <iostream>
#include <string>

//#include "CLDataAttributesVisitor.h"
#include "generator/FanucGenerator.h"

namespace fanuc_test {

CPPUNIT_TEST_SUITE_REGISTRATION(FanucGeneratorTest);

void FanucGeneratorTest::setUp()
{
}

void FanucGeneratorTest::tearDown()
{
}

static void verify(std::vector<pp::interface::AttributeVariant>&& av, std::vector<std::string>&& data_expected,
                   bool ret_expected)
{
    using namespace pp::fanuc;
    using namespace pp::interface;

    std::string              message;
    std::vector<std::string> data;
    CLDAtaAttributeData      cl_data;
    cl_data.value = std::move(av);

    FanucGenerator fg(3);
    auto           ret = fg.generate(1, cl_data, data, message, true);
    std::cout << message << std::endl;
    if (ret)
        CPPUNIT_ASSERT_EQUAL_MESSAGE("generate(): returned true but it contains error message", true, message.empty());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("generate(): returned value not equal for", ret_expected, ret);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("generate(): returned generated string size not equal", data_expected.size(),
                                 data.size());
    for (size_t x = 0; x < data_expected.size(); ++x)
        CPPUNIT_ASSERT_EQUAL_MESSAGE("generate(): returned generated string not equal", data_expected[x], data[x]);
}

void FanucGeneratorTest::gotoTest()
{
    using namespace pp::interface;

    verify({Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")}}},
           {"G94 G90 X-24.585 Y-115. Z100."}, true);

    verify({Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")}}},
           {"G94 G90 X-24.585 Y-115. Z100."}, true);

#ifdef THROW_WHEN_ERROR // an example of a test when exceptions are thrown
    verify({Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")}}},
           {}, false);
#else
    verify({Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")}}},
           {"G94 G90 X-24.585 Y-115. Z<error>"}, true);
#endif

    verify({Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")}}}, {"G94 G90 X-24.585 Y<error> Z<error>"},
           true);

    verify({Goto{}}, {"G94 G90 X<error> Y<error> Z<error>"}, true);

    verify({Goto{FloatValue{'-', std::string("24"), boost::none, std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")}}},
           {"G94 G90 X<error> Y-115. Z100."}, true);

    verify({Goto{FloatValue{'-', boost::none, '.', std::string("5855")},
                 FloatValue{boost::none, boost::none, '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', boost::none}}},
           {"G94 G90 X-.585 Y. Z100."}, true);
}

} // namespace fanuc_test
