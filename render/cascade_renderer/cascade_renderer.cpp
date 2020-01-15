#include "cascade_renderer.hpp"

#include <QPainter>

void CascadeRenderer::render(QPixmap& pixmap, const QVector<Mesh>& meshes, const QVector<QColor>& colors, const Matrix4x4<double>& view_matrix) {
	for (int i = 0; i < meshes.size(); ++i) {
		renderMesh(pixmap, meshes[i], view_matrix, colors[i]);
	}
}

void CascadeRenderer::renderMesh(QPixmap& pixmap, const Mesh& mesh, const Matrix4x4<double>& view_matrix, const QColor& color) {
	const auto h = pixmap.height() / 2;
	const auto w = pixmap.width() / 2;

	QPainter painter(&pixmap);
	painter.setPen(color);

	for (auto&& edge: mesh.edges) {
		if (!std::isfinite(mesh.vertices[edge.p1()].z()) || !std::isfinite(mesh.vertices[edge.p2()].z())) {
			continue;
		}

		auto p1 = view_matrix * mesh.vertices[edge.p1()];
		auto p2 = view_matrix * mesh.vertices[edge.p2()];

		painter.drawLine(
			w + static_cast<int>(p1.x()), h - static_cast<int>(p1.y()),
			w + static_cast<int>(p2.x()), h - static_cast<int>(p2.y())
		);
	}
}
