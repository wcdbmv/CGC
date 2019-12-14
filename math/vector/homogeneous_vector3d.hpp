#ifndef MATH_VECTOR_HOMOGENEOUS_VECTOR_3D_HPP_
#define MATH_VECTOR_HOMOGENEOUS_VECTOR_3D_HPP_

#include "vector.hpp"

template <typename T>
class HomogeneousVector3D : public Vector<4, T> {
public:
	using Base = Vector<4, T>;

	using value_type = typename Base::value_type;
	using reference = typename Base::reference;
	using const_reference = typename Base::const_reference;
	using pointer = typename Base::pointer;
	using const_pointer = typename Base::const_pointer;

	using iterator = typename Base::iterator;
	using const_iterator = typename Base::const_iterator;
	using size_type = typename Base::size_type;

public:
	constexpr HomogeneousVector3D() noexcept;
	constexpr explicit HomogeneousVector3D(const value_type& value) noexcept;
	constexpr HomogeneousVector3D(const value_type& x, const value_type& y, const value_type& z) noexcept;
	constexpr HomogeneousVector3D(const Vector<3, T>& rhs) noexcept;
	constexpr HomogeneousVector3D(std::initializer_list<value_type> list) noexcept;

	reference x() noexcept;
	constexpr const_reference x() const noexcept;
	reference y() noexcept;
	constexpr const_reference y() const noexcept;
	reference z() noexcept;
	constexpr const_reference z() const noexcept;
	reference w() noexcept;
	constexpr const_reference w() const noexcept;

	value_type length3d() const;
	void normalize3d();

	static value_type dot3d(const HomogeneousVector3D&, const HomogeneousVector3D&);
	static HomogeneousVector3D cross3d(const HomogeneousVector3D&, const HomogeneousVector3D&);
};


template <typename T>
constexpr HomogeneousVector3D<T>::HomogeneousVector3D() noexcept
		: Base{0, 0, 0, 1} {}
template <typename T>
constexpr HomogeneousVector3D<T>::HomogeneousVector3D(const value_type& value) noexcept
		: Base(value) {}

template <typename T>
constexpr HomogeneousVector3D<T>::HomogeneousVector3D(const value_type& x, const value_type& y, const value_type& z) noexcept
		: Base{x, y, z, 1} {}

template <typename T>
constexpr HomogeneousVector3D<T>::HomogeneousVector3D(const Vector<3, T>& rhs) noexcept
		: Base{rhs[0], rhs[1], rhs[2], 1} {}

template <typename T>
constexpr HomogeneousVector3D<T>::HomogeneousVector3D(std::initializer_list<value_type> list) noexcept
		: Base(list) {}

template <typename T>
auto HomogeneousVector3D<T>::x() noexcept -> reference {
	return Base::data_[0];
}

template <typename T>
constexpr auto HomogeneousVector3D<T>::x() const noexcept -> const_reference {
	return Base::data_[0];
}

template <typename T>
auto HomogeneousVector3D<T>::y() noexcept -> reference {
	return Base::data_[1];
}

template <typename T>
constexpr auto HomogeneousVector3D<T>::y() const noexcept -> const_reference {
	return Base::data_[1];
}

template <typename T>
auto HomogeneousVector3D<T>::z() noexcept -> reference {
	return Base::data_[2];
}

template <typename T>
constexpr auto HomogeneousVector3D<T>::z() const noexcept -> const_reference {
	return Base::data_[2];
}

template <typename T>
auto HomogeneousVector3D<T>::w() noexcept -> reference {
	return Base::data_[3];
}

template <typename T>
constexpr auto HomogeneousVector3D<T>::w() const noexcept -> const_reference {
	return Base::data_[3];
}

template <typename T>
auto HomogeneousVector3D<T>::length3d() const -> value_type {
	const auto x = (*this)[0];
	const auto y = (*this)[1];
	const auto z = (*this)[2];

	return std::sqrt(x * x + y * y + z * z);
}

template <typename T>
void HomogeneousVector3D<T>::normalize3d() {
	const T norm = 1 / length3d();

	for (std::size_t i = 0; i < Base::size() - 1; ++i) {
		(*this)[i] *= norm;
	}
}

template <typename T>
auto HomogeneousVector3D<T>::dot3d(const HomogeneousVector3D<T>& v1, const HomogeneousVector3D<T>& v2) -> value_type {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

template <typename T>
auto HomogeneousVector3D<T>::cross3d(const HomogeneousVector3D<T>& v1, const HomogeneousVector3D<T>& v2) -> HomogeneousVector3D {
	HomogeneousVector3D<T> result;

	result[0] = v1[2] * v2[1] - v1[1] * v2[2];
	result[1] = v1[0] * v2[2] - v1[2] * v2[0];
	result[2] = v1[1] * v2[0] - v1[0] * v2[1];
	result[3] = 1;

	return result;
}


#endif  // MATH_VECTOR_HOMOGENEOUS_VECTOR_3D_HPP_
