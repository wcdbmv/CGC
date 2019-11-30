#include "mainwindow.hpp"
#include "ui_mainwindow.h"

const QColor MainWindow::BG_COLOR = Qt::white;

MainWindow::MainWindow(QWidget* parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow) {
	ui->setupUi(this);

	on_clearAllPushButton_clicked();
}

MainWindow::~MainWindow() noexcept {
	delete ui;
}

void MainWindow::on_clearAllPushButton_clicked() {
	//
}


