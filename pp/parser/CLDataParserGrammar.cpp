//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "CLDataParserGrammar.h"

namespace pp {
namespace cldata {

std::ostream& operator<<(std::ostream& ostr, const interface::RetractionType& value)
{
    switch (value)
    {
    case interface::RetractionType::AUTO:
        ostr << "AUTO";
        break;
    case interface::RetractionType::MANUAL:
        ostr << "MANUAL";
        break;
    }
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const interface::FedrateType& value)
{
    switch (value)
    {
    case interface::FedrateType::IPM:
        ostr << "IPM";
        break;
    case interface::FedrateType::IPR:
        ostr << "IPR";
        break;
    case interface::FedrateType::MMPM:
        ostr << "MMPM";
        break;
    case interface::FedrateType::MMPR:
        ostr << "MMPR";
        break;
    }
    return ostr;
}

template class all_attributes_grammar<pos_iterator_type>;

} // namespace cldata
} // namespace pp
