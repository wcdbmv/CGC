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

	symbolTable.add_variable("x", x);
	symbolTable.add_variable("y", y);
	symbolTable.add_constants();

	expression.register_symbol_table(symbolTable);
}

void FunctionTableWidget::append() {
	functions.push_back("");

	const auto row = rowCount();
	insertRow(row);

	for (int i = 0; i != HEADER_LABELS.size(); ++i) {
		setItem(row, i, new QTableWidgetItem());
	}

	auto colorItem = item(row, COLOR_COLUMN);
	colorItem->setFlags(colorItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	colorItem->setBackground(DEFAULT_COLORS[row % DEFAULT_COLORS.size()]);
}

void FunctionTableWidget::on_tableWidget_itemChanged(QTableWidgetItem* item) {
	const auto input = item->text().trimmed();
	const auto row = item->row();

	if (input.isEmpty()) {
		functions[row] = input;
		return;
	}

	if (!parser.compile(input.toStdString(), expression)) {
		QMessageBox::critical(this, "Error",
			"An error was occurred while parsing mathematical expression. "
			"Please, input the valid mathematical expression."
		);
		item->setText(functions[row]);
		return;
	}

	functions[row] = input;
}
