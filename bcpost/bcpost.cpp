//#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <memory>

#include <boost/algorithm/string/trim.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "generator/FanucGenerator.h"
#include "interface/CLData.h"
#include "parser/CLDataParser.h"

namespace po = boost::program_options;
namespace pt = boost::property_tree;

#define VERIFY_OPTION(NAME, VARIABLE)                                                                                  \
    if (vm.count(NAME))                                                                                                \
    {                                                                                                                  \
        if (vm.count("verbose"))                                                                                       \
            std::cout << NAME << " was set to [" << VARIABLE << "]." << std::endl;                                     \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        std::cerr << "ERROR: " << NAME << " was not set." << std::endl;                                                \
        return 1;                                                                                                      \
    }

int main(int argc, char* argv[])
{
    std::string input;
    std::string output;
    bool        single_line_output;

    // Declare the supported options.
    po::options_description desc("Allowed options");
    // clang-format off
    desc.add_options()
        ("help,h", "produce help message")
        ("verbose,v", "output additional information")
        ("single-line-output,s", po::value<bool>(&single_line_output)->default_value(true), "whether the error output is single line")
        ("output,o", po::value<std::string>(&input), "path to output generated file")
        ("input,i", po::value<std::string>(&input), "path to input CLData file")
    ;
    // clang-format on

    po::positional_options_description p;
    p.add("input", 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    VERIFY_OPTION("single-line-output", single_line_output);
    VERIFY_OPTION("input", input);

    if (vm.count("output"))
    {
        if (vm.count("verbose"))
            std::cout << "output"
                      << " was set to [" << output << "]." << std::endl;
    }

    std::ifstream file(input.c_str());
    if (file.fail())
    {
        std::cerr << "ERROR: Path to file [" << input << "] is wrong!" << std::endl;
        return 1;
    }

    pp::cldata::CLDataParser parser;

    size_t                                          line_nbr{};
    size_t                                          line_err{};
    std::string                                     data;
    const std::string                               line_str("line 1");
    std::vector<pp::interface::CLDataAttributeData> av_vec;
    while (std::getline(file, data))
    {
        ++line_nbr;
        boost::algorithm::trim(data);
        if (data.empty())
            continue;

        bool                               ret{};
        std::string                        message;
        pp::interface::CLDataAttributeData av;

        ret = parser.parse(static_cast<int>(line_nbr), data, av, message, single_line_output ? true : false);
        if (ret)
        {
            av_vec.emplace_back(std::move(av));
        }
        else
        {
            ++line_err;
            auto pos = message.find(line_str);
            if (pos != std::string::npos)
            {
                message.replace(pos, line_str.size(), "line " + std::to_string(line_nbr));
            }
            else
            {
                if (message.empty())
                {
                    message = data;
                    message = "line " + std::to_string(line_nbr) + R"(: ')" + message + R"(')";
                }
                else if (message[0] == '1')
                {
                    message = std::to_string(line_nbr) + message.substr(1);
                }
                else
                {
                    message = std::to_string(line_nbr) + ": " + message;
                }
            }
            std::cout << "= " << message << std::endl;
        }
    }

    std::cout << line_nbr << " lines parsed, " << line_err << " error(s) found!" << std::endl;

    std::vector<std::string>  gen_data;
    pp::fanuc::FanucGenerator fg(3);

    for (size_t x = 0; x < av_vec.size(); ++x)
    {
        std::string message;
        const auto& cl_data = av_vec[x];

        if (!fg.generate(static_cast<int>(x), cl_data, gen_data, message, true))
        {
            std::cout << "x=" << x << ": " << message << std::endl;
        }
    }

    if (!output.empty())
    {
        std::ofstream file(output.c_str());
        if (file.fail())
        {
            std::cerr << "ERROR: Path to file [" << output << "] is wrong!" << std::endl;
            return 1;
        }

        for (const auto& text : gen_data)
        {
            file << text;
            file << std::endl;
        }
        file.close();
    }
    else
    {
        for (const auto& text : gen_data)
        {
            std::cout << text;
            std::cout << std::endl;
        }
    }

    return 0;
}
