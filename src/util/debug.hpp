#ifndef _CIRCUITRY_UTIL_DEBUG_HPP_
#define _CIRCUITRY_UTIL_DEBUG_HPP_

#include <string>

namespace util {

enum class Gravity : char {
	info = 0,
	warning = 1,
	error = 2,
	critical = 3,
	max = critical,
};

void debug(Gravity gravity, const std::string& source, const std::string& message);

} // namespace util

#endif // _CIRCUITRY_UTIL_DEBUG_HPP_