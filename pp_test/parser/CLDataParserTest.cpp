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
    CLDAtaAttributeData av;

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

void CLDataParserTest::ignoredValueTest()
{
    using namespace pp::interface;

    verify("$$ centerline data", {AttributeVariant{}}, true);

    verify("PAINT/PATH", {AttributeVariant{}}, true);
    verify("PAINT/SPEED,10", {AttributeVariant{}}, true);
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

} // namespace cldata_test
