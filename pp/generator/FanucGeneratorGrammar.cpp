//#include "stdafx.h"
#ifdef _MSC_VER
#pragma warning(disable : 4348)
#endif

#include "FanucGeneratorGrammar.h"

namespace pp {
namespace fanuc {

template class goto_grammar<std::back_insert_iterator<std::string>>;

} // namespace fanuc
} // namespace pp
