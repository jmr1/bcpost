//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "EndOfPathGenerator.h"

#include <iomanip>
#include <string>

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

namespace pp {
namespace fanuc {

template <typename Iterator>
class end_of_path_grammar : public karma::grammar<Iterator, interface::EndOfPath()>
{
public:
    end_of_path_grammar(uint32_t& line, uint32_t step)
        : end_of_path_grammar::base_type(attribute)
    {
        // N1 G69
        // N2 G91 G28 Z0.0
        // N3 G91 G28 X0.0 Y0.0
        // N4 G90 G53 G00 A0.0 C0.0
        // N5 M05
        // N6 M09
        // N7 M30
        // %
        attribute = "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G69" << karma::eol << "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G91 G28 Z0.0" << karma::eol << "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G91 G28 X0.0 Y0.0" << karma::eol << "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G90 G53 G00 A0.0 C0.0" << karma::eol << "N" << karma::lit(phx::ref(line) += step) << " "
                        << "M05" << karma::eol << "N" << karma::lit(phx::ref(line) += step) << " "
                        << "M09" << karma::eol << "N" << karma::lit(phx::ref(line) += step) << " "
                        << "M30" << karma::eol << "%";
    }

private:
    karma::rule<Iterator, interface::EndOfPath()> attribute;
};

template <typename Iterator>
bool generate_endOfPath(Iterator& sink, uint32_t& line, uint32_t step)
{
    end_of_path_grammar<Iterator> endOfPath_g(line, step);
    return karma::generate(sink, endOfPath_g);
}

std::string generate_endOfPath(uint32_t& line, uint32_t step)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_endOfPath(sink, line, step);

    return generated;
}

} // namespace fanuc
} // namespace pp
