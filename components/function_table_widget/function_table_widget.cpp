#include "function_table_widget.hpp"

#include <QMessageBox>

const QVector<QColor> FunctionTableWidget::DEFAULT_COLORS = {Qt::blue, Qt::green, Qt::red};
const QStringList FunctionTableWidget::HEADER_LABELS = {"z(x, y)", "color"};
const int FunctionTableWidget::COLOR_COLUMN = FunctionTableWidget::HEADER_LABELS.indexOf(QRegExp("^color$"));

FunctionTableWidget::FunctionTableWidget(QWidget *parent) : QTableWidget(parent) {
	setColumnCount(HEADER_LABELS.size());
	setHorizontalHeaderLabels(HEADER_LABELS);

	append();

	connect(this, &FunctionTableWidget::itemChanged, this, &FunctionTableWidget::on_tableWidget_itemChanged);
}

Function& FunctionTableWidget::function(int row) {
	return functions[row];
}

void FunctionTableWidget::append() {
	functions.push_back(Function());
	functions_strings.push_back("");

	const auto row = rowCount();
	insertRow(row);

	for (int i = 0; i != HEADER_LABELS.size(); ++i) {
		setItem(row, i, new QTableWidgetItem());
	}

	auto colorItem = item(row, COLOR_COLUMN);
	colorItem->setFlags(colorItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	colorItem->setBackground(DEFAULT_COLORS[row % DEFAULT_COLORS.size()]);
}

void FunctionTableWidget::remove() {
	QModelIndexList selected = selectionModel()->selectedRows();
	for (auto select = selected.rbegin(); select != selected.rend(); ++select) {
		const int row = select->row();
		removeRow(row);
		functions.remove(row);
		functions_strings.remove(row);
	}
}

void FunctionTableWidget::truncate() {
	setRowCount(0);
	functions.clear();
	functions_strings.clear();

	append();
}

void FunctionTableWidget::on_tableWidget_itemChanged(QTableWidgetItem* item) {
	const auto input = item->text().trimmed();
	const auto row = item->row();

	if (input.isEmpty()) {
		functions[row] = Function();
		functions_strings[row] = "";
		return;
	}

	if (!functions[row].set_expression(input.toStdString())) {
		QMessageBox::critical(this, "Error",
			"An error was occurred while parsing mathematical expression. "
			"Please, input the valid mathematical expression."
		);
		item->setText(functions_strings[row]);
		return;
	}

	functions_strings[row] = input;
}
