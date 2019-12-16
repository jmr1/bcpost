//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "RapidGenerator.h"

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
#include "interface/FusionRapid.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

namespace pp {
namespace fanuc {

template <typename Iterator>
class rapid_grammar : public karma::grammar<Iterator, interface::Rapid()>
{
public:
    rapid_grammar(uint32_t& line, uint32_t step)
        : rapid_grammar::base_type(attribute)
    {
        // N4 G90 G53 G00 A0.0 C0.0
        attribute = "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G90 G53 G00 A0.0 C0.0";
    }

private:
    karma::rule<Iterator, interface::Rapid()> attribute;
};

template <typename Iterator>
bool generate_rapid(Iterator& sink, uint32_t& line, uint32_t step)
{
    rapid_grammar<Iterator> rapid_g(line, step);
    return karma::generate(sink, rapid_g);
}

std::string generate_rapid(uint32_t& line, uint32_t step)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_rapid(sink, line, step);

    return generated;
}

} // namespace fanuc
} // namespace pp
