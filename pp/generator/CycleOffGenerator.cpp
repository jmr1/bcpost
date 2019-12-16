//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "CycleOffGenerator.h"

#include <iomanip>
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

#include "interface/CLData.h"
#include "interface/FusionCycleOff.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

namespace pp {
namespace fanuc {

template <typename Iterator>
class cycle_off_grammar : public karma::grammar<Iterator, interface::CycleOff()>
{
public:
    cycle_off_grammar(uint32_t& line, uint32_t step)
        : cycle_off_grammar::base_type(attribute)
    {
        // N1 G80
        attribute = "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G80";
    }

private:
    karma::rule<Iterator, interface::CycleOff()> attribute;
};

template <typename Iterator>
bool generate_cycleOff(Iterator& sink, uint32_t& line, uint32_t step)
{
    cycle_off_grammar<Iterator> cycleOff_g(line, step);
    return karma::generate(sink, cycleOff_g);
}

std::string generate_cycleOff(uint32_t& line, uint32_t step)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_cycleOff(sink, line, step);

    return generated;
}

} // namespace fanuc
} // namespace pp
