#include "color_label.hpp"

ColorLabel::ColorLabel(QWidget* parent) : QLabel(parent) {}

const QColor& ColorLabel::color() const {
	return this->palette().color(this->backgroundRole());
}

void ColorLabel::setColor(const QColor& color) {
	QPalette palette = this->palette();
	palette.setColor(this->backgroundRole(), color);
	this->setAutoFillBackground(true);
	this->setPalette(palette);
}
