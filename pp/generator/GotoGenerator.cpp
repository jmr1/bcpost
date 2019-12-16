//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#ifndef NDEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include "GotoGenerator.h"

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
#include "GeneratorData.h"
#include "interface/CLData.h"
#include "interface/FusionGoto.h"

namespace karma   = boost::spirit::karma;
namespace ascii   = boost::spirit::ascii;
namespace classic = boost::spirit::classic;
namespace phx     = boost::phoenix;
namespace fusion  = boost::fusion;

namespace pp {
namespace fanuc {

#ifdef THROW_WHEN_ERROR

template <typename Iterator>
class goto_grammar : public karma::grammar<Iterator, interface::Goto()>
{
public:
    goto_grammar(uint32_t& line, uint32_t step, uint32_t precision)
        : goto_grammar::base_type(goto_attribute)
        , attr_value_float_throw(precision)
    {
        // G94 G90 X-24.585 Y-115. Z100.
        attr_value_float %= attr_value_float_throw[karma::_pass = phx::bind(&verify_throw, karma::_1)];
        goto_attribute %= "N" << karma::lit(phx::ref(line) += step) << " G94 G90 X" << attr_value_float << " Y"
                              << attr_value_float << " Z" << attr_value_float;
    }

private:
    float_value_grammar<Iterator>                  attr_value_float_throw;
    karma::rule<Iterator, interface::FloatValue()> attr_value_float;
    karma::rule<Iterator, interface::Goto()>       goto_attribute;
};

#else

template <typename Iterator>
class goto_grammar : public karma::grammar<Iterator, interface::Goto()>
{
public:
    goto_grammar(GeneratorData& data, uint32_t& line, uint32_t step, uint32_t precision)
        : goto_grammar::base_type(goto_attribute)
        , attr_value_float_check(precision)
    {
        // G94 G90 X-24.585 Y-115. Z100.
        attr_value_float %=
            (attr_value_float_check[karma::_pass = phx::bind(&verify, karma::_1)] | karma::lit("<error>"));
        goto_attribute %= "N" << karma::lit(phx::ref(line) += step) << " G94 G90 X"
                              << attr_value_float[phx::bind(&GeneratorData::x, &data) = karma::_1] << " Y"
                              << attr_value_float[phx::bind(&GeneratorData::y, &data) = karma::_1] << " Z"
                              << attr_value_float[phx::bind(&GeneratorData::z, &data) = karma::_1];
    }

private:
    float_value_grammar<Iterator>                attr_value_float_check;
    karma::rule<Iterator, interface::FloatValue> attr_value_float;
    karma::rule<Iterator, interface::Goto()>     goto_attribute;
};

std::string sum(const interface::FloatValue& lhs, const interface::FloatValue& rhs)
{
    return to_string(lhs + rhs);
}

template <typename Iterator>
class goto_in_cycle_grammar : public karma::grammar<Iterator, interface::Goto()>
{
public:
    goto_in_cycle_grammar(const std::map<std::string, std::string>& m, GeneratorData& data, uint32_t& line,
                          uint32_t step, uint32_t precision, bool first)
        : goto_in_cycle_grammar::base_type(goto_attribute)
        , attr_value_float_check(precision)
    {
        auto func = [&m](const std::string& value) {
            return phx::bind(
                static_cast<const std::string& (std::map<std::string, std::string>::*)(const std::string&)const>(
                    &std::map<std::string, std::string>::at),
                phx::cref(m), value);
        };

        const auto rapto = func("RAPTO");
        const auto f     = func("F");

        // if first:
        //   N12 G98 G81 X-24.585 Y-115. Z36.996 F250. R73.
        // else:
        //   N14 G81 X.415 Y-100. Z36.996 F250. R73.
        //
        // N15 G00 Z100.
        attr_value_float %=
            (attr_value_float_check[karma::_pass = phx::bind(&verify, karma::_1)] | karma::lit("<error>"));

        std::string block_start;
        if (first)
            block_start = " G98 G81 X";
        else
            block_start = " G81 X";

        goto_attribute %=
            "N" << karma::lit(phx::ref(line) += step) << block_start
                << attr_value_float[phx::bind(&GeneratorData::x, &data) = karma::_1] << " Y"
                << attr_value_float[phx::bind(&GeneratorData::y, &data) = karma::_1] << " Z"
                << attr_value_float[phx::bind(&GeneratorData::z, &data) = karma::_1] << " F" << karma::lit(f) << " R"
                << karma::lit(phx::bind(&sum, phx::ref(*data.rapto), phx::bind(&interface::Goto::z, karma::_val)))
                << karma::eol << "N" << karma::lit(phx::ref(line) += step) << " G00 Z100.";
    }

private:
    float_value_grammar<Iterator>                attr_value_float_check;
    karma::rule<Iterator, interface::FloatValue> attr_value_float;
    karma::rule<Iterator, interface::Goto()>     goto_attribute;
};

#endif

template <typename Iterator>
bool generate_goto(Iterator& sink, GeneratorData& data, uint32_t& line, uint32_t step, const interface::Goto& v,
                   uint32_t precision, bool in_cycle, bool first_goto_in_cycle)
{
    if (in_cycle)
    {
        std::map<std::string, std::string> m;

        auto func = [&m, precision](const std::string& key, const auto& value) {
            m.emplace(key, generate_floatValue(
                               value ? *value : interface::FloatValue{boost::none, std::string("0"), '.'}, precision));
        };

        func("RAPTO", data.rapto);
        func("F", data.fedrate);

        goto_in_cycle_grammar<Iterator> goto_g(m, data, line, step, precision, first_goto_in_cycle);
        return karma::generate(sink, goto_g, v);
    }
    else
    {
        goto_grammar<Iterator> goto_g(data, line, step, precision);
        return karma::generate(sink, goto_g, v);
    }

    return false;
}

std::string generate_goto(GeneratorData& data, uint32_t& line, uint32_t step, const interface::Goto& value,
                          uint32_t precision, bool in_cycle, bool first_goto_in_cycle)
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_goto(sink, data, line, step, value, precision, in_cycle, first_goto_in_cycle);

    return generated;
}

} // namespace fanuc
} // namespace pp
