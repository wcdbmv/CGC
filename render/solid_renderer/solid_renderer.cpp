#include "solid_renderer.hpp"

#include <QPainter>

SolidRenderer::SolidRenderer() noexcept : pixmap_(nullptr) {}

SolidRenderer::SolidRenderer(QPixmap* pixmap) noexcept :
		pixmap_(pixmap),
		buff_(pixmap->height(), QVector<double>(pixmap->width(), std::numeric_limits<int>::max())) {}

void SolidRenderer::setPixmap(QPixmap* pixmap) noexcept {
	pixmap_ = pixmap;
	resizePixmap();
}

void SolidRenderer::resizePixmap() {
	buff_ = QVector<QVector<double>>(pixmap_->height(), QVector<double>(pixmap_->width(), std::numeric_limits<int>::max()));
}

void SolidRenderer::render(const QVector<Mesh>& meshes, const QVector<QColor>& colors, const Matrix4x4<double>& view_matrix) {
	clearBuff();

	for (int i = 0; i < meshes.size(); ++i) {
		renderMesh(meshes[i], view_matrix, colors[i]);
	}
}

void SolidRenderer::clearBuff() {
	if (buff_.size() != pixmap_->height() || (!buff_.empty() && buff_[0].size() != pixmap_->width())) {
		resizePixmap();
		return;
	}

	for (auto&& b: buff_) {
		for (auto&& item: b) {
			item = std::numeric_limits<int>::max();
		}
	}
}

void SolidRenderer::renderMesh(const Mesh& mesh, const Matrix4x4<double>& view_matrix, const QColor& color) {
	for (auto&& face: mesh.faces) {
		if (!std::isfinite(mesh.vertices[face[0]].z())
		 || !std::isfinite(mesh.vertices[face[1]].z())
		 || !std::isfinite(mesh.vertices[face[2]].z())) {
			continue;
		}

		const Triangle triangle(
			view_matrix * mesh.vertices[face[0]],
			view_matrix * mesh.vertices[face[1]],
			view_matrix * mesh.vertices[face[2]]
		);

		renderTriangle(triangle, color);
	}
}

void SolidRenderer::renderTriangle(const Triangle& triangle, const QColor& color) {
//	QPoint leftCorner(
//		static_cast<int>(std::min(triangle.a().x(), std::min(triangle.b().x(), triangle.c().x()))),
//		static_cast<int>(std::min(triangle.a().y(), std::min(triangle.b().y(), triangle.c().y())))
//	);
	//	QPoint rightCorner(
//		static_cast<int>(std::max(triangle.a().x(), std::max(triangle.b().x(), triangle.c().x()))),
//		static_cast<int>(std::max(triangle.a().y(), std::max(triangle.b().y(), triangle.c().y())))
//	);
	QPoint leftCorner(
		std::max(0, std::min(
			std::min(
				static_cast<int>(triangle.a().x()),
				static_cast<int>(triangle.b().x())
			),
			std::min(
				static_cast<int>(triangle.c().x()),
				pixmap_->width() - 1
			)
		)),
		std::max(0, std::min(
			std::min(
				static_cast<int>(triangle.a().y()),
				static_cast<int>(triangle.b().y())
			),
			std::min(
				static_cast<int>(triangle.c().y()),
				pixmap_->width() - 1
			)
		))
	);
	QPoint rightCorner(
		std::min(pixmap_->width() - 1, std::max(
			std::max(
				static_cast<int>(triangle.a().x()),
				static_cast<int>(triangle.b().x())
			),
			std::max(
				static_cast<int>(triangle.c().x()),
				0
			)
		)),
		std::min(pixmap_->height() - 1, std::max(
			std::max(
				static_cast<int>(triangle.a().y()),
				static_cast<int>(triangle.b().y())
			),
			std::max(
				static_cast<int>(triangle.c().y()),
				0
			)
		))
	);
	const double square = (triangle[0].y() - triangle[2].y()) * (triangle[1].x() - triangle[2].x())
	                    + (triangle[1].y() - triangle[2].y()) * (triangle[2].x() - triangle[0].x());

	QPainter painter(pixmap_);
	painter.setPen(color);

	for (int i = leftCorner.x(); i <= rightCorner.x(); ++i) {
		for (int j = leftCorner.y(); j <= rightCorner.y(); ++j) {
			const auto barCoords = triangle.barycentric(QPoint(i, j), square);
			if (barCoords.x() >= -std::numeric_limits<double>::epsilon()
			 && barCoords.y() >= -std::numeric_limits<double>::epsilon()
			 && barCoords.z() >= -std::numeric_limits<double>::epsilon()) {
				const auto z = (barCoords.x() * triangle[0].z() + barCoords.y() * triangle[1].z() + barCoords.z() * triangle[2].z());
				if (z <= buff_[j][i]) {
					buff_[j][i] = z;
					painter.drawPoint(i, j);
				}
			}
		}
	}
}
