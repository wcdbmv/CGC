#ifndef COMPONENTS_COLOR_LABEL_COLOR_LABEL_HPP_
#define COMPONENTS_COLOR_LABEL_COLOR_LABEL_HPP_

#include <QLabel>

class ColorLabel : public QLabel {
	Q_OBJECT
public:
	explicit ColorLabel(QWidget* parent = nullptr);

	[[nodiscard]] const QColor& color() const;
	void setColor(const QColor& color);
};

#endif  // COMPONENTS_COLOR_LABEL_COLOR_LABEL_HPP_
