#ifndef RENDER_SOLID_RENDERER_SOLID_RENDERER_HPP_
#define RENDER_SOLID_RENDERER_SOLID_RENDERER_HPP_

#include <QPixmap>
#include <QVector>
#include "math/matrix/matrix4x4.hpp"
#include "object/mesh/mesh.hpp"
#include "object/triangle/triangle.hpp"

class SolidRenderer {
public:
	SolidRenderer() noexcept;
	explicit SolidRenderer(QPixmap* pixmap) noexcept;
	void setPixmap(QPixmap* pixmap) noexcept;

	void render(const QVector<Mesh>& meshes, const QVector<QColor>& colors, const Matrix4x4<double>& view_matrix);

public slots:
	void resizePixmap();

private:
	void clearBuff();
	void renderMesh(const Mesh& mesh, const Matrix4x4<double>& view_matrix, const QColor& color);
	void renderTriangle(const Triangle& triangle, const QColor& color);

	QPixmap* pixmap_;
	QVector<QVector<double>> buff_;
};

#endif  // RENDER_SOLID_RENDERER_SOLID_RENDERER_HPP_
