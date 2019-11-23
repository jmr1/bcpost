//#include "stdafx.h"

#include "CLDataVisitor.h"

#include <boost/variant.hpp>

#include "FanucGeneratorGrammar.h"

namespace pp {
namespace fanuc {

std::string CLDataVisitor::operator()(const interface::Goto& value) const
{
    std::string                            generated;
    std::back_insert_iterator<std::string> sink(generated);

    generate_goto(sink, value, precision);

    return generated;
}

} // namespace fanuc
} // namespace pp