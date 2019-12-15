#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QMainWindow>
#include <QMouseEvent>
#include <QImage>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() noexcept override;

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;

private slots:
	void on_plotPushButton_clicked();
	void on_clearAllPushButton_clicked();

private:
	void clearImage();
	void displayImage();

private:
	Ui::MainWindow* ui;

	QImage image;
	QPixmap pixmap;
	bool plotted;

	bool zoom = true;

	int factor;
	bool keyboard = true;
	bool w, a, s, d, plus, minus;
	void receiveKey(int key, bool value);

	bool mouse = true;
	QPoint drag;
	double up = 0;
	double right = 0;

	static const QColor BG_COLOR;
};

#endif  // MAINWINDOW_HPP_
