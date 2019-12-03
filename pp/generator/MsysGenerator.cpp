//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "MsysGenerator.h"

#include <iomanip>
#include <string>

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp> // construct
#include <boost/spirit/include/phoenix_operator.hpp>
//#include <boost/phoenix/object/dynamic_cast.hpp>
//#include <boost/phoenix/operator/self.hpp>

#include "FloatValueGenerator.h"
#include "interface/CLData.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

// clang-format off

// must be in global namespace

BOOST_FUSION_ADAPT_STRUCT(
    pp::interface::Msys,
    (pp::interface::FloatValue, shift_x)
    (pp::interface::FloatValue, shift_y)
    (pp::interface::FloatValue, shift_z)
    (pp::interface::FloatValue, col1_x)
    (pp::interface::FloatValue, col1_y)
    (pp::interface::FloatValue, col1_z)
    (pp::interface::FloatValue, col2_x)
    (pp::interface::FloatValue, col2_y)
    (pp::interface::FloatValue, col2_z)
)

// clang-format on

namespace pp {
namespace fanuc {

template <typename Iterator>
class msys_grammar : public karma::grammar<Iterator, interface::Msys()>
{
public:
    msys_grammar(uint32_t& line, uint32_t step, uint32_t precision)
        : msys_grammar::base_type(msys_attribute)
        , attr_value_float_check(precision)
    {
        // N7 G97 G90 G54
        // N8 G68.2 X0.0 Y0.0 Z0.0 I60. J90. K0.0
        // N9 G53.1
        attr_value_float %=
            (attr_value_float_check[karma::_pass = phx::bind(&verify, karma::_1)] | karma::lit("<error>"));
        msys_attribute = "N" << karma::lit(phx::ref(line) += step) << " G97 G90 G54" << karma::eol << "N"
                             << karma::lit(phx::ref(line) += step) << " G68.2" << karma::omit[attr_value_float]
                             << karma::omit[attr_value_float] << karma::omit[attr_value_float] << " X"
                             << attr_value_float << " Y" << attr_value_float << " Z" << attr_value_float << " I"
                             << attr_value_float << " J" << attr_value_float << " K" << attr_value_float << karma::eol
                             << "N" << karma::lit(phx::ref(line) += step) << " G53.1";
    }

private:
    float_value_grammar<Iterator>                attr_value_float_check;
    karma::rule<Iterator, interface::FloatValue> attr_value_float;
    karma::rule<Iterator, interface::Msys()>     msys_attribute;
};

template <typename Iterator>
bool generate_msys(Iterator& sink, uint32_t& line, uint32_t step, const interface::Msys& v, uint32_t precision)
{
    msys_grammar<Iterator> msys_g(line, step, precision);
    return karma::generate(sink, msys_g, v);
}

std::string generate_msys(uint32_t& line, uint32_t step, const interface::Msys& value, uint32_t precision)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_msys(sink, line, step, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp
