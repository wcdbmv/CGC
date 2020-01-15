#ifndef MATH_MATRIX_MATRIX4X4_HPP_
#define MATH_MATRIX_MATRIX4X4_HPP_

#include "math/matrix/matrix.hpp"
#include "math/vector/homogeneous_vector3d.hpp"
#include "math/vector/vector3d.hpp"

template <typename T>
class Matrix4x4 : public Matrix<4, T> {
	static_assert(std::is_arithmetic<T>::value, "Type must be arithmetic!");

public:
	Matrix4x4();
	Matrix4x4(std::initializer_list<Vector<4, T>>);
	Matrix4x4(const RectangularMatrix<4, 4, T>&);
	Matrix4x4(const Matrix4x4&);
	Matrix4x4(Matrix4x4&&) noexcept;
	~Matrix4x4() = default;

	Matrix4x4& operator=(const Matrix4x4&);
	Matrix4x4& operator=(Matrix4x4&&) noexcept;
	Matrix4x4& operator=(std::initializer_list<Vector<4, T>>);

	HomogeneousVector3D<T> operator*(const HomogeneousVector3D<T>&) const;
	Matrix4x4 operator*(const T&) const;
	Vector3D<T> operator*(const Vector3D<T>&) const;

	template <typename U>
	friend HomogeneousVector3D<U> operator*(const HomogeneousVector3D<U>&, const Matrix4x4<U>&);
};

template <typename T>
Matrix4x4<T>::Matrix4x4()
		: Matrix<4, T>() {}

template <typename T>
Matrix4x4<T>::Matrix4x4(std::initializer_list<Vector<4, T>> lst)
		: Matrix<4, T>(lst) {}

template <typename T>
Matrix4x4<T>::Matrix4x4(const RectangularMatrix<4, 4, T>& rhs)
		: Matrix<4, T>(rhs) {}

template <typename T>
Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& other)
		: Matrix<4, T>(other) {}

template <typename T>
Matrix4x4<T>::Matrix4x4(Matrix4x4<T>&& other) noexcept
		: Matrix<4, T>(std::move(other)) {}

template <typename T>
Matrix4x4<T>& Matrix4x4<T>::operator=(const Matrix4x4& rhs) {
	Matrix<4, T>::operator=(rhs);
	return *this;
}

template <typename T>
Matrix4x4<T>& Matrix4x4<T>::operator=(Matrix4x4&& rhs) noexcept {
	Matrix<4, T>::operator=(std::move(rhs));
	return *this;
}

template <typename T>
Matrix4x4<T>& Matrix4x4<T>::operator=(std::initializer_list<Vector<4, T>> lst) {
	*this = Matrix4x4(lst);
	return *this;
}

template <typename T>
HomogeneousVector3D<T> Matrix4x4<T>::operator*(const HomogeneousVector3D<T>& vector) const {
	HomogeneousVector3D<T> result = {0, 0, 0, 0};

	for (std::size_t i = 0; i < 4; ++i) {
		for (std::size_t j = 0; j < 4; ++j) {
			result[i] += (*this)[i][j] * vector[j];
		}
	}

	return result;
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator*(const T& value) const {
	Matrix4x4<T> result = *this;

	for (std::size_t i = 0; i < 4; ++i) {
		for (std::size_t j = 0; j < 4; ++j) {
			result.data_[i][j] *= value;
		}
	}

	return result;
}

template <typename T>
Vector3D<T> Matrix4x4<T>::operator*(const Vector3D<T>& point) const {
	Vector<4, T> vector = {point.x(), point.y(), point.z(), 1};
	Vector<4, T> result = {0, 0, 0, 0};

	for (std::size_t i = 0; i < 4; ++i) {
		for (std::size_t j = 0; j < 4; ++j) {
			result[i] += (*this)[i][j] * vector[j];
		}
	}

	return Vector3D<T>(result[0], result[1], result[2]);
}

template <typename T>
HomogeneousVector3D<T> operator*(const HomogeneousVector3D<T>& vector, const Matrix4x4<T>& matrix) {
	HomogeneousVector3D<T> result = {0, 0, 0, 0};

	for (std::size_t i = 0; i < 4; ++i) {
		for (std::size_t j = 0; j < 4; ++j) {
			result[i] += matrix[i][j] * vector[j];
		}
	}

	return result;
}

#endif  // MATH_MATRIX_MATRIX4X4_HPP_
