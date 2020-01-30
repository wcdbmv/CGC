#ifndef RENDER_CASCADE_RENDERER_CASCADE_RENDERER_HPP_
#define RENDER_CASCADE_RENDERER_CASCADE_RENDERER_HPP_

#include <QPixmap>
#include <QVector>
#include "math/matrix/matrix4x4.hpp"
#include "object/mesh/mesh.hpp"

class CascadeRenderer {
public:
	CascadeRenderer() noexcept;
	explicit CascadeRenderer(QPixmap* pixmap) noexcept;
	void setPixmap(QPixmap* pixmap) noexcept;

	void render(const QVector<Mesh>& meshes, const QVector<QColor>& colors, const Matrix4x4<double>& view_matrix);

private:
	void renderMesh(const Mesh& mesh, const Matrix4x4<double>& view_matrix, const QColor& color);

	QPixmap* pixmap_;
};

#endif  // RENDER_CASCADE_RENDERER_CASCADE_RENDERER_HPP_
