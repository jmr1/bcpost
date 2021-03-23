#pragma once

#include <boost/spirit/include/qi.hpp>

#include "interface/CLData.h"

#include "PosIteratorType.h"

#include "CircleGrammar.h"
#include "CutcomGrammar.h"
#include "CycleDrillGrammar.h"
#include "CycleOffGrammar.h"
#include "EndOfPathGrammar.h"
#include "FedratGrammar.h"
#include "GotoGrammar.h"
#include "IgnoredValueGrammar.h"
#include "LoadToolGrammar.h"
#include "MsysGrammar.h"
#include "RapidGrammar.h"
#include "SelectToolGrammar.h"
#include "SpindlRpmGrammar.h"
#include "TldataDrillGrammar.h"
#include "TldataMillGrammar.h"
#include "ToolPathGrammar.h"

namespace qi = boost::spirit::qi;

namespace pp {
namespace cldata {

class all_attributes_grammar
    : public qi::grammar<pos_iterator_type, std::vector<interface::AttributeVariant>(), qi::blank_type>
{
public:
    explicit all_attributes_grammar(std::string& message);

private:
    goto_grammar                                                                            goto_rule;
    circle_grammar                                                                          circle_rule;
    fedrat_grammar                                                                          fedrat_rule;
    msys_grammar                                                                            msys_rule;
    rapid_grammar                                                                           rapid_rule;
    cycle_off_grammar                                                                       cycle_off_rule;
    cycle_drill_grammar                                                                     cycle_drill_rule;
    end_of_path_grammar                                                                     end_of_path_rule;
    ignored_value_grammar                                                                   ignored_rule;
    tool_path_grammar                                                                       tool_path_rule;
    load_tool_grammar                                                                       load_tool_rule;
    select_tool_grammar                                                                     select_tool_rule;
    tldata_drill_grammar                                                                    tldata_drill_rule;
    tldata_mill_grammar                                                                     tldata_mill_rule;
    spindl_rpm_grammar                                                                      spindl_rpm_rule;
    cutcom_grammar                                                                          cutcom_rule;
    qi::rule<pos_iterator_type, interface::AttributeVariant(), qi::blank_type>              line_attribute;
    qi::rule<pos_iterator_type, std::vector<interface::AttributeVariant>(), qi::blank_type> line_attribute_vec;
};

} // namespace cldata
} // namespace pp
