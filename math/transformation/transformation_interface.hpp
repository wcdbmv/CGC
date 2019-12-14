#ifndef LAB04_TRANSFORMATIONS_TRANSFORMATION_INTERFACE_HPP_
#define LAB04_TRANSFORMATIONS_TRANSFORMATION_INTERFACE_HPP_

#include "math/matrix/matrix4x4.hpp"

class ITransformation : public Matrix4x4<double> {
public:
	ITransformation();
	ITransformation(const ITransformation&) = delete;

protected:
	void ResetMatrix();
};

#endif  // LAB04_TRANSFORMATIONS_TRANSFORMATION_INTERFACE_HPP_
