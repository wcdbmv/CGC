#ifndef MATH_MATRIX_MATRIX_HPP_
#define MATH_MATRIX_MATRIX_HPP_

#include "math/matrix/rectangular_matrix.hpp"

template <std::size_t Size, typename T>
class Matrix : public RectangularMatrix<Size, Size, T> {
public:
	using Base = RectangularMatrix<Size, Size, T>;

	using value_type = typename Base::value_type;
	using pointer = typename Base::pointer;
	using const_pointer = typename Base::const_pointer;
	using reference = typename Base::reference;
	using const_reference = typename Base::const_reference;

	using iterator = typename Base::iterator;
	using const_iterator = typename Base::const_iterator;
	using size_type = typename Base::size_type;

public:
	constexpr static Matrix Identity();

	constexpr Matrix() noexcept = default;
	constexpr explicit Matrix(const RectangularMatrix<4, 4, T>& rhs) noexcept;
	constexpr explicit Matrix(T value) noexcept;
	constexpr Matrix(std::initializer_list<Vector<Size, T>> list) noexcept;
};


template <std::size_t Size, typename T>
constexpr auto Matrix<Size, T>::Identity() -> Matrix {
	return Matrix(1);
}

template <std::size_t Size, typename T>
constexpr Matrix<Size, T>::Matrix(const RectangularMatrix<4, 4, T>& rhs) noexcept:
		Base(rhs) {}

template <std::size_t Size, typename T>
constexpr Matrix<Size, T>::Matrix(T value) noexcept
		: Base{} {
	for (std::size_t i = 0; i != Size; ++i) {
		Base::data_[i][i] = value;
	}
}

template <std::size_t Size, typename T>
constexpr Matrix<Size, T>::Matrix(std::initializer_list<Vector<Size, T>> list) noexcept
		: Base(list) {}

#endif  // MATH_MATRIX_MATRIX_HPP_
