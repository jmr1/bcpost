#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "SpindlRpmGenerator.h"

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
    pp::interface::SpindlRpm,
    (pp::interface::FloatValue, rpm)
    (pp::interface::RotationDirection, rotation_direction)
)

// clang-format on

namespace pp {
namespace fanuc {

struct RotationDirectionSym : karma::symbols<interface::RotationDirection, std::string>
{
public:
    RotationDirectionSym()
    {
        add(interface::RotationDirection::CLW, "3")(interface::RotationDirection::CCLW, "4");
    }
};

template <typename Iterator>
class spindl_rpm_grammar : public karma::grammar<Iterator, interface::SpindlRpm()>
{
public:
    spindl_rpm_grammar(uint32_t& line, uint32_t step, uint32_t precision)
        : spindl_rpm_grammar::base_type(attribute)
        , attr_value_float(precision)
    {
        // N10 G43 H00 S800 M03
        attribute = "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G43 H00 S" << attr_value_float << " M0" << rotation_direction_sym;
    }

private:
    float_value_grammar<Iterator>                 attr_value_float;
    karma::rule<Iterator, interface::SpindlRpm()> attribute;
    RotationDirectionSym rotation_direction_sym;
};

template <typename Iterator>
bool generate_spindlRpm(Iterator& sink, uint32_t& line, uint32_t step, const interface::SpindlRpm& value,
                        uint32_t precision)
{
    spindl_rpm_grammar<Iterator> spindlRpm_g(line, step, precision);
    return karma::generate(sink, spindlRpm_g, value);
}

std::string generate_spindlRpm(uint32_t& line, uint32_t step, const interface::SpindlRpm& value, uint32_t precision)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_spindlRpm(sink, line, step, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp
