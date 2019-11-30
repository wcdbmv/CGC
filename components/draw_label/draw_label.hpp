#ifndef COMPONENTS_DRAW_LABEL_DRAW_LABEL_HPP_
#define COMPONENTS_DRAW_LABEL_DRAW_LABEL_HPP_

#include <QLabel>

class DrawLabel : public QLabel {
	Q_OBJECT
public:
	explicit DrawLabel(QWidget* parent);
};

#endif  // COMPONENTS_DRAW_LABEL_DRAW_LABEL_HPP_
