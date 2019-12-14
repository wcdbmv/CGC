#ifndef LAB04_TRANSFORMATIONS_TRANSFORMATION_HPP_
#define LAB04_TRANSFORMATIONS_TRANSFORMATION_HPP_

#include "transformation_interface.hpp"
#include "object/mesh/mesh.hpp"

class Transformation {
public:
	explicit Transformation(ITransformation& interface);
	~Transformation() = default;

	void Transform(Mesh& object);

private:
	Matrix4x4<double> matrix_ = Matrix4x4<double>();
};

#endif  // LAB04_TRANSFORMATIONS_TRANSFORMATION_HPP_
