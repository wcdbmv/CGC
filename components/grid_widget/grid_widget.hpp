#ifndef COMPONENTS_GRID_WIDGET_GRID_WIDGET_HPP_
#define COMPONENTS_GRID_WIDGET_GRID_WIDGET_HPP_

#include <QWidget>

namespace Ui {
class GridWidget;
}

class GridWidget : public QWidget {
	Q_OBJECT

public:
	explicit GridWidget(QWidget *parent = nullptr);
	~GridWidget();

private:
	Ui::GridWidget *ui;
};

#endif  // COMPONENTS_GRID_WIDGET_GRID_WIDGET_HPP_
