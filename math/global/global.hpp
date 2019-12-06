#ifndef MATH_GLOBAL_GLOBAL_HPP_
#define MATH_GLOBAL_GLOBAL_HPP_

#include <cstdlib>
#include <limits>

template <typename T>
constexpr bool equal(const T& a, const T& b) {
	return std::abs(a - b) <= std::numeric_limits<T>::epsilon();
}

#endif  // MATH_GLOBAL_GLOBAL_HPP_
