#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QThread>

const QColor MainWindow::BG_COLOR = Qt::white;
const int MainWindow::DEFAULT_ZOOM = 50;

MainWindow::MainWindow(QWidget* parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow) {
	ui->setupUi(this);

	connect(ui->appendPushButton, &QPushButton::clicked, ui->functionTableWidget, &FunctionTableWidget::append);
	connect(ui->removePushButton, &QPushButton::clicked, ui->functionTableWidget, &FunctionTableWidget::remove);
	connect(ui->changeColorPushButton, &QPushButton::clicked, ui->functionTableWidget, &FunctionTableWidget::changeColor);
	connect(ui->clearAllPushButton, &QPushButton::clicked, ui->functionTableWidget, &FunctionTableWidget::truncate);
	connect(ui->clearAllPushButton, &QPushButton::clicked, ui->gridWidget, &GridWidget::clear);

	QThread::create([&] {
		QTimer::singleShot(100, this, &MainWindow::on_clearAllPushButton_clicked);
		ui->functionTableWidget->setColumnWidth(0, 271);
		ui->functionTableWidget->setColumnWidth(1, 57);
	})->start();

	cascade_renderer.setPixmap(&pixmap);
	solid_renderer.setPixmap(&pixmap);
}

MainWindow::~MainWindow() noexcept {
	delete ui;
}

#include <QMessageBox>
#include <QtDebug>
#include "surface/surface.hpp"
#include "scene/scene.hpp"
#include <QVector>
#include <QPainter>
#include <QComboBox>

void MainWindow::on_plotPushButton_clicked() {
	plotted_meshes.clear();
	plotted_colors.clear();
	plot();
}

void MainWindow::on_clearAllPushButton_clicked() {
	clearAll();
}

void MainWindow::plot() {
	try {
		grid = ui->gridWidget->grid();
	} catch (...) {
		QMessageBox::critical(this, "Error", "Wrong range");
		return;
	}

	Camera camera;
	camera.RotateUpDownSphere(phi_y);
	camera.RotateLeftRightSphere(phi_x);
	const auto view_matrix = camera.get_view_matrix(factor, pixmap.height() / 2.0, pixmap.width() / 2.0);

	clearImage();

	if (!plotted()) {
		QModelIndexList selected = ui->functionTableWidget->selectionModel()->selectedRows();
		for (auto&& select : selected) {
			const auto row = select.row();
			auto function = ui->functionTableWidget->function(row);
			plotted_meshes.append(Surface::build(function, grid));
			plotted_colors.append(ui->functionTableWidget->color(row));
		}
	}

	switch (ui->comboBox->currentIndex()) {
	case 0:
		solid_renderer.render(plotted_meshes, plotted_colors, view_matrix);
		break;
	case 1:
		cascade_renderer.render(plotted_meshes, plotted_colors, view_matrix);
		break;
	default:
		break;
	}

	displayImage();
}

bool MainWindow::plotted() const {
	return !plotted_meshes.empty();
}

void MainWindow::clearImage() {
	image = QImage(ui->drawLabel->size(), QImage::Format_RGB32);
	image.fill(Qt::white);
	pixmap = QPixmap::fromImage(image);
}

void MainWindow::displayImage() {
	ui->drawLabel->setPixmap(pixmap);
}

void MainWindow::clearAll() {
	plotted_meshes.clear();
	plotted_colors.clear();

	clearImage();
	displayImage();

	factor = DEFAULT_ZOOM;

	keyW = keyA = keyS = keyD = keyPlus = keyMinus = false;

	phi_x = phi_y = 0;
}

void MainWindow::addZoom(int delta) {
	factor += delta;

	checkZoom();
}

void MainWindow::checkZoom() {
	if (constexpr int max_factor = 100; factor > max_factor) {
		factor = max_factor;
	} else if (constexpr int min_factor = 1; factor < min_factor) {
		factor = min_factor;
	}
}

bool MainWindow::checkMouse(QMouseEvent* event) const {
	return mouse && plotted() && event->buttons() == Qt::LeftButton;
}

bool MainWindow::checkWheel() const {
	return zoom && mouse && plotted();
}

template <typename Event>
bool MainWindow::checkMouseOnDrawLabel(Event* event) const {
	const int x = event->x() - ui->drawLabel->x();
	const int y = event->y() - ui->drawLabel->y();

	return 0 <= x && x <= ui->drawLabel->width() && 0 <= y && y <= ui->drawLabel->height();
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
	if (!checkMouse(event) || !checkMouseOnDrawLabel(event)) {
		return;
	}

	drag = {event->x(), event->y()};
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
	if (!checkMouse(event) || !checkMouseOnDrawLabel(event)) {
		return;
	}

	phi_y += (drag.x() - event->x()) / rotateDecelerationFactor;
	phi_x += (drag.y() - event->y()) / rotateDecelerationFactor;

	plot();

	drag = {event->x(), event->y()};
}

void MainWindow::wheelEvent(QWheelEvent* event) {
	if (!checkWheel() && checkMouseOnDrawLabel(event)) {
		return;
	}

	addZoom(event->delta() / 64);

	plot();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
	if (!keyboard || !plotted()) {
		return;
	}

	receiveKey(event->key(), true);

	constexpr double delta_phi = 1;
	constexpr int delta_zoom = 1;

	if (keyW) phi_x += delta_phi;
	if (keyA) phi_y += delta_phi;
	if (keyS) phi_x -= delta_phi;
	if (keyD) phi_y -= delta_phi;

	if (zoom) {
		if (keyPlus) addZoom(delta_zoom);
		if (keyMinus) addZoom(-delta_zoom);
	}

	plot();
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
	if (!keyboard) {
		return;
	}

	receiveKey(event->key(), false);
}

void MainWindow::receiveKey(int key, bool value) {
	switch (key) {
	case Qt::Key_W:
//	case Qt::Key_Up:
		keyW = value;
		break;
	case Qt::Key_A:
//	case Qt::Key_Left:
		keyA = value;
		break;
	case Qt::Key_S:
//	case Qt::Key_Down:
		keyS = value;
		break;
	case Qt::Key_D:
//	case Qt::Key_Right:
		keyD = value;
		break;
	case Qt::Key_Plus:
		keyPlus = value;
		break;
	case Qt::Key_Minus:
		keyMinus = value;
		[[fallthrough]];
	default:
		break;
	}
}

void MainWindow::resizeEvent(QResizeEvent*) {
	solid_renderer.resizePixmap();
	plot();
}
