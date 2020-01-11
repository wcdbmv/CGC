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

Grid GridWidget::grid() const {
	return {
		Range(ui->xbDoubleSpinBox->value(), ui->xeDoubleSpinBox->value(), ui->dxDoubleSpinBox->value()),
		Range(ui->ybDoubleSpinBox->value(), ui->yeDoubleSpinBox->value(), ui->dyDoubleSpinBox->value())
	};
}
