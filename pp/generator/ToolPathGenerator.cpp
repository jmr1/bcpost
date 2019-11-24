﻿//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "ToolPathGenerator.h"

#include <iomanip>
#include <string>

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/phoenix/bind.hpp>
//#include <boost/bind.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp> // construct
#include <boost/spirit/include/phoenix_operator.hpp>
//#include <boost/phoenix/object/dynamic_cast.hpp>
//#include <boost/phoenix/operator/self.hpp>

//#include "MessageTextImpl.h"

#include "interface/CLData.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::ToolPath,
    (std::string, operation_name)
    (std::string, tool_name)
)

// clang-format on

namespace pp {
namespace fanuc {

template <typename Iterator>
class tool_path_grammar : public karma::grammar<Iterator, interface::ToolPath()>
{
public:
    tool_path_grammar()
        : tool_path_grammar::base_type(attribute)
    {
        // %
        // O0001
        // G40 G17 G90 G49 G21
        // (DRILLING_1)
        attribute = karma::lit("%") << karma::eol << "O0001" << karma::eol << "G40 G17 G90 G49 G21" << karma::eol << "("
                                    << karma::string << ")" << karma::omit[karma::string];
    }

private:
    karma::rule<Iterator, interface::ToolPath()> attribute;
};

template <typename Iterator>
bool generate_toolPath(Iterator& sink, const interface::ToolPath& value)
{
    tool_path_grammar<Iterator> toolPath_g;
    return karma::generate(sink, toolPath_g, value);
}

std::string generate_toolPath(const interface::ToolPath& value)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_toolPath(sink, value);

    return generated;
}

} // namespace fanuc
} // namespace pp
