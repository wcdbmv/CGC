#ifndef SURFACE_SURFACE_HPP_
#define SURFACE_SURFACE_HPP_

#include "function/function/function.hpp"
#include "math/grid/grid.hpp"
#include "object/mesh/mesh.hpp"

class Surface {
public:
	static Mesh build(Function& function, const Grid& grid);
};

#endif  // SURFACE_SURFACE_HPP_
