#ifndef OBJECT_FACE_FACE_HPP_
#define OBJECT_FACE_FACE_HPP_

#include <array>
#include <initializer_list>
#include <stdexcept>

template <size_t VerticesCount>
class Face {
public:
	using Base = std::array<size_t, VerticesCount>;

	using value_type = typename Base::value_type;
	using reference = typename Base::reference;
	using const_reference = typename Base::const_reference;
	using pointer = typename Base::pointer;
	using const_pointer = typename Base::const_pointer;

	using iterator = typename Base::iterator;
	using const_iterator = typename Base::const_iterator;
	using size_type = typename Base::size_type;

public:
	constexpr Face(std::initializer_list<value_type> list);

	constexpr iterator begin() noexcept;
	constexpr const_iterator begin() const noexcept;
	constexpr iterator end() noexcept;
	constexpr const_iterator end() const noexcept;

	constexpr reference operator[](size_type index);
	constexpr const_reference operator[](size_type index) const;
	reference at(size_type index);
	[[nodiscard]] const_reference at(size_type index) const;

private:
	std::array<size_t, VerticesCount> vertex_index_;
};

template <size_t VerticesCount>
constexpr Face<VerticesCount>::Face(std::initializer_list<value_type> list) {
	auto first = begin(), last = end();
	for (
		auto list_first = list.begin(), list_last = list.end();
		first != last && list_first != list_last;
		++first, ++list_first
	) {
		*first = *list_first;
	}

	if (first != last) {
		throw std::invalid_argument("Face<VerticesCount>::Face(std::initializer_list<size_t>)");
	}
}

template <size_t VerticesCount>
constexpr auto Face<VerticesCount>::begin() noexcept -> iterator {
	return vertex_index_.begin();
}

template <size_t VerticesCount>
constexpr auto Face<VerticesCount>::begin() const noexcept -> const_iterator {
	return vertex_index_.begin();
}

template <size_t VerticesCount>
constexpr auto Face<VerticesCount>::end() noexcept -> iterator {
	return vertex_index_.end();
}

template <size_t VerticesCount>
constexpr auto Face<VerticesCount>::end() const noexcept -> const_iterator {
	return vertex_index_.end();
}

template <size_t VerticesCount>
constexpr auto Face<VerticesCount>::operator[](size_type index) -> reference {
	return vertex_index_[index];
}

template <size_t VerticesCount>
constexpr auto Face<VerticesCount>::operator[](size_type index) const -> const_reference {
	return vertex_index_[index];
}

template <size_t VerticesCount>
auto Face<VerticesCount>::at(size_type index) -> reference {
	if (index >= VerticesCount) {
		throw std::out_of_range("Face::at");
	}

	return vertex_index_[index];
}

template <size_t VerticesCount>
auto Face<VerticesCount>::at(size_type index) const -> const_reference {
	if (index >= VerticesCount) {
		throw std::out_of_range("Face::at");
	}

	return vertex_index_[index];
}

#endif  // OBJECT_FACE_FACE_HPP_
