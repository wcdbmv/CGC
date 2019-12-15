#include "mainwindow.hpp"
#include "ui_mainwindow.h"

const QColor MainWindow::BG_COLOR = Qt::white;

MainWindow::MainWindow(QWidget* parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow) {
	ui->setupUi(this);

	on_clearAllPushButton_clicked();

	connect(ui->appendPushButton, &QPushButton::clicked, ui->functionTableWidget, &FunctionTableWidget::append);
	connect(ui->removePushButton, &QPushButton::clicked, ui->functionTableWidget, &FunctionTableWidget::remove);
}

MainWindow::~MainWindow() noexcept {
	delete ui;
}

#include <QtDebug>
#include "surface/surface.hpp"
#include "scene/scene.hpp"
#include <QVector>
#include <QPainter>

void MainWindow::on_plotPushButton_clicked() {
	qDebug() << "plot";

	auto function = ui->functionTableWidget->function(0);
	Grid grid = {
		{-5, 5, 1},
		{-5, 5, 1},
	};

	auto mesh = Surface::build(function, grid);
	Camera camera;
	camera.RotateUpDownSphere(up / 8);
	camera.RotateLeftRightSphere(right / 8);
	const auto view_matrix = camera.get_view_matrix();

	clearImage();

	const auto h = ui->drawLabel->height() / 2;
	const auto w = ui->drawLabel->width() / 2;
	int f = 50;

	for (auto&& edge: mesh.edges) {
		auto p1 = view_matrix * mesh.vertices[edge.p1()];
		auto p2 = view_matrix * mesh.vertices[edge.p2()];

		QPainter painter(&pixmap);
		painter.drawLine(
			w + static_cast<int>(f * p1.x()), h - static_cast<int>(f * p1.y()),
			w + static_cast<int>(f * p2.x()), h - static_cast<int>(f * p2.y())
		);
	}

	ui->drawLabel->setPixmap(pixmap);
	plotted = true;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
	if (!mouse || !plotted || event->button() != Qt::LeftButton)
		return;

	const int x = event->x() - ui->drawLabel->x();
	const int y = event->y() - ui->drawLabel->y();

	if (x < 0 || y < 0 || x > 720 || y > 720)
		return;

	drag = {x, y};
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	if (!mouse || !plotted || event->buttons() != Qt::LeftButton)
		return;

	const int x = event->x() - ui->drawLabel->x();
	const int y = event->y() - ui->drawLabel->y();

	if (x < 0 || y < 0 || x > ui->drawLabel->width() || y > ui->drawLabel->height()) {
		return;
	}

	up += drag.y() - y;
	right += drag.x() - x;

	on_plotPushButton_clicked();

	drag = {x, y};
}

void MainWindow::wheelEvent(QWheelEvent *event) {
	if (!zoom || !mouse || !plotted) {
		return;
	}

	const int x = event->x() - ui->drawLabel->x();
	const int y = event->y() - ui->drawLabel->y();

	if (x < 0 || y < 0 || x > ui->drawLabel->width() || y > ui->drawLabel->height()) {
		return;
	}

	zoom += event->delta() / 8;

	on_plotPushButton_clicked();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if (!keyboard || !plotted)
		return;

	receiveKey(event->key(), true);

	static const double delta_phi = 1;
	static const int delta_zoom = 1;

	if (w) up += delta_phi;
	if (a) right += delta_phi;
	if (s) up -= delta_phi;
	if (d) right -= delta_phi;

	if (zoom) {
		if (plus) zoom += delta_zoom;
		if (minus) zoom -= delta_zoom;
	}

	on_plotPushButton_clicked();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
	if (!keyboard) {
		return;
	}

	receiveKey(event->key(), false);
}

void MainWindow::clearImage() {
	image = QImage(ui->drawLabel->size(), QImage::Format_RGB32);
	image.fill(Qt::white);
	pixmap = QPixmap::fromImage(image);
}

void MainWindow::on_clearAllPushButton_clicked() {
	plotted = false;

	clearImage();

	factor = 50;

	w = a = s = d = plus = minus = false;
}

void MainWindow::receiveKey(int key, bool value) {
	switch (key) {
		case Qt::Key_W:
//	case Qt::Key_Up:
			w = value;
			break;
		case Qt::Key_A:
//	case Qt::Key_Left:
			a = value;
			break;
		case Qt::Key_S:
//	case Qt::Key_Down:
			s = value;
			break;
		case Qt::Key_D:
//	case Qt::Key_Right:
			d = value;
			break;
		case Qt::Key_Plus:
			plus = value;
			break;
		case Qt::Key_Minus:
			minus = value;
			[[fallthrough]];
		default:
			break;
	}
}
