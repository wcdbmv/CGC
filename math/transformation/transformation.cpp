#include "transformation.hpp"

Transformation::Transformation(ITransformation& interface)
		: matrix_(interface) {}

void Transformation::Transform(Mesh& mesh) {
	for (auto&& vertex: mesh.vertices) {
		vertex = matrix_ * vertex;
	}
}
