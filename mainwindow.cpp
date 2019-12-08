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
#include <QVector>

void MainWindow::on_plotPushButton_clicked() {
	auto function = ui->functionTableWidget->function(0);
	Grid grid = {
		{-2, 2, 1},
		{-2, 2, 1},
	};
	auto mesh = Surface::build(function, grid);

	qDebug() << "faces";
	for (auto&& f: mesh.faces) {
		const auto v1 = mesh.vertices[f[0]];
		const auto v2 = mesh.vertices[f[1]];
		const auto v3 = mesh.vertices[f[2]];
		qDebug() << '(' << v1.x() <<  v1.y() << v1.z() << ')' << '(' << v2.x() <<  v2.y() << v2.z() << ')' << '(' << v3.x() <<  v3.y() << v3.z() << ')';
	}
}

void MainWindow::on_clearAllPushButton_clicked() {

}

