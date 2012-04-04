#ifndef HsTestEditor_H
#define HsTestEditor_H

#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QtGui/QPrinter>
#include "ui_mainwindow.h"
#include "testmanager.h"
#include "dlgcreatetest.h"
#include "dlgaddtask.h"
#include "htmltemplate.h"
#include "dlgfind.h"

namespace Ui
{
class MainWindow;
}

class HsTestEditor : public QMainWindow
{
	Q_OBJECT
public:
	explicit HsTestEditor(const QString & testFilePath = "", QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~HsTestEditor();

private slots:
	void on_actionExit_triggered();
	void on_actionAbout_triggered();
	void on_actionNewTest_triggered();
	void on_actionOpen_triggered();
	void on_actionAddTask_triggered();
	void on_actionSave_triggered();
	void on_twStruct_itemDoubleClicked(QTreeWidgetItem * item, int column);
	void on_twStruct_itemClicked(QTreeWidgetItem * item, int column);
	void on_actionToPDF_triggered();
	void on_actionToText_triggered();
	void on_actionFind_triggered();
	
	void findTextNext(const QString &str, Qt::CaseSensitivity cs);
	void findTextPrev(const QString &str, Qt::CaseSensitivity cs);

private:
	Ui::MainWindow *ui;
	QString appName;
	QString testFilePath;
	QTreeWidgetItem *root;
	TestManager *testManager;
	DlgCreateTest *createTestDialog;
	DlgAddTask *addTaskDialog;
	DlgFind *findDialog;
	HtmlTemplate *htmlTemplate;
	
	void showTree();
	void showTest();
};

#endif // HsTestEditor_H
