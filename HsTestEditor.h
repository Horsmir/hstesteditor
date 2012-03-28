#ifndef HsTestEditor_H
#define HsTestEditor_H

#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include "ui_mainwindow.h"
#include "testmanager.h"
#include "dlgcreatetest.h"
#include "dlgaddtask.h"

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
	void on_actionNewTest_triggered();
	void on_actionOpen_triggered();
	void on_actionAddTask_triggered();
	void on_actionSave_triggered();
	void on_twStruct_itemDoubleClicked(QTreeWidgetItem * item, int column);

private:
	Ui::MainWindow *ui;
	QString appName;
	QTreeWidgetItem *root;
	TestManager *testManager;
	DlgCreateTest *createTestDialog;
	DlgAddTask *addTaskDialog;
	
	void showTree();
};

#endif // HsTestEditor_H
