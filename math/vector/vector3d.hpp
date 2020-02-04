#ifndef MATH_VECTOR_VECTOR3D_HPP_
#define MATH_VECTOR_VECTOR3D_HPP_

#include "vector.hpp"

template <typename T>
class Vector3D : public Vector<3, T> {
public:
	using Base = Vector<3, T>;

	using value_type = typename Base::value_type;
	using reference = typename Base::reference;
	using const_reference = typename Base::const_reference;
	using pointer = typename Base::pointer;
	using const_pointer = typename Base::const_pointer;

	using iterator = typename Base::iterator;
	using const_iterator = typename Base::const_iterator;
	using size_type = typename Base::size_type;

public:
	constexpr Vector3D() noexcept = default;
	constexpr explicit Vector3D(const value_type& value) noexcept;
	constexpr Vector3D(const value_type& x, const value_type& y, const value_type& z = 0) noexcept;

	template <std::size_t OtherSize>
	constexpr Vector3D(const Vector<OtherSize, T>& rhs) noexcept;

	reference x() noexcept;
	constexpr const_reference x() const noexcept;
	reference y() noexcept;
	constexpr const_reference y() const noexcept;
	reference z() noexcept;
	constexpr const_reference z() const noexcept;

	static constexpr Vector3D cross(const Base& lhs, const Base& rhs) noexcept;
};


template <typename T>
constexpr Vector3D<T>::Vector3D(const value_type& value) noexcept
		: Base(value) {}

template <typename T>
constexpr Vector3D<T>::Vector3D(const value_type& x, const value_type& y, const value_type& z) noexcept
		: Base{x, y, z} {}

template <typename T>
template <std::size_t OtherSize>
constexpr Vector3D<T>::Vector3D(const Vector<OtherSize, T>& rhs) noexcept
		: Base(rhs) {}

template <typename T>
auto Vector3D<T>::x() noexcept -> reference {
	return Base::data_[0];
}

template <typename T>
constexpr auto Vector3D<T>::x() const noexcept -> const_reference {
	return Base::data_[0];
}

template <typename T>
auto Vector3D<T>::y() noexcept -> reference {
	return Base::data_[1];
}

template <typename T>
constexpr auto Vector3D<T>::y() const noexcept -> const_reference {
	return Base::data_[1];
}

template <typename T>
auto Vector3D<T>::z() noexcept -> reference {
	return Base::data_[2];
}

template <typename T>
constexpr auto Vector3D<T>::z() const noexcept -> const_reference {
	return Base::data_[2];
}

template <typename T>
constexpr auto Vector3D<T>::cross(const Base& lhs, const Base& rhs) noexcept -> Vector3D {
	return {
		lhs[1] * rhs[2] - lhs[2] * rhs[1],
		lhs[2] * rhs[0] - lhs[0] * rhs[2],
		lhs[0] * rhs[1] - lhs[1] * rhs[0]
	};
}

#endif  // MATH_VECTOR_VECTOR3D_HPP_
