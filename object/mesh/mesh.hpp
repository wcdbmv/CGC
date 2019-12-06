#ifndef OBJECT_MESH_MESH_HPP_
#define OBJECT_MESH_MESH_HPP_

#include <vector>
#include "object/edge/edge.hpp"
#include "object/face/triangle_face.hpp"
#include "object/vertex/vertex.hpp"

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;
	std::vector<TriangleFace> faces;
};

#endif  // OBJECT_MESH_MESH_HPP_
