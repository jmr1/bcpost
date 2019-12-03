//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "SelectToolGenerator.h"

#include <iomanip>
#include <string>

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp> // construct
#include <boost/spirit/include/phoenix_operator.hpp>
//#include <boost/phoenix/object/dynamic_cast.hpp>
//#include <boost/phoenix/operator/self.hpp>

#include "interface/CLData.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::SelectTool,
    (int, tool_number)
)

// clang-format on

namespace pp {
namespace fanuc {

template <typename Iterator>
class select_tool_grammar : public karma::grammar<Iterator, interface::SelectTool()>
{
public:
    select_tool_grammar(uint32_t& line, uint32_t step)
        : select_tool_grammar::base_type(attribute)
    {
        // :6 T5 M06
        attribute = ":" << karma::lit(phx::ref(line) += step) << " "
                        << "T" << karma::int_ << karma::space << "M06";
    }

private:
    karma::rule<Iterator, interface::SelectTool()> attribute;
};

template <typename Iterator>
bool generate_selectTool(Iterator& sink, uint32_t& line, uint32_t step, const interface::SelectTool& value)
{
    select_tool_grammar<Iterator> selectTool_g(line, step);
    return karma::generate(sink, selectTool_g, value);
}

std::string generate_selectTool(uint32_t& line, uint32_t step, const interface::SelectTool& value)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_selectTool(sink, line, step, value);

    return generated;
}

} // namespace fanuc
} // namespace pp
