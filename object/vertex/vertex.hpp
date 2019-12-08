#ifndef OBJECT_VERTEX_VERTEX_HPP_
#define OBJECT_VERTEX_VERTEX_HPP_

#include "math/vector/vector3d.hpp"

class Vertex : public Vector3D<double> {
public:
	using Base = Vector3D<double>;

	using value_type = typename Base::value_type;
	using reference = typename Base::reference;
	using const_reference = typename Base::const_reference;
	using pointer = typename Base::pointer;
	using const_pointer = typename Base::const_pointer;

	using iterator = typename Base::iterator;
	using const_iterator = typename Base::const_iterator;
	using size_type = typename Base::size_type;

public:
	constexpr Vertex() noexcept = default;
	constexpr explicit Vertex(const value_type& value) noexcept;
	constexpr Vertex(const value_type& x, const value_type& y, const value_type& z) noexcept;
};

inline constexpr Vertex::Vertex(const value_type& value) noexcept
	: Base(value) {}

inline constexpr Vertex::Vertex(const value_type& x, const value_type& y, const value_type& z) noexcept
	: Base(x, y, z) {}

#endif  // OBJECT_VERTEX_VERTEX_HPP_
