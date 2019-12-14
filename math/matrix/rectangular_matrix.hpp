#ifndef MATH_MATRIX_RECTANGULAR_MATRIX_HPP_
#define MATH_MATRIX_RECTANGULAR_MATRIX_HPP_

#include "math/vector/vector.hpp"

template <std::size_t Rows, std::size_t Cols, typename T>
class RectangularMatrix {
public:
	using value_type = Vector<Cols, T>;
	using pointer = Vector<Cols, T>*;
	using const_pointer = const Vector<Cols, T>*;
	using reference = Vector<Cols, T>&;
	using const_reference = const Vector<Cols, T>&;

	using iterator = value_type*;
	using const_iterator = const value_type*;
	using size_type = std::size_t;

public:
	constexpr RectangularMatrix() noexcept = default;
	constexpr explicit RectangularMatrix(T value) noexcept;
	constexpr RectangularMatrix(std::initializer_list<Vector <Cols, T>> list) noexcept;

	constexpr iterator begin();
	constexpr const_iterator begin() const;
	constexpr iterator end();
	constexpr const_iterator end() const;

	constexpr reference operator[](size_type index);
	constexpr const_reference operator[](size_type index) const;
	reference at(size_type index);
	const_reference at(size_type index) const;

protected:
	Vector<Rows, Vector<Cols, T>> data_;
};

template <std::size_t Rows, std::size_t Cols, typename T>
std::istream& operator<<(std::istream& is, RectangularMatrix<Rows, Cols, T>& matrix);
template <std::size_t Rows, std::size_t Cols, typename T>
std::ostream& operator<<(std::ostream& os, const RectangularMatrix<Rows, Cols, T>& matrix);

template <std::size_t L, std::size_t M, std::size_t N, typename T>
const RectangularMatrix<L, N, T> operator*(const RectangularMatrix<L, M, T>& m1, const RectangularMatrix<M, N, T>& m2);


template <std::size_t Rows, std::size_t Cols, typename T>
constexpr RectangularMatrix<Rows, Cols, T>::RectangularMatrix(T value) noexcept
		: data_(Vector<Cols, T>(value)) {}

template <std::size_t Rows, std::size_t Cols, typename T>
constexpr RectangularMatrix<Rows, Cols, T>::RectangularMatrix(std::initializer_list<Vector<Cols, T>> list) noexcept
		: data_{} {
	auto first = begin(), last = end();
	for (
		auto list_first = list.begin(), list_last = list.end();
		first != last && list_first != list_last;
		++first, ++list_first
	) {
		*first = *list_first;
	}
}

template <std::size_t Rows, std::size_t Cols, typename T>
constexpr auto RectangularMatrix<Rows, Cols, T>::begin() -> iterator {
	return data_.begin();
}

template <std::size_t Rows, std::size_t Cols, typename T>
constexpr auto RectangularMatrix<Rows, Cols, T>::begin() const -> const_iterator {
	return data_.begin();
}

template <std::size_t Rows, std::size_t Cols, typename T>
constexpr auto RectangularMatrix<Rows, Cols, T>::end() -> iterator {
	return data_.end();
}

template <std::size_t Rows, std::size_t Cols, typename T>
constexpr auto RectangularMatrix<Rows, Cols, T>::end() const -> const_iterator {
	return data_.end();
}

template <std::size_t Rows, std::size_t Cols, typename T>
constexpr auto RectangularMatrix<Rows, Cols, T>::operator[](size_type index) -> reference {
	return data_[index];
}

template <std::size_t Rows, std::size_t Cols, typename T>
constexpr auto RectangularMatrix<Rows, Cols, T>::operator[](size_type index) const -> const_reference {
	return data_[index];
}

template <std::size_t Rows, std::size_t Cols, typename T>
auto RectangularMatrix<Rows, Cols, T>::at(size_type index) -> reference {
	if (index >= Rows) {
		throw std::out_of_range("RectangularMatrix::at");
	}

	return data_.at(index);
}

template <std::size_t Rows, std::size_t Cols, typename T>
auto RectangularMatrix<Rows, Cols, T>::at(size_type index) const -> const_reference {
	if (index >= Rows) {
		throw std::out_of_range("RectangularMatrix::at");
	}

	return data_.at(index);
}

template <std::size_t L, std::size_t M, std::size_t N, typename T>
const RectangularMatrix<L, N, T> operator*(const RectangularMatrix<L, M, T>& m1, const RectangularMatrix<M, N, T>& m2) {
	RectangularMatrix<L, N, T> result;

	for (std::size_t i = 0; i != L; ++i) {
		for (std::size_t j = 0; j != N; ++j) {
			for (std::size_t k = 0; k != M; ++k) {
				result[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}

	return result;
}

template <std::size_t Rows, std::size_t Cols, typename T>
std::istream& operator<<(std::istream& is, RectangularMatrix<Rows, Cols, T>& matrix) {
	for (auto& row: matrix) {
		is >> row;
	}

	return is;
}

template <std::size_t Rows, std::size_t Cols, typename T>
std::ostream& operator<<(std::ostream& os, const RectangularMatrix<Rows, Cols, T>& matrix) {
	std::copy(matrix.begin(), matrix.end(), std::experimental::make_ostream_joiner(os, "\n"));
	return os;
}

#endif  // MATH_MATRIX_RECTANGULAR_MATRIX_HPP_
