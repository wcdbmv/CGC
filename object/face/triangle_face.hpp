#ifndef OBJECT_FACE_FACE3_HPP_
#define OBJECT_FACE_FACE3_HPP_

#include "object/face/face.hpp"

class TriangleFace : public Face<3> {
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
	constexpr TriangleFace(value_type v1, value_type v2, value_type v3) noexcept;
	constexpr TriangleFace(std::initializer_list<value_type> list);
};

constexpr TriangleFace::TriangleFace(value_type v1, value_type v2, value_type v3) noexcept
		: Base({v1, v2, v3}) {}

constexpr TriangleFace::TriangleFace(std::initializer_list<value_type> list)
		: Base(list) {}

#endif  // OBJECT_FACE_FACE3_HPP_
