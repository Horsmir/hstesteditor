#ifndef HsTestEditor_H
#define HsTestEditor_H

#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include "ui_mainwindow.h"

namespace Ui
{
class MainWindow;
}

class HsTestEditor : public QMainWindow
{
	Q_OBJECT
public:
	explicit HsTestEditor(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~HsTestEditor();

private slots:
	void on_actionExit_triggered();
	void on_actionAbout_triggered();

private:
	Ui::MainWindow *ui;
	QString appName;
};

#endif // HsTestEditor_H
