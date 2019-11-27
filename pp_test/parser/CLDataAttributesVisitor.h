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
    bool operator()(const interface::Ignored& value) const;
    bool operator()(const interface::ToolPath& value) const;
    bool operator()(const interface::TldataDrill& value) const;
    bool operator()(const interface::LoadTool& value) const;
    bool operator()(const interface::SelectTool& value) const;
    bool operator()(const interface::Msys& value) const;

private:
    const interface::AttributeVariant& v_expected;
};

} // namespace cldata_test
