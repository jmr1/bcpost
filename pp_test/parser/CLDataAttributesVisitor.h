#pragma once

#include <string>
#include <vector>

#include "interface/CLData.h"

using namespace pp;

namespace cldata_test {

class CLDataAttributesVisitor : public boost::static_visitor<bool>
{
public:
    CLDataAttributesVisitor(const interface::AttributeVariant& expected)
        : v_expected(expected)
    {
    }

    bool operator()(const interface::Goto& value) const;
    bool operator()(const interface::EndOfPath& value) const;

private:
    const interface::AttributeVariant& v_expected;
};

} // namespace cldata_test
