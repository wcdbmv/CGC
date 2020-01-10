#include "components/grid_widget/grid_widget.hpp"
#include "ui_grid_widget.h"

GridWidget::GridWidget(QWidget *parent) :
		QWidget(parent),
		ui(new Ui::GridWidget) {
	ui->setupUi(this);
}

GridWidget::~GridWidget() {
	delete ui;
}
