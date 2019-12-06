#ifndef OBJECT_FACE_FACE3_HPP_
#define OBJECT_FACE_FACE3_HPP_

#include "object/face/face.hpp"

class Face3 : public Face<3> {
public:
	using Base = Face<3>;

	using value_type = typename Base::value_type;
	using reference = typename Base::reference;
	using const_reference = typename Base::const_reference;
	using pointer = typename Base::pointer;
	using const_pointer = typename Base::const_pointer;

	using iterator = typename Base::iterator;
	using const_iterator = typename Base::const_iterator;
	using size_type = typename Base::size_type;

public:
	constexpr Face3(value_type v1, value_type v2, value_type v3) noexcept;
	constexpr Face3(std::initializer_list<value_type> list);
};

constexpr Face3::Face3(value_type v1, value_type v2, value_type v3) noexcept
		: Base({v1, v2, v3}) {}

constexpr Face3::Face3(std::initializer_list<value_type> list)
		: Face(list) {}

#endif  // OBJECT_FACE_FACE3_HPP_
