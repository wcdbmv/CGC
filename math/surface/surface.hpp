#ifndef MATH_SURFACE_SURFACE_HPP_
#define MATH_SURFACE_SURFACE_HPP_

#include <vector>
#include "../function/function.hpp"
#include "../region/region.hpp"
#include "../vector/vector3d.hpp"

class Surface {
public:
	Surface(Function& function, const Region& region);

	void calc_nodes();
private:
	Function& function_;
	const Region& region_;

//	std::vector<std::vector<Vector3D<double>>> nodes_;
};

#endif  // MATH_SURFACE_SURFACE_HPP_
