//#include "stdafx.h"

#include "CLDataParserTest.h"

#include <boost/type_index.hpp>
#include <iostream>
#include <string>

#include "CLDataAttributesVisitor.h"
#include "parser/CLDataParser.h"

namespace cldata_test {

CPPUNIT_TEST_SUITE_REGISTRATION(CLDataParserTest);

void CLDataParserTest::setUp()
{
}

void CLDataParserTest::tearDown()
{
}

static void verify(std::string&& data, std::vector<pp::interface::AttributeVariant>&& av_expected, bool ret_expected)
{
    using namespace pp::cldata;
    using namespace pp::interface;

    std::string         message;
    CLDataAttributeData av;

    CLDataParser pp;
    auto         ret = pp.parse(1, data, av, message, true);
    std::cout << message << std::endl;
    if (ret)
        CPPUNIT_ASSERT_EQUAL_MESSAGE("parse(): returned true but it contains error message", true, message.empty());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("parse(): ret value not equal", ret_expected, ret);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("parse(): Number of elements in the container not equal", av_expected.size(),
                                 av.value.size());

    for (size_t x = 0; x < av.value.size(); ++x)
        CPPUNIT_ASSERT(boost::apply_visitor(CLDataAttributesVisitor(av_expected[x]), av.value[x]));
}

void CLDataParserTest::gotoTest()
{
    using namespace pp::interface;

    verify("GOTO/-24.5855,-115.0000,100.0000,0.0000000,0.0000000,1.0000000",
           {Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("1"), '.', std::string("0000000")}}},
           true);

    verify("GOTO / -24.5855 , -115.0000,100.0000,\t 0.0000000 ,0.0000000 ",
           {Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")}}},
           true);

    verify("GOTO/-24.5855,-115.0000,100.0000",
           {Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.', std::string("0000")}}},
           true);

    verify("GOTO/-24.5855,-115.0000,100.",
           {Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100"), '.'}}},
           true);

    verify("GOTO/-24.5855,-115.0000,100",
           {Goto{FloatValue{'-', std::string("24"), '.', std::string("5855")},
                 FloatValue{'-', std::string("115"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("100")}}},
           true);

    verify("GOTO/-24.5855,-115.0000", {}, false);
    verify("GOTO-24.5855,-115.0000,100", {}, false);
    verify("GOT/-24.5855,-115.0000,100", {}, false);
    verify("GOTO/-24.5855,-115 .0000,100", {}, false);
    verify("GOTO/-24.5855,- 115.0000,100", {}, false);
    verify("GOTO/-24.5855,-115. 0000,100", {}, false);
    verify("GOTO/-24.5855,-1 15.0000,100", {}, false);
}

void CLDataParserTest::circleTest()
{
    using namespace pp::interface;

    verify("CIRCLE/206.4575,-30.0000,0.0000,0.0000000,0.0000000,1.0000000,30.0000,0.0600,0.5000,30.0000,0.0000",
           {Circle{FloatValue{boost::none, std::string("206"), '.', std::string("4575")},
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
           true);
}

void CLDataParserTest::ignoredValueTest()
{
    using namespace pp::interface;

    verify("$$ centerline data", {Ignored{}}, true);

    verify("PAINT/PATH", {Ignored{}}, true);
    verify("PAINT/SPEED,10", {Ignored{}}, true);
    verify("PANT/PATH", {}, false);
}

void CLDataParserTest::endOfPathTest()
{
    using namespace pp::interface;

    verify("END-OF-PATH", {EndOfPath{}}, true);
    verify("END-OFPATH", {}, false);
}

void CLDataParserTest::toolPathTest()
{
    using namespace pp::interface;

    verify("TOOL PATH/DRILLING_1,TOOL,STD_DRILL_D10", {ToolPath{"DRILLING_1", "STD_DRILL_D10"}}, true);
    verify("TOOL PATH/DRILLING_1,TOOL,STD DRILL_D10", {}, false);
    verify("TOOL PATH/DRILLING 1,TOOL,STD_DRILL_D10", {}, false);
    verify("TOOL PATH/DRILLING_1,TOOL,STD_DRILL_D10,", {}, false);
    verify("TOOL PATH/DRILLING_1, TOOL, STD_DRILL_D10", {ToolPath{"DRILLING_1", "STD_DRILL_D10"}}, true);
    verify("TOOL  PATH / DRILLING_1, TOOL, STD_DRILL_D10 ", {ToolPath{"DRILLING_1", "STD_DRILL_D10"}}, true);
    verify("TOOL\tPATH/DRILLING_1, TOOL, STD_DRILL_D10", {ToolPath{"DRILLING_1", "STD_DRILL_D10"}}, true);
}

void CLDataParserTest::tldataDrillTest()
{
    using namespace pp::interface;

    verify("TLDATA/DRILL,MILL,10.0000,0.0000,80.0000,118.0000,35.0000",
           {TldataDrill{"MILL", FloatValue{boost::none, std::string("10"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("80"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("118"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("35"), '.', std::string("0000")}}},
           true);

    verify(" TLDATA / DRILL , MILL , 10.0000 , 0.0000 , 80.0000 , 118.0000 , 35.0000 ",
           {TldataDrill{"MILL", FloatValue{boost::none, std::string("10"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("80"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("118"), '.', std::string("0000")},
                        FloatValue{boost::none, std::string("35"), '.', std::string("0000")}}},
           true);

    verify("TLDATA/DRILL,MILL,10.0000,0.0000,80.0000,118.0000", {}, false);
    verify("TLDATA/DRILL,MILL,10.0000,0.0000,80.0000,118.0000,", {}, false);
}

void CLDataParserTest::tldataMillTest()
{
    using namespace pp::interface;

    verify("TLDATA/MILL,10.0000,0.0000,80.0000,118.0000,35.0000",
           {TldataMill{FloatValue{boost::none, std::string("10"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("80"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("118"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("35"), '.', std::string("0000")}}},
           true);

    verify("TLDATA/MILL,10.0000,0.0000,80.0000,118.0000,35.0000,10.0000,0.0000,80.0000,118.0000,35.0000",
           {TldataMill{FloatValue{boost::none, std::string("10"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("80"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("118"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("35"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("10"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("80"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("118"), '.', std::string("0000")},
                       FloatValue{boost::none, std::string("35"), '.', std::string("0000")}}},
           true);

    verify("TLDATA/MILL,10.0000,0.0000,80.0000,118.0000", {}, false);
}

void CLDataParserTest::loadToolTest()
{
    using namespace pp::interface;

    verify("LOAD/TOOL,5", {LoadTool{5}}, true);
    verify(" LOAD / TOOL , 5 ", {LoadTool{5}}, true);
    verify("LOAD/TOOL,5.2", {}, false);
    verify("LOAD/TOOL,", {}, false);
    verify("LOAD/TOOL,G", {}, false);
    verify("LOAD/TUOOL,", {}, false);
    verify("LOAUD/TOOL,", {}, false);

    verify("LOAD/TOOL,4,ADJUST,1", {LoadTool{4, 1}}, true);
}

void CLDataParserTest::selectToolTest()
{
    using namespace pp::interface;

    verify("SELECT/TOOL,5", {SelectTool{5}}, true);
    verify(" SELECT / TOOL , 5 ", {SelectTool{5}}, true);
    verify("SELECT/TOOL,5.2", {}, false);
    verify("SELECT/TOOL,", {}, false);
    verify("SELECT/TOOL,G", {}, false);
    verify("SELECT/TUOOL,", {}, false);
    verify("LOAUD/TOOL,", {}, false);
}

void CLDataParserTest::msysTest()
{
    using namespace pp::interface;

    verify("MSYS/0.0000,0.0000,180.0000,0.5000000,0.0000000,0.8660254,0.8660254,0.0000000,-0.5000000",
           {Msys{FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("180"), '.', std::string("0000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("5000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("8660254")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("8660254")},
                 FloatValue{boost::none, std::string("0"), '.', std::string("0000000")},
                 FloatValue{'-', std::string("0"), '.', std::string("5000000")}}},
           true);
}

void CLDataParserTest::cycleOffTest()
{
    using namespace pp::interface;

    verify("CYCLE/OFF", {CycleOff{}}, true);
    verify(" CYCLE / OFF ", {CycleOff{}}, true);
    verify("CYCLE OFF", {}, false);
}

void CLDataParserTest::cycleDrillTest()
{
    using namespace pp::interface;

    verify("CYCLE/DRILL,RAPTO,3.0000,FEDTO,-33.0043,RTRCTO,AUTO,MMPM,250.0000",
           {CycleDrill{FloatValue{boost::none, std::string("3"), '.', std::string("0000")},
                       FloatValue{'-', std::string("33"), '.', std::string("0043")}, boost::none, RetractionType::AUTO,
                       FedrateType::MMPM, FloatValue{boost::none, std::string("250"), '.', std::string("0000")}}},
           true);

    verify("CYCLE/DRILL,RAPTO,3.0000,FEDTO,-33.0043,RTRCTO,4.0000,MANUAL,IPR,250.0000",
           {CycleDrill{FloatValue{boost::none, std::string("3"), '.', std::string("0000")},
                       FloatValue{'-', std::string("33"), '.', std::string("0043")},
                       FloatValue{boost::none, std::string("4"), '.', std::string("0000")}, RetractionType::MANUAL,
                       FedrateType::IPR, FloatValue{boost::none, std::string("250"), '.', std::string("0000")}}},
           true);

    verify("CYCLE/DRILL,RAPTO,3.0000,FEDTO,-33.0043,AUTO,MMPM,250.0000",
           {CycleDrill{FloatValue{boost::none, std::string("3"), '.', std::string("0000")},
                       FloatValue{'-', std::string("33"), '.', std::string("0043")}, boost::none, RetractionType::AUTO,
                       FedrateType::MMPM, FloatValue{boost::none, std::string("250"), '.', std::string("0000")}}},
           true);

    verify("CYCLE/DRILL,RAPTO,3.0000,FEDTO,-33.0043,RTRCTO,WRONG,MMPM,250.0000", {}, false);
    verify("CYCLE/DRILL,RAPTO,3.0000,FEDTO,-33.0043,RTRCTO,AUTO,WRONG,250.0000", {}, false);
}

void CLDataParserTest::fedratTest()
{
    using namespace pp::interface;

    verify("FEDRAT/MMPM,250.0000",
           {Fedrat{FedrateType::MMPM, FloatValue{boost::none, std::string("250"), '.', std::string("0000")}}}, true);
}

void CLDataParserTest::spindlRpmTest()
{
    using namespace pp::interface;

    verify("SPINDL/RPM,800,CLW", {SpindlRpm{FloatValue{boost::none, std::string("800")}, RotationDirection::CLW}},
           true);

    verify("SPINDL/RPM,600,CCLW", {SpindlRpm{FloatValue{boost::none, std::string("600")}, RotationDirection::CCLW}},
           true);

    verify("SPINDL/RPM,800,WRONG", {}, false);
}

void CLDataParserTest::rapidTest()
{
    using namespace pp::interface;

    verify("RAPID", {Rapid{}}, true);
    verify("RAPI", {}, false);
}

void CLDataParserTest::cutcomTest()
{
    using namespace pp::interface;

    verify("CUTCOM/RIGHT,1", {Cutcom{CutterCompensation::RIGHT, 1}}, true);
    verify("CUTCOM/LEFT,3", {Cutcom{CutterCompensation::LEFT, 3}}, true);
    verify("CUTCOM/OFF", {Cutcom{CutterCompensation::OFF}}, true);
    verify("CUTCOM/ON", {Cutcom{CutterCompensation::ON}}, true);
}

} // namespace cldata_test
