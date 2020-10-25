//#include "stdafx.h"

#include <string>

#include <boost/type_index.hpp>
#include <gtest/gtest.h>

#include "CLDataAttributesVisitor.h"

namespace cldata_test {

TEST(FloatValueParserTest, operatorPlusTest)
{
    using namespace pp::interface;

    FloatValue fv1{'-', std::string("24"), '.', std::string("5855")};
    FloatValue fv2{'-', std::string("115"), '.', std::string("0000")};

    FloatValue fv3 = fv1 + fv2;

    FloatValueComparer()(FloatValue{'-', std::string("139"), '.', std::string("5855")}, fv3);
}

} // namespace cldata_test
