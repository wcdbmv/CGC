#include "object/vertex/vertex.hpp"

constexpr Vertex::Vertex(const value_type& value) noexcept
		: Base(value) {}

constexpr Vertex::Vertex(const value_type& x, const value_type& y, const value_type& z) noexcept
		: Base(x, y, z) {}
