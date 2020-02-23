//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "MsysGenerator.h"

#include <iomanip>
#include <string>

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

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
#include "interface/FusionMsys.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

namespace pp {
namespace fanuc {

auto calc_matrix_elems(double i1, double j1, double k1, double i2, double j2, double k2)
{
    const double i3 = j1 * k2 - k1 * j2;
    const double j3 = -1. * (i1 * k2 - k1 * i2);
    const double k3 = i1 * j2 - j1 * i2;

    return std::make_tuple(i3, j3, k3);
}

auto calc_angle_rotation(double i1, double j1, double k1, double i2, double j2, double k2)
{
    double angleA{};
    double angleB{};
    double angleC{};

    const auto [i3, j3, k3] = calc_matrix_elems(i1, j1, k1, i2, j2, k2);

    if (i3 != 1 && i3 != -1)
    {
        // Obliczenia dla radianow w osiach z y x (fi theta psi)
        const double prad  = atan2(j3, k3);
        const double frad  = atan2(i2, i1);
        const double pierw = sqrt(1 - pow(i3, 2));
        const double trad  = atan2(i3, pierw);
        // Przeliczenie na stopnie
        const double pstop = (prad * 180) / M_PI;
        double       tstop = (trad * 180) / M_PI;
        const double fstop = (frad * 180) / M_PI;
        if (sin(tstop) != k1)
        {
            tstop = tstop * -1;
        }
        angleA = pstop;
        angleB = tstop;
        angleC = fstop;
    }
    if (i3 == -1)
    {
        const double prad  = atan2(j1, k1);
        const double trad  = (M_PI * 0.5);
        const double frad  = 0.;
        const double pstop = (prad * 180) / M_PI;
        const double tstop = (trad * 180) / M_PI;
        const double fstop = frad;
        angleA             = pstop;
        angleB             = tstop;
        angleC             = fstop;
    }
    if (i3 == 1)
    {
        const double prad  = atan2((-1 * j1), (-1 * k1));
        const double trad  = (-M_PI * 0.5);
        const double frad  = 0.;
        const double tstop = (trad * 180) / M_PI;
        const double pstop = (prad * 180) / M_PI;
        const double fstop = frad;
        angleA             = pstop;
        angleB             = tstop;
        angleC             = fstop;
    }

    return std::make_tuple(angleA, angleB, angleC);
}

template <typename Iterator>
class msys_grammar : public karma::grammar<Iterator, interface::Msys()>
{
public:
    msys_grammar(uint32_t& line, uint32_t step, uint32_t precision, bool is_3axis, const interface::FloatValue& i,
                 const interface::FloatValue& j, const interface::FloatValue& k)
        : msys_grammar::base_type(msys_attribute)
        , attr_value_float_check(precision)
    {
        // 5 axis:
        // N7 G97 G90 G54
        // N8 G68.2 X0.0 Y0.0 Z0.0 I60. J90. K0.0
        // or
        // N8 G68.2 P1 X0.0 Y0.0 Z0.0 I90. J0. K60.
        // N9 G53.1
        //
        // 3 axis:
        // N7 G97 G90 G54
        // N8 G53.1
        attr_value_float %=
            (attr_value_float_check[karma::_pass = phx::bind(&verify, karma::_1)] | karma::lit("<error>"));
        msys_attribute %=
            "N" << karma::lit(phx::ref(line) += step) << " G97 G90 G54" << karma::eol
                << (karma::eps(is_3axis) |
                    ("N" << karma::lit(phx::ref(line) += step) << " G68.2"
                         << " P1"
                         << " X" << attr_value_float << " Y" << attr_value_float << " Z" << attr_value_float << " I"
                         << karma::lit(interface::to_string(i)) << " J" << karma::lit(interface::to_string(j)) << " K"
                         << karma::lit(interface::to_string(k)) << karma::eol))
                << "N" << karma::lit(phx::ref(line) += step) << " G53.1";
    }

private:
    float_value_grammar<Iterator>                attr_value_float_check;
    karma::rule<Iterator, interface::FloatValue> attr_value_float;
    karma::rule<Iterator, interface::Msys()>     msys_attribute;
};

template <typename Iterator>
bool generate_msys(Iterator& sink, uint32_t& line, uint32_t step, const interface::Msys& v, uint32_t precision)
{
    const auto col1_3axis = std::make_tuple(1., 0., 0.);
    const auto col2_3axis = std::make_tuple(0., 1., 0.);
    const auto col1       = std::make_tuple(to_double(v.col1_x), to_double(v.col1_y), to_double(v.col1_z));
    const auto col2       = std::make_tuple(to_double(v.col2_x), to_double(v.col2_y), to_double(v.col2_z));

    const auto is_3axis = (col1_3axis == col1 && col2_3axis == col2) || (col1_3axis == col2 && col2_3axis == col1);

    const auto [i, j, k] = calc_angle_rotation(to_double(v.col1_x), to_double(v.col1_y), to_double(v.col1_z),
                                               to_double(v.col2_x), to_double(v.col2_y), to_double(v.col2_z));

    msys_grammar<Iterator> msys_g(
        line, step, precision, is_3axis, interface::to_FloatValue(std::to_string(i), precision),
        interface::to_FloatValue(std::to_string(j), precision), interface::to_FloatValue(std::to_string(k), precision));

    return karma::generate(sink, msys_g, v);
}

std::string generate_msys(uint32_t& line, uint32_t step, const interface::Msys& value, uint32_t precision)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_msys(sink, line, step, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp
