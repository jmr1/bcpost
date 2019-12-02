#pragma once

#include <boost/spirit/home/qi/stream.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

namespace pp {
namespace cldata {

using pos_iterator_type = boost::spirit::classic::position_iterator2<boost::spirit::istream_iterator>;

} // namespace cldata
} // namespace pp
