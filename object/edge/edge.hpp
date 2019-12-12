#ifndef OBJECT_EDGE_EDGE_HPP_
#define OBJECT_EDGE_EDGE_HPP_

#include <stdexcept>

class Edge {
public:
	using value_type = size_t;
	using reference = size_t&;
	using const_reference = const size_t&;
	using pointer = size_t*;
	using const_pointer = const size_t*;

	using iterator = value_type*;
	using const_iterator = const value_type*;
	using size_type = size_t;

public:
	constexpr explicit Edge(size_t p1 = 0, size_t p2 = 0) noexcept;

	constexpr reference p1() noexcept;
	[[nodiscard]] constexpr const_reference p1() const noexcept;
	constexpr reference p2() noexcept;
	[[nodiscard]] constexpr const_reference p2() const noexcept;

	constexpr reference operator[](size_type index);
	constexpr const_reference operator[](size_type index) const;
	reference at(size_type index);
	[[nodiscard]] const_reference at(size_type index) const;

private:
	std::size_t p1_, p2_;
};

inline constexpr Edge::Edge(std::size_t p1, std::size_t p2) noexcept
	: p1_(p1), p2_(p2) {}

inline constexpr auto Edge::p1() noexcept -> reference {
	return p1_;
}

inline constexpr auto Edge::p1() const noexcept -> const_reference {
	return p1_;
}

inline constexpr auto Edge::p2() noexcept -> reference {
	return p2_;
}

inline constexpr auto Edge::p2() const noexcept -> const_reference {
	return p2_;
}

inline constexpr auto Edge::operator[](size_type index) -> reference {
	return *(&p1_ + index);
}

inline constexpr auto Edge::operator[](size_type index) const -> const_reference {
	return *(&p1_ + index);
}

inline auto Edge::at(size_type index) -> reference {
	if (index >= 2) {
		throw std::out_of_range("Edge::at");
	}

	return *(&p1_ + index);
}

inline auto Edge::at(size_type index) const -> const_reference {
	if (index >= 2) {
		throw std::out_of_range("Edge::at");
	}

	return *(&p1_ + index);
}

#endif  // OBJECT_EDGE_EDGE_HPP_
