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

#include "math/surface/surface.hpp"

void MainWindow::on_plotPushButton_clicked() {
	auto function = ui->functionTableWidget->function(0);
	Region region = {
		{-5, 5, 1},
		{-5, 5, 1},
		{-5, 5, 1},
	};
	Surface surface(function, region);
	surface.calc_nodes();
}

void MainWindow::on_clearAllPushButton_clicked() {

}

