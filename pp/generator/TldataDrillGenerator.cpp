﻿//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "TldataDrillGenerator.h"

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

#include "FloatValueGenerator.h"
#include "interface/CLData.h"
#include "interface/FusionTldataDrill.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

namespace pp {
namespace fanuc {

template <typename Iterator>
class tldata_drill_grammar : public karma::grammar<Iterator, interface::TldataDrill()>
{
public:
    tldata_drill_grammar(uint32_t& line, uint32_t step, uint32_t precision)
        : tldata_drill_grammar::base_type(attribute)
        , attr_value_float(precision)
    {
        // N3 G91 G28 Z0.0
        // N4 G91 G28 X0.0 Y0.0
        // N5 G90 G53 G00 A0.0 C0.0
        attribute = "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G91 G28 Z0.0" << karma::eol << "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G91 G28 X0.0 Y0.0" << karma::eol << "N" << karma::lit(phx::ref(line) += step) << " "
                        << "G90 G53 G00 A0.0 C0.0" << karma::omit[karma::string] << karma::omit[attr_value_float]
                        << karma::omit[attr_value_float] << karma::omit[attr_value_float]
                        << karma::omit[attr_value_float] << karma::omit[attr_value_float];
    }

private:
    float_value_grammar<Iterator>                   attr_value_float;
    karma::rule<Iterator, interface::TldataDrill()> attribute;
};

template <typename Iterator>
bool generate_tldataDrill(Iterator& sink, uint32_t& line, uint32_t step, const interface::TldataDrill& value,
                          uint32_t precision)
{
    tldata_drill_grammar<Iterator> tldataDrill_g(line, step, precision);
    return karma::generate(sink, tldataDrill_g, value);
}

std::string generate_tldataDrill(uint32_t& line, uint32_t step, const interface::TldataDrill& value, uint32_t precision)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_tldataDrill(sink, line, step, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp
