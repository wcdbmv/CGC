#include "surface.hpp"

Surface::Surface(Function& function, const Region& region) :
		function_(function),
		region_(region) {

}

#include <QtDebug>

void Surface::calc_nodes() {
	const auto xrange = region_.x.range();
	const auto yrange = region_.y.range();
	const auto z_min = region_.z.left();
	const auto z_max = region_.z.right();

//	nodes_.assign(xrange.size(), std::vector<Vector3D<double>>(yrange.size()));
	for (size_t i = 0; i < xrange.size(); ++i) {
		for (size_t j = 0; j < yrange.size(); ++j) {
			const double x = xrange[i];
			const double y = yrange[j];
			const double z = std::max(std::min(function_(x, y), z_max), z_min);
//			nodes_[i][j] = {x, y, z};

			qDebug() << x << y << z;
		}
	}
}

