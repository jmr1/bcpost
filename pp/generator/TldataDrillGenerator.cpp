//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "TldataDrillGenerator.h"

#include <iomanip>
#include <string>

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/adapted.hpp>
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

BOOST_FUSION_ADAPT_STRUCT_NAMED(
    const pp::interface::FloatValue, fvTldataDrill,
    (boost::optional<char>, sign)
    (boost::optional<std::string>, value)
    (boost::optional<char>, dot)
    (boost::optional<std::string>, value2)
)

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::TldataDrill,
    (std::string, module_type)
    (pp::interface::FloatValue, diameter)
    (pp::interface::FloatValue, corner_radius)
    (pp::interface::FloatValue, length)
    (pp::interface::FloatValue, point_angle)
    (pp::interface::FloatValue, flute_length)
)

// clang-format on

namespace pp {
namespace fanuc {

// This is simplified implementation as this data isn't going to be output for TldataDrill type
template <typename Iterator>
class float_value_grammar : public karma::grammar<Iterator, boost::fusion::adapted::fvTldataDrill()>
{
public:
    float_value_grammar()
        : float_value_grammar::base_type(float_value_attribute)
    {
        float_value_attribute = -karma::char_ << -karma::string << -karma::char_ << -karma::string;
    }

private:
    karma::rule<Iterator, boost::fusion::adapted::fvTldataDrill()> float_value_attribute;
};

template <typename Iterator>
class tldata_drill_grammar : public karma::grammar<Iterator, interface::TldataDrill()>
{
public:
    tldata_drill_grammar()
        : tldata_drill_grammar::base_type(attribute)
    {
        // G91 G28 Z0.0
        // G91 G28 X0.0 Y0.0
        // G90 G53 G00 A0.0 C0.0
        attribute = karma::lit("G91 G28 Z0.0")
                    << karma::eol << "G91 G28 X0.0 Y0.0" << karma::eol << "G90 G53 G00 A0.0 C0.0"
                    << karma::omit[karma::string] << karma::omit[attr_value_float] << karma::omit[attr_value_float]
                    << karma::omit[attr_value_float] << karma::omit[attr_value_float] << karma::omit[attr_value_float];
    }

private:
    float_value_grammar<Iterator>                   attr_value_float;
    karma::rule<Iterator, interface::TldataDrill()> attribute;
};

template <typename Iterator>
bool generate_tldataDrill(Iterator& sink, const interface::TldataDrill& value)
{
    tldata_drill_grammar<Iterator> tldataDrill_g;
    return karma::generate(sink, tldataDrill_g, value);
}

std::string generate_tldataDrill(const interface::TldataDrill& value)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_tldataDrill(sink, value);

    return generated;
}

} // namespace fanuc
} // namespace pp
