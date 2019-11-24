//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "GotoGenerator.h"

#include <iomanip>
#include <string>

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

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
    end_of_path_grammar()
        : end_of_path_grammar::base_type(attribute)
    {
        // G69
        // G91 G28 Z0.0
        // G91 G28 X0.0 Y0.0
        // G90 G53 G00 A0.0 C0.0
        // M05
        // M09
        // M30
        // %
        attribute %= karma::lit("G69") << karma::eol << "G91 G28 Z0.0" << karma::eol << "G91 G28 X0.0 Y0.0"
                                       << karma::eol << "G90 G53 G00 A0.0 C0.0" << karma::eol << "M05" << karma::eol
                                       << "M09" << karma::eol << "M30" << karma::eol << "%";
    }

private:
    karma::rule<Iterator, interface::EndOfPath()> attribute;
};

template <typename Iterator>
bool generate_endOfPath(Iterator& sink)
{
    end_of_path_grammar<Iterator> endOfPath_g;
    return karma::generate(sink, endOfPath_g);
}

std::string generate_endOfPath()
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_endOfPath(sink);

    return generated;
}

} // namespace fanuc
} // namespace pp
