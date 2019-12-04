#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "CycleDrillGenerator.h"

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
    pp::interface::CycleDrill,
    (pp::interface::FloatValue, rapto)
    (pp::interface::FloatValue, fedto)
    (boost::optional<pp::interface::FloatValue>, rtrcto)
    (pp::interface::RetractionType, retraction_type)
    (pp::interface::FedrateType, fedrate_type)
    (pp::interface::FloatValue, fedrate)
)

// clang-format on

namespace pp {
namespace fanuc {

template <typename Iterator>
class cycle_drill_grammar : public karma::grammar<Iterator, interface::CycleDrill()>
{
public:
    cycle_drill_grammar(GeneratorData& data, uint32_t& line, uint32_t step, uint32_t precision)
        : cycle_drill_grammar::base_type(attribute)
        , attr_value_float(precision)
    {
        // N12 G98 G81 X-24.585 Y-115. Z36.996 F250. R73.
        attribute =
            "N" << karma::lit(phx::ref(line) += step) << " "
                << "G98 G81 X" /*<< data.x << " Y" << data.y << " Z" << data.z*/ << karma::omit[attr_value_float]
                << karma::omit[attr_value_float] << karma::omit[attr_value_float];
    }

private:
    float_value_grammar<Iterator>                  attr_value_float;
    karma::rule<Iterator, interface::CycleDrill()> attribute;
};

template <typename Iterator>
bool generate_cycleDrill(Iterator& sink, GeneratorData& data, uint32_t& line, uint32_t step,
                         const interface::CycleDrill& value, uint32_t precision)
{
    cycle_drill_grammar<Iterator> cycleDrill_g(data, line, step, precision);
    return karma::generate(sink, cycleDrill_g, value);
}

std::string generate_cycleDrill(GeneratorData& data, uint32_t& line, uint32_t step, const interface::CycleDrill& value,
                                uint32_t precision)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_cycleDrill(sink, data, line, step, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp
