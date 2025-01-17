#ifndef COMPONENTS_FUNCTION_TABLE_WIDGET_FUNCTION_TABLE_WIDGET_HPP_
#define COMPONENTS_FUNCTION_TABLE_WIDGET_FUNCTION_TABLE_WIDGET_HPP_

#include <QTableWidget>
#include <QVector>
#include <QVBoxLayout>
#include "function/function/function.hpp"

class FunctionTableWidget : public QTableWidget {
	Q_OBJECT
public:
	explicit FunctionTableWidget(QWidget* parent = nullptr);

	Function& function(int row);
	QColor color(int row) const;

public slots:
	void append();
	void remove();
	void truncate();
	void changeColor();

private slots:
	void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
	QVector<QString> functions_strings;
	QVector<Function> functions;

	static const QVector<QColor> DEFAULT_COLORS;
	static const QStringList HEADER_LABELS;
	static const int COLOR_COLUMN;
};

#endif  // COMPONENTS_FUNCTION_TABLE_WIDGET_FUNCTION_LIST_HPP_
