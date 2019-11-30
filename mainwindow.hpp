#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QMainWindow>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() noexcept override;

private slots:
	void on_clearAllPushButton_clicked();

private:
	void clearImage();
	void displayImage();

private:
	Ui::MainWindow* ui;

	QPixmap pixmap;
	static const QColor BG_COLOR;
};

#endif  // MAINWINDOW_HPP_
