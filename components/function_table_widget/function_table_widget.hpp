#ifndef COMPONENTS_FUNCTION_TABLE_WIDGET_FUNCTION_TABLE_WIDGET_HPP_
#define COMPONENTS_FUNCTION_TABLE_WIDGET_FUNCTION_TABLE_WIDGET_HPP_

#include <QTableWidget>
#include <QVector>
#include <QVBoxLayout>
#include "../../exprtk/exprtk.hpp"

class FunctionTableWidget : public QTableWidget {
	Q_OBJECT
public:
	explicit FunctionTableWidget(QWidget* parent = nullptr);

	void append();

private slots:
	void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
	QVector<QString> functions;

	exprtk::symbol_table<double> symbolTable;
	exprtk::expression<double> expression;
	exprtk::parser<double> parser;
	double x, y;

	static const QVector<QColor> DEFAULT_COLORS;
	static const QStringList HEADER_LABELS;
	static const int COLOR_COLUMN;
};

#endif  // COMPONENTS_FUNCTION_TABLE_WIDGET_FUNCTION_LIST_HPP_
