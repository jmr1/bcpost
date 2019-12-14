#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "CircleGenerator.h"

#include <iomanip>
#include <map>
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
    pp::interface::Circle,
    (pp::interface::FloatValue, x)
    (pp::interface::FloatValue, y)
    (pp::interface::FloatValue, z)
    (pp::interface::FloatValue, i)
    (pp::interface::FloatValue, j)
    (pp::interface::FloatValue, k)
    (pp::interface::FloatValue, r)
    (pp::interface::FloatValue, t)
    (pp::interface::FloatValue, f)
    (pp::interface::FloatValue, d)
    (pp::interface::FloatValue, e)
    (boost::optional<uint32_t>, n)
)

// clang-format on

namespace pp {
namespace fanuc {

template <typename Iterator>
class circle_grammar : public karma::grammar<Iterator, interface::Circle()>
{
public:
    circle_grammar(uint32_t& line, uint32_t step, uint32_t precision)
        : circle_grammar::base_type(attribute)
        , attr_value_float(precision)
    {
        // N55 G2 X206.458 Y-15. I9. J-12.
        // or
        // N85 G3 X440. Y300. I-10.909 J38.484
        attribute = "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G2 X" << attr_value_float << " Y" << attr_value_float << karma::omit[attr_value_float]
                        << " I" << attr_value_float << " J" << attr_value_float;
    }

private:
    float_value_grammar<Iterator>              attr_value_float;
    karma::rule<Iterator, interface::Circle()> attribute;
};

template <typename Iterator>
bool generate_circle(Iterator& sink, uint32_t& line, uint32_t step, const interface::Circle& value, uint32_t precision)
{
    circle_grammar<Iterator> circle_g(line, step, precision);
    return karma::generate(sink, circle_g, value);
}

std::string generate_circle(uint32_t& line, uint32_t step, const interface::Circle& value, uint32_t precision)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_circle(sink, line, step, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp
