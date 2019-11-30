#ifndef MATH_VECTOR_VECTOR_HPP_
#define MATH_VECTOR_VECTOR_HPP_

#include <initializer_list>
#include <iostream>

template <std::size_t Size, typename T>
class Vector {
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	using iterator = value_type*;
	using const_iterator = const value_type*;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

public:
	constexpr Vector() noexcept;
	constexpr explicit Vector(const value_type& value) noexcept;
	constexpr Vector(std::initializer_list<value_type> list) noexcept;

	constexpr iterator begin() noexcept;
	constexpr const_iterator begin() const noexcept;
	constexpr iterator end() noexcept;
	constexpr const_iterator end() const noexcept;

	constexpr void fill(const value_type& value) noexcept;
	[[nodiscard]] constexpr size_type size() const noexcept;

	constexpr reference operator[](size_type index) noexcept;
	constexpr const_reference operator[](size_type index) const noexcept;
	constexpr reference at(size_type index);
	constexpr const_reference at(size_type index) const;

	constexpr Vector& operator+=(const Vector& rhs) noexcept;
	constexpr Vector& operator-=(const Vector& rhs) noexcept;
	constexpr Vector& operator*=(const Vector& rhs) noexcept;
	constexpr Vector& operator/=(const Vector& rhs);
	constexpr Vector& operator*=(double rhs) noexcept;
	constexpr Vector& operator/=(double rhs);

	constexpr value_type sum() const;
	static constexpr value_type dot(const Vector& lhs, const Vector& rhs) noexcept;

	std::enable_if_t<std::is_integral_v<T>, double> length() const;

	std::enable_if_t<std::is_floating_point_v<T>> normalize();

	template <std::size_t _Size, typename _T>
	friend constexpr Vector<_Size, _T> operator+(Vector<_Size, _T> lhs, const Vector<_Size, _T>& rhs) noexcept;
	template <std::size_t _Size, typename _T>
	friend constexpr Vector<_Size, _T> operator-(Vector<_Size, _T> lhs, const Vector<_Size, _T>& rhs) noexcept;
	template <std::size_t _Size, typename _T>
	friend constexpr Vector<_Size, _T> operator*(Vector<_Size, _T> lhs, const Vector<_Size, _T>& rhs) noexcept;
	template <std::size_t _Size, typename _T>
	friend constexpr Vector<_Size, _T> operator*(Vector<_Size, _T> lhs, const Vector<_Size, _T>& rhs) noexcept;
	template <std::size_t _Size, typename _T>
	friend constexpr Vector<_Size, _T> operator/(Vector<_Size, _T> lhs, const Vector<_Size, _T>& rhs);
	template <std::size_t _Size, typename _T>
	friend constexpr Vector<_Size, _T> operator*(Vector<_Size, _T> lhs, double rhs) noexcept;
	template <std::size_t _Size, typename _T>
	friend constexpr Vector<_Size, _T> operator*(double lhs, Vector<_Size, _T> rhs) noexcept;
	template <std::size_t _Size, typename _T>
	friend constexpr Vector<_Size, _T> operator/(Vector<_Size, _T> lhs, double rhs);

	template <std::size_t _Size, typename _T>
	friend std::istream& operator>>(std::istream& is, Vector<_Size, _T>& vector);
	template <std::size_t _Size, typename _T>
	friend std::ostream& operator<<(std::ostream& os, const Vector<_Size, _T>& vector);

protected:
	T data_[Size];
};

#include <cmath>
#include <experimental/iterator>
#include <numeric>

template <std::size_t Size, typename T>
constexpr Vector<Size, T>::Vector() noexcept
	: data_{} {}

template <std::size_t Size, typename T>
constexpr Vector<Size, T>::Vector(const value_type& value) noexcept : Vector() {
	fill(value);
}

template <std::size_t Size, typename T>
constexpr Vector<Size, T>::Vector(std::initializer_list<value_type> list) noexcept : Vector() {
	// std::copy_n(list.begin(), min(size(), list.size()), begin());
	auto first = begin(), last = end();
	for (auto list_first = list.begin(), list_last = list.end(); first != last && list_first != list_last; ++first, ++list_first) {
		*first = *list_first;
	}
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::begin() noexcept -> iterator {
	// return std::addressof(data_[0]);
	return data_;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::begin() const noexcept -> const_iterator {
	return data_;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::end() noexcept -> iterator {
	return data_ + Size;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::end() const noexcept -> const_iterator {
	return data_ + Size;
}

template <std::size_t Size, typename T>
constexpr void Vector<Size, T>::fill(const value_type& value) noexcept {
	for (auto&& it: *this) {
		it = value;
	}
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::size() const noexcept -> size_type {
	return Size;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::operator[](size_type index) noexcept -> reference {
	return data_[index];
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::operator[](size_type index) const noexcept -> const_reference {
	return data_[index];
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::at(size_type index) -> reference {
	return index < Size ? data_[index] : throw std::out_of_range("Vector::at");
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::at(size_type index) const -> const_reference {
	return index < Size ? data_[index] : throw std::out_of_range("Vector::at");
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::operator+=(const Vector& rhs) noexcept -> Vector& {
	for (size_type i = 0; i != Size; ++i) {
		data_[i] += rhs.data_[i];
	}

	return *this;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::operator-=(const Vector& rhs) noexcept -> Vector& {
	for (size_type i = 0; i != Size; ++i) {
		data_[i] -= rhs.data_[i];
	}

	return *this;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::operator*=(const Vector& rhs) noexcept -> Vector& {
	for (size_type i = 0; i != Size; ++i) {
		data_[i] *= rhs.data_[i];
	}

	return *this;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::operator/=(const Vector& rhs)-> Vector& {
	for (size_type i = 0; i != Size; ++i) {
		// data_[i] /= rhs.data_[i] ?: throw std::overflow_error("Vector::operator/=");
		data_[i] /= rhs.data_[i] ? rhs.data_[i] : throw std::overflow_error("Vector::operator/=");
	}

	return *this;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::operator*=(double rhs) noexcept -> Vector& {
	for (auto&& it: *this) {
		it *= rhs;
	}

	return *this;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::operator/=(double rhs) -> Vector& {
	for (auto&& it: *this) {
		it /= rhs;
	}

	return *this;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::sum() const -> value_type {
	return std::accumulate(begin(), end(), T{});
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::dot(const Vector& lhs, const Vector& rhs) noexcept -> value_type {
	return (lhs * rhs).sum();
}

template <std::size_t Size, typename T>
auto Vector<Size, T>::length() const -> std::enable_if_t<std::is_integral_v<T>, double> {
	return std::sqrt(dot(*this, *this));
}

template <std::size_t Size, typename T>
std::enable_if_t<std::is_floating_point_v<T>> Vector<Size, T>::normalize() {
	*this *= 1.0 / length();
}

template <std::size_t Size, typename T>
constexpr Vector<Size, T> operator+(Vector<Size, T> lhs, const Vector<Size, T>& rhs) noexcept {
	return lhs += rhs;
}

template <std::size_t Size, typename T>
constexpr Vector<Size, T> operator-(Vector<Size, T> lhs, const Vector<Size, T>& rhs) noexcept {
	return lhs -= rhs;
}

template <std::size_t Size, typename T>
constexpr Vector<Size, T> operator*(Vector<Size, T> lhs, const Vector<Size, T>& rhs) noexcept {
	return lhs *= rhs;
}

template <std::size_t Size, typename T>
constexpr Vector<Size, T> operator/(Vector<Size, T> lhs, const Vector<Size, T>& rhs) {
	return lhs /= rhs;
}

template <std::size_t Size, typename T>
constexpr Vector<Size, T> operator*(Vector<Size, T> lhs, double rhs) noexcept {
	return lhs *= rhs;
}

template <std::size_t Size, typename T>
constexpr Vector<Size, T> operator*(double lhs, Vector<Size, T> rhs) noexcept {
	return rhs *= lhs;
}

template <std::size_t Size, typename T>
constexpr Vector<Size, T> operator/(Vector<Size, T> lhs, double rhs) noexcept {
	return lhs /= rhs;
}

template <std::size_t Size, typename T>
std::istream& operator>>(std::istream& is, Vector<Size, T>& vector) {
	for (auto&& it: vector) {
		is >> it;
	}

	return is;
}

template <std::size_t Size, typename T>
std::ostream& operator<<(std::ostream& os, const Vector<Size, T>& vector) {
	std::copy(vector.begin(), vector.end(), std::experimental::make_ostream_joiner(os, " "));
	return os;
}

#endif  // MATH_VECTOR_VECTOR_HPP_
