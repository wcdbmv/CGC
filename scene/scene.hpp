#ifndef SCENE_SCENE_HPP_
#define SCENE_SCENE_HPP_

#include "object/camera/camera.hpp"
#include "object/mesh/mesh.hpp"

class Scene {
public:
	std::vector<Mesh> meshes;
	Camera camera;
};

#endif  // SCENE_SCENE_HPP_
