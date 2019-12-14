#ifndef MATH_VECTOR_VECTOR4D_HPP_
#define MATH_VECTOR_VECTOR4D_HPP_

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
	constexpr HomogeneousVector3D(const value_type& x, const value_type& y, const value_type& z = 0) noexcept;
	constexpr HomogeneousVector3D(std::initializer_list<value_type> list) noexcept;

	reference x() noexcept;
	constexpr const_reference x() const noexcept;
	reference y() noexcept;
	constexpr const_reference y() const noexcept;
	reference z() noexcept;
	constexpr const_reference z() const noexcept;
	reference w() noexcept;
	constexpr const_reference w() const noexcept;

	T Length();
	void Normalize();

	static T Dot(const HomogeneousVector3D&, const HomogeneousVector3D&);
	static HomogeneousVector3D Cross(const HomogeneousVector3D&, const HomogeneousVector3D&);
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
T HomogeneousVector3D<T>::Length() {
	const auto x = (*this)[0];
	const auto y = (*this)[1];
	const auto z = (*this)[2];

	return std::sqrt(x * x + y * y + z * z);
}

template <typename T>
void HomogeneousVector3D<T>::Normalize() {
	const T norm = 1 / Length();

	for (std::size_t i = 0; i < Vector<4, T>::size() - 1; ++i)
		(*this)[i] *= norm;
}

template <typename T>
T HomogeneousVector3D<T>::Dot(const HomogeneousVector3D<T>& v1, const HomogeneousVector3D<T>& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

template <typename T>
HomogeneousVector3D<T> HomogeneousVector3D<T>::Cross(const HomogeneousVector3D<T>& v1, const HomogeneousVector3D<T>& v2) {
	HomogeneousVector3D<T> result;

	result[0] = v1[2] * v2[1] - v1[1] * v2[2];
	result[1] = v1[0] * v2[2] - v1[2] * v2[0];
	result[2] = v1[1] * v2[0] - v1[0] * v2[1];
	result[3] = 1;

	return result;
}


#endif  // MATH_VECTOR_VECTOR4D_HPP_
