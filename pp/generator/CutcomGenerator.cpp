#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "CutcomGenerator.h"

#include <iomanip>
#include <map>
#include <string>

#include <boost/config/warning_disable.hpp>
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
#include "interface/FusionCutcom.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

namespace pp {
namespace fanuc {

struct CutterCompensationSym : karma::symbols<interface::CutterCompensation, std::string>
{
public:
    CutterCompensationSym()
    {
        add(interface::CutterCompensation::ON, "39")(interface::CutterCompensation::OFF, "40")(
            interface::CutterCompensation::LEFT, "41")(interface::CutterCompensation::RIGHT, "42");
    }
};

template <typename Iterator>
class cutcom_grammar : public karma::grammar<Iterator, interface::Cutcom()>
{
public:
    cutcom_grammar(uint32_t& line, uint32_t step, uint32_t precision)
        : cutcom_grammar::base_type(attribute)
    {
        // N10 G42 D4
        attribute = "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G" << cutter_compensation_sym << -(" D" << karma::uint_);
    }

private:
    karma::rule<Iterator, interface::Cutcom()> attribute;
    CutterCompensationSym                      cutter_compensation_sym;
};

template <typename Iterator>
bool generate_cutcom(Iterator& sink, uint32_t& line, uint32_t step, const interface::Cutcom& value, uint32_t precision)
{
    cutcom_grammar<Iterator> cutcom_g(line, step, precision);
    return karma::generate(sink, cutcom_g, value);
}

std::string generate_cutcom(uint32_t& line, uint32_t step, const interface::Cutcom& value, uint32_t precision)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_cutcom(sink, line, step, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp
