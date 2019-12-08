#ifndef SURFACE_SURFACE_HPP_
#define SURFACE_SURFACE_HPP_

#include "function/function/function.hpp"
#include "math/grid/grid.hpp"
#include "object/mesh/mesh.hpp"

class Surface {
public:
	static Mesh build(Function& function, const Grid& grid);
};

Mesh Surface::build(Function& function, const Grid& grid) {
	const auto xrange = grid.x.range();
	const auto yrange = grid.y.range();

	const size_t outer_grid_size = xrange.size() * yrange.size();
	const size_t inner_grid_size = (xrange.size() - 1) * (yrange.size() - 1);

	std::vector<Vertex> vertices;
	std::vector<Edge> edges;
	std::vector<TriangleFace> faces;

	vertices.reserve(inner_grid_size + outer_grid_size);
	faces.reserve(4 * inner_grid_size);

	for (auto&& x: xrange) {
		for (auto&& y: yrange) {
			const double z = function(x, y);
			vertices.emplace_back(x, y, z);
		}
	}

	const double half_dx = grid.x.delta() / 2;
	const double half_dy = grid.y.delta() / 2;

	for (size_t i = 0; i + 1 < xrange.size(); ++i) {
		for (size_t j = 0; j + 1 < yrange.size(); ++j) {
			const double x = xrange[i] + half_dx;
			const double y = yrange[i] + half_dy;
			const double z = function(x, y);
			vertices.emplace_back(x, y, z);
		}
	}

	size_t inner = outer_grid_size;
	for (size_t i = 0; i + 1 < xrange.size(); ++i) {
		for (size_t j = 0; j + 1 < yrange.size(); ++j) {
			++inner;
			const size_t lt = i * xrange.size() + j;
			const size_t rt = lt + 1;
			const size_t lb = lt + xrange.size();
			const size_t rb = lb + 1;

			faces.emplace_back(lt, rt, inner);
			faces.emplace_back(rt, rb, inner);
			faces.emplace_back(rb, lb, inner);
			faces.emplace_back(lb, lt, inner);
		}
	}

	return {vertices, edges, faces};
}

#endif  // SURFACE_SURFACE_HPP_
