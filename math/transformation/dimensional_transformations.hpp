#ifndef LAB04_TRANSFORMATIONS_DIMENSIONAL_TRANSFORMATIONS_HPP_
#define LAB04_TRANSFORMATIONS_DIMENSIONAL_TRANSFORMATIONS_HPP_

#include <cmath>

#include "math/transformation/transformation_interface.hpp"

namespace DimensionalTransformations {

class RotationOX : public ITransformation {
public:
	explicit RotationOX(double);
	RotationOX(const RotationOX&) = delete;
};

class RotationOY : public ITransformation {
public:
	explicit RotationOY(double);
	RotationOY(const RotationOY&) = delete;
};

class RotationOZ : public ITransformation {
public:
	explicit RotationOZ(double);
	RotationOZ(const RotationOZ&) = delete;
};

class Rotation : public ITransformation {
public:
	explicit Rotation(const Vector3D<double>&, double);
	Rotation(const Rotation&) = delete;
};

class Translation : public ITransformation {
public:
	explicit Translation(const Vector3D<double>&);
	Translation(const Translation&) = delete;
};

class Scaling : public ITransformation {
public:
	explicit Scaling(double);
	Scaling(const Scaling&) = delete;
};

}  // namespace DimensionalTransformations

#endif  // LAB04_TRANSFORMATIONS_DIMENSIONAL_TRANSFORMATIONS_HPP_
