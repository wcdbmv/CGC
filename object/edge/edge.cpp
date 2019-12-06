#include "object/edge/edge.hpp"

constexpr Edge::Edge(std::size_t p1, std::size_t p2) noexcept
		: p1_(p1), p2_(p2) {}

constexpr auto Edge::p1() noexcept -> reference {
	return p1_;
}

constexpr auto Edge::p1() const noexcept -> const_reference {
	return p1_;
}

constexpr auto Edge::p2() noexcept -> reference {
	return p2_;
}

constexpr auto Edge::p2() const noexcept -> const_reference {
	return p2_;
}

constexpr auto Edge::operator[](size_type index) -> reference {
	return *(&p1_ + index);
}

constexpr auto Edge::operator[](size_type index) const -> const_reference {
	return *(&p1_ + index);
}

auto Edge::at(size_type index) -> reference {
	if (index >= 2) {
		throw std::out_of_range("Edge::at");
	}

	return *(&p1_ + index);
}

auto Edge::at(size_type index) const -> const_reference {
	if (index >= 2) {
		throw std::out_of_range("Edge::at");
	}

	return *(&p1_ + index);
}
