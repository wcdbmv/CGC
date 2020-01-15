#ifndef RENDER_CASCADE_RENDERER_CASCADE_RENDERER_HPP_
#define RENDER_CASCADE_RENDERER_CASCADE_RENDERER_HPP_

#include <QPixmap>
#include <QVector>
#include "math/matrix/matrix4x4.hpp"
#include "object/mesh/mesh.hpp"

class CascadeRenderer {
public:
	static void render(QPixmap& pixmap, const QVector<Mesh>& meshes, const QVector<QColor>& colors, const Matrix4x4<double>& view_matrix);

private:
	static void renderMesh(QPixmap& pixmap, const Mesh& mesh, const Matrix4x4<double>& view_matrix, const QColor& color);
};



#endif  // RENDER_CASCADE_RENDERER_CASCADE_RENDERER_HPP_
