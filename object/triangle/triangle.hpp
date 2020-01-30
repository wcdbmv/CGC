#ifndef OBJECT_TRIANGLE_TRIANGLE_HPP_
#define OBJECT_TRIANGLE_TRIANGLE_HPP_

#include "object/vertex/vertex.hpp"

class Triangle {
public:
	using value_type = Vertex;
	using reference = Vertex&;
	using const_reference = const Vertex&;
	using pointer = Vertex*;
	using const_pointer = const Vertex*;

	using iterator = value_type*;
	using const_iterator = const value_type*;
	using size_type = size_t;

public:
	constexpr Triangle() noexcept;
	constexpr Triangle(const Vertex& a, const Vertex& b, const Vertex& c) noexcept;

	reference a() noexcept;
	[[nodiscard]] constexpr const_reference a() const noexcept;
	reference b() noexcept;
	[[nodiscard]] constexpr const_reference b() const noexcept;
	reference c() noexcept;
	[[nodiscard]] constexpr const_reference c() const noexcept;

	constexpr reference operator[](size_type index);
	constexpr const_reference operator[](size_type index) const;
	reference at(size_type index);
	[[nodiscard]] const_reference at(size_type index) const;

	template <typename Point>
	Vertex barycentric(const Point& p, double square) const;

private:
	Vertex a_, b_, c_;
};


inline constexpr Triangle::Triangle() noexcept
		: a_(0, 0, 0), b_(0, 1, 0), c_(1, 0, 0) {}

inline constexpr Triangle::Triangle(const Vertex& a, const Vertex& b, const Vertex& c) noexcept
		: a_(a), b_(b), c_(c) {}

inline auto Triangle::a() noexcept -> reference {
	return a_;
}

inline constexpr auto Triangle::a() const noexcept -> const_reference {
	return a_;
}

inline auto Triangle::b() noexcept -> reference {
	return b_;
}

inline constexpr auto Triangle::b() const noexcept -> const_reference {
	return b_;
}

inline auto Triangle::c() noexcept -> reference {
	return c_;
}

inline constexpr auto Triangle::c() const noexcept -> const_reference {
	return c_;
}

inline constexpr auto Triangle::operator[](size_type index) -> reference {
	return *(&a_ + index);
}

inline constexpr auto Triangle::operator[](size_type index) const -> const_reference {
	return *(&a_ + index);
}

inline auto Triangle::at(size_type index) -> reference {
	if (index >= 2) {
		throw std::out_of_range("Triangle::at");
	}

	return *(&a_ + index);
}

inline auto Triangle::at(size_type index) const -> const_reference {
	if (index >= 2) {
		throw std::out_of_range("Triangle::at");
	}

	return *(&a_ + index);
}

template <typename Point>
Vertex Triangle::barycentric(const Point& p, double square) const {
	const double x = ((p.y() - c_.y()) * (b_.x() - c_.x()) + (b_.y() - c_.y()) * (c_.x() - p.x())) / square;
	const double y = ((p.y() - a_.y()) * (c_.x() - a_.x()) + (c_.y() - a_.y()) * (a_.x() - p.x())) / square;
	const double z = 1 - x - y;
	return {x, y, z};
}

#endif  // OBJECT_TRIANGLE_TRIANGLE_HPP_
