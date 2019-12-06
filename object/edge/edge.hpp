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

#endif  // OBJECT_EDGE_EDGE_HPP_
