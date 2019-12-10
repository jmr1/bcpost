#pragma once

#include <string>
#include <vector>

#include "interface/CLData.h"

using namespace pp;

namespace cldata_test {

struct FloatValueComparer
{
    void operator()(const interface::FloatValue& value_expected, const interface::FloatValue& value);

    void operator()(const boost::optional<interface::FloatValue>& value_expected,
                    const boost::optional<interface::FloatValue>& value);
};

class CLDataAttributesVisitor : public boost::static_visitor<bool>
{
public:
    CLDataAttributesVisitor(const interface::AttributeVariant& expected)
        : v_expected(expected)
    {
    }

    bool operator()(const interface::Nil& value) const;
    bool operator()(const interface::Goto& value) const;
    bool operator()(const interface::EndOfPath& value) const;
    bool operator()(const interface::Ignored& value) const;
    bool operator()(const interface::ToolPath& value) const;
    bool operator()(const interface::TldataDrill& value) const;
    bool operator()(const interface::LoadTool& value) const;
    bool operator()(const interface::SelectTool& value) const;
    bool operator()(const interface::Msys& value) const;
    bool operator()(const interface::CycleOff& value) const;
    bool operator()(const interface::CycleDrill& value) const;
    bool operator()(const interface::SpindlRpm& value) const;
    bool operator()(const interface::Rapid& value) const;

private:
    const interface::AttributeVariant& v_expected;
};

} // namespace cldata_test
