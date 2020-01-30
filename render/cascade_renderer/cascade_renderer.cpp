#include "cascade_renderer.hpp"

#include <QPainter>

CascadeRenderer::CascadeRenderer() noexcept : pixmap_(nullptr) {}
CascadeRenderer::CascadeRenderer(QPixmap* pixmap) noexcept : pixmap_(pixmap) {}

void CascadeRenderer::setPixmap(QPixmap* pixmap) noexcept {
	pixmap_ = pixmap;
}

void CascadeRenderer::render(const QVector<Mesh>& meshes, const QVector<QColor>& colors, const Matrix4x4<double>& view_matrix) {
	for (int i = 0; i < meshes.size(); ++i) {
		renderMesh(meshes[i], view_matrix, colors[i]);
	}
}

void CascadeRenderer::renderMesh(const Mesh& mesh, const Matrix4x4<double>& view_matrix, const QColor& color) {
	QPainter painter(pixmap_);
	painter.setPen(color);

	for (auto&& edge: mesh.edges) {
		if (!std::isfinite(mesh.vertices[edge.p1()].z()) || !std::isfinite(mesh.vertices[edge.p2()].z())) {
			continue;
		}

		auto p1 = view_matrix * mesh.vertices[edge.p1()];
		auto p2 = view_matrix * mesh.vertices[edge.p2()];

		painter.drawLine(
			static_cast<int>(p1.x()), static_cast<int>(p1.y()),
			static_cast<int>(p2.x()), static_cast<int>(p2.y())
		);
	}
}
