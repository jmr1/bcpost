//#include "stdafx.h"

#include "FanucGeneratorTest.h"

#include <iostream>
#include <string>

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

    const uint32_t           step      = 1;
    const uint32_t           precision = 3;
    uint32_t                 line      = 0;
    std::string              message;
    std::vector<std::string> data;
    CLDataAttributeData      cl_data;
    cl_data.value = std::move(av);

    FanucGenerator fg(step, precision);
    auto           ret = fg.generate(line, cl_data, data, message, true);
    std::cout << message << std::endl;
    if (ret)
        CPPUNIT_ASSERT_EQUAL_MESSAGE("generate(): returned true but it contains error message", true, message.empty());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("generate(): returned value not equal for", ret_expected, ret);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("generate(): returned generated string size not equal", data_expected.size(),
                                 data.size());
    for (size_t x = 0; x < data_expected.size(); ++x)
    {
        // for (size_t y = 0; y < data_expected[x].size(); ++y)
        //     CPPUNIT_ASSERT_EQUAL_MESSAGE("generate(): returned generated string not equal for character [" +
        //                                      std::to_string(y) + "]",
        //                                  data_expected[x][y], data[x][y]);
        // CPPUNIT_ASSERT_EQUAL_MESSAGE("generate(): returned generated string size not equal for string[" +
        //                                  std::to_string(x) + "]",
        //                              data_expected[x].size(), data[x].size());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("generate(): returned generated string not equal", data_expected[x], data[x]);
    }
}

void FanucGeneratorTest::gotoTest()
{
    using namespace pp::interface;

    verify({Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")}},
            Goto{FloatValue{'-', std::string("25"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")}},
            Goto{FloatValue{'-', std::string("25"), '.', std::string("5855")},
                 FloatValue{'-', std::string("116"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")}},
            Goto{FloatValue{'-', std::string("25"), '.', std::string("5855")},
                 FloatValue{'-', std::string("116"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("200"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")}}},
           {"N1 G94 G90 X-24.585 Y-115. Z100.", "N2 X-25.585", "N3 Y-116.", "N4 Z200."}, true);

    verify({Goto{FloatValue{'-', std::string("25"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")}}},
           {"N1 G94 G90 X-25.585 Y-115. Z100."}, true);

#ifdef THROW_WHEN_ERROR // an example of a test when exceptions are thrown
    verify({Goto{FloatValue{'-', std::string("26"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")}}},
           {}, false);
#else
    verify({Goto{FloatValue{'-', std::string("26"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")}}},
           {"N1 G94 G90 X-26.585 Y-115. Z<error>"}, true);
#endif

    verify({Goto{FloatValue{'-', std::string("27"), '.', std::string("5855")}}},
           {"N1 G94 G90 X-27.585 Y<error> Z<error>"}, true);

    verify({Goto{}}, {"N1 G94 G90 X<error> Y<error> Z<error>"}, true);

    verify({Goto{FloatValue{'-', std::string("28"), boost::none, std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")}}},
           {"N1 G94 G90 X<error> Y-115. Z100."}, true);

    verify({Goto{FloatValue{'-', boost::none, '.', std::string("5855")},
                 FloatValue{boost::none, boost::none, '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', boost::none}}},
           {"N1 G94 G90 X-.585 Y. Z100."}, true);
}

void FanucGeneratorTest::gotoInCircleTest()
{
    using namespace pp::interface;

    verify({Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")}},
            CycleDrill{FloatValue{boost::none, std::string("3"), '.', std::string("0000")},
                       FloatValue{'-', std::string("33"), '.', std::string("0043")}, boost::none, RetractionType::AUTO,
                       FedrateType::MMPM, FloatValue{boost::none, std::string("250"), '.', std::string("0000")}},
            Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")}},
            Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")}},
            CycleOff{},
            Goto{FloatValue{'-', std::string("25"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")}}},
           {"N1 G94 G90 X-24.585 Y-115. Z100.",
            "N2 G98 G81 X-24.585 Y-115. Z100. F250. R103.\n"
            "N3 G00 Z100.",
            "N4 G81 X-24.585 Y-115. Z100. F250. R103.\n"
            "N5 G00 Z100.",
            "N6 G80", "N7 X-25.585"},
           true);
}

void FanucGeneratorTest::circleTest()
{
    using namespace pp::interface;

    verify({Circle{FloatValue{boost::none, std::string("206"), '.', std::string("4575")},
                   FloatValue{'-', std::string("30"), '.', std::string("0000")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                   FloatValue{boost::none, std::string("1"), '.', std::string("0000000")},
                   FloatValue{boost::none, std::string("30"), '.', std::string("0000")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("0600")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("5000")},
                   FloatValue{boost::none, std::string("30"), '.', std::string("0000")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("0000")}}},
           {"N1 G2 X206.457 Y-30. I0. J0."}, true);

    verify({Circle{FloatValue{boost::none, std::string("206"), '.', std::string("4575")},
                   FloatValue{'-', std::string("30"), '.', std::string("0000")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                   FloatValue{'-', std::string("1"), '.', std::string("0000000")},
                   FloatValue{boost::none, std::string("30"), '.', std::string("0000")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("0600")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("5000")},
                   FloatValue{boost::none, std::string("30"), '.', std::string("0000")},
                   FloatValue{boost::none, std::string("0"), '.', std::string("0000")}}},
           {"N1 G3 X206.457 Y-30. I0. J0."}, true);
}

void FanucGeneratorTest::endOfPathTest()
{
    using namespace pp::interface;

    verify({EndOfPath{}},
           {"N1 G49 G21\n"
            "N2 G69\n"
            "N3 G91 G28 Z0.0\n"
            "N4 G91 G28 X0.0 Y0.0\n"
            "N5 G90 G53 G00 A0.0 C0.0\n"
            "N6 M05\n"
            "N7 M09\n"
            "N8 M30\n"
            "%"},
           true);
}

void FanucGeneratorTest::toolPathTest()
{
    using namespace pp::interface;

    verify({ToolPath{"DRILLING_1", "STD_DRILL_D10"}},
           {"%\n"
            "O0001\n"
            "N1 G40 G17 G90 G49 G21\n"
            "N2 (DRILLING_1)"},
           true);
}

void FanucGeneratorTest::tldataDrillTest()
{
    using namespace pp::interface;

    verify({TldataDrill{"MILL", FloatValue{boost::none, std::string("10"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("80"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("118"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("35"), '.', std::string("0000")}}},
           {"N1 G91 G28 Z0.0\n"
            "N2 G91 G28 X0.0 Y0.0\n"
            "N3 G90 G53 G00 A0.0 C0.0"},
           true);
}

void FanucGeneratorTest::tldataMillTest()
{
    using namespace pp::interface;

    verify({TldataMill{FloatValue{boost::none, std::string("10"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("80"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("118"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("35"), '.', std::string("0000")}}},
           {"N1 G91 G28 Z0.0\n"
            "N2 G91 G28 X0.0 Y0.0\n"
            "N3 G90 G54 G00 A0.0 C0.0"},
           true);
}

void FanucGeneratorTest::loadToolTest()
{
    using namespace pp::interface;

    verify({LoadTool{5}}, {":1 T5 M06"}, true);
    verify({LoadTool{5, 1}},
           {":1 T5 M06\n"
            "N2 G43 H1 Z100."},
           true);
}

void FanucGeneratorTest::msysTest()
{
    using namespace pp::interface;

    verify({Msys{FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("180"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("5000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("8660254")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("8660254")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("5000000")}}},
           {"N1 G97 G90 G54\n"
            "N2 G68.2 P1 X0. Y0. Z180. I90. J0. K60.\n"
            "N3 G53.1"},
           true);

    verify({Msys{FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("180"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")}}},
           {"N1 G97 G90 G54\n"
            "N2 G53.1"},
           true);
}

void FanucGeneratorTest::cycleOffTest()
{
    using namespace pp::interface;

    verify({CycleOff{}}, {"N1 G80"}, true);
}

void FanucGeneratorTest::cycleDrillTest()
{
    using namespace pp::interface;

    verify({CycleDrill{FloatValue{boost::none, std::string("3"), '.', std::string("0000")},
                       FloatValue{'-', std::string("33"), '.', std::string("0043")}, boost::none, RetractionType::AUTO,
                       FedrateType::MMPM, FloatValue{boost::none, std::string("250"), '.', std::string("0000")}}},
           {}, true);
}

void FanucGeneratorTest::spindlRpmTest()
{
    using namespace pp::interface;

    verify({SpindlRpm{FloatValue{boost::none, std::string("800")}, RotationDirection::CLW}}, {"N1 G43 H00 S800 M03"},
           true);

    verify({SpindlRpm{FloatValue{boost::none, std::string("700")}, RotationDirection::CCLW}}, {"N1 G43 H00 S700 M04"},
           true);
}

void FanucGeneratorTest::fedratTest()
{
    using namespace pp::interface;

    verify({Fedrat{FedrateType::MMPM, FloatValue{boost::none, std::string("250"), '.', std::string("0000")}}},
           {"N1 G94 F250."}, true);

    verify({Fedrat{FedrateType::MMPR, FloatValue{boost::none, std::string("250"), '.', std::string("0000")}}},
           {"N1 G95 F250."}, true);

    verify({Fedrat{FedrateType::IPM, FloatValue{boost::none, std::string("250"), '.', std::string("0000")}}},
           {"N1 G94 F250."}, true);

    verify({Fedrat{FedrateType::IPR, FloatValue{boost::none, std::string("250"), '.', std::string("0000")}}},
           {"N1 G95 F250."}, true);
}

void FanucGeneratorTest::rapidTest()
{
    using namespace pp::interface;

    verify({Rapid{}}, {"N1 G90 G53 G00 A0.0 C0.0"}, true);
}

void FanucGeneratorTest::cutcomTest()
{
    using namespace pp::interface;

    verify({Cutcom{CutterCompensation::LEFT, 4}}, {"N1 G41 D4"}, true);
    verify({Cutcom{CutterCompensation::RIGHT, 3}}, {"N1 G42 D3"}, true);
    verify({Cutcom{CutterCompensation::OFF}}, {"N1 G40"}, true);
}

} // namespace fanuc_test
