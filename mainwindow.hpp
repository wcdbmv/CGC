#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QMainWindow>
#include <QMouseEvent>
#include <QImage>
#include <QPixmap>
#include "math/grid/grid.hpp"
#include "math/matrix/matrix4x4.hpp"
#include "object/mesh/mesh.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() noexcept override;

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private slots:
	void on_plotPushButton_clicked();
	void on_clearAllPushButton_clicked();

private:
	Ui::MainWindow* ui;

	QImage image;
	QPixmap pixmap;
	bool plotted;
	void clearImage();
	void displayImage();

	Grid grid;
	void plot();
	void plotMesh(const Mesh& mesh, const Matrix4x4<double>& view_matrix, const QColor& color);
	void clearAll();

	const bool zoom = true;
	int factor;
	void addZoom(int delta);
	void checkZoom();

	bool antialiasing = true;

	const bool keyboard = true;
	bool keyW, keyA, keyS, keyD, keyPlus, keyMinus;
	void receiveKey(int key, bool value);

	const bool mouse = true;
	QPoint drag;
	double phi_x;
	double phi_y;
	double rotateDecelerationFactor = 64;
	[[nodiscard]] bool checkMouse(QMouseEvent* event) const;
	[[nodiscard]] bool checkWheel() const;
	template <typename Event>
	[[nodiscard]] bool checkMouseOnDrawLabel(Event* event) const;

private:
	static const QColor BG_COLOR;
	static const int DEFAULT_ZOOM;
};

#endif  // MAINWINDOW_HPP_
