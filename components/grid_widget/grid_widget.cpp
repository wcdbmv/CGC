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

void GridWidget::clear() {
	ui->xbDoubleSpinBox->setValue(-5);
	ui->xeDoubleSpinBox->setValue(5);
	ui->dxDoubleSpinBox->setValue(1);
	ui->ybDoubleSpinBox->setValue(-5);
	ui->yeDoubleSpinBox->setValue(5);
	ui->dyDoubleSpinBox->setValue(1);
}
