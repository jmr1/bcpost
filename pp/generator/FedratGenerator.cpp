#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "FedratGenerator.h"

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
#include "interface/FusionFedrat.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

namespace pp {
namespace fanuc {

struct FedrateTypeSym : karma::symbols<interface::FedrateType, std::string>
{
public:
    FedrateTypeSym()
    {
        add(interface::FedrateType::MMPM, "94")(interface::FedrateType::MMPR, "95")(interface::FedrateType::IPM, "94")(
            interface::FedrateType::IPR, "95");
    }
};

template <typename Iterator>
class fedrat_grammar : public karma::grammar<Iterator, interface::Fedrat()>
{
public:
    fedrat_grammar(uint32_t& line, uint32_t step, uint32_t precision)
        : fedrat_grammar::base_type(attribute)
        , attr_value_float(precision)
    {
        // N10 G94 F250.
        // or
        // N10 G95 F250.
        attribute = "N" << karma::lit(phx::ref(line) += step) << " G" << fedrate_type_sym << " F" << attr_value_float;
    }

private:
    float_value_grammar<Iterator>              attr_value_float;
    karma::rule<Iterator, interface::Fedrat()> attribute;
    FedrateTypeSym                             fedrate_type_sym;
};

template <typename Iterator>
bool generate_fedrat(Iterator& sink, uint32_t& line, uint32_t step, const interface::Fedrat& value, uint32_t precision)
{
    fedrat_grammar<Iterator> fedrat_g(line, step, precision);
    return karma::generate(sink, fedrat_g, value);
}

std::string generate_fedrat(uint32_t& line, uint32_t step, const interface::Fedrat& value, uint32_t precision)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_fedrat(sink, line, step, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp
