#include "HsTestEditor.h"

HsTestEditor::HsTestEditor(QWidget *parent, Qt::WindowFlags flags):
	QMainWindow(parent, flags), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	QAction *viewDocStruct = ui->dockWidgetStruct->toggleViewAction();
	QAction *viewDocTask = ui->dockWidgetShowTask->toggleViewAction();
	ui->menu_4->addAction(viewDocStruct);
	ui->menu_4->addAction(viewDocTask);
}

HsTestEditor::~HsTestEditor()
{
	delete ui;
}

void HsTestEditor::on_actionExit_triggered()
{
	close();
}


#include "HsTestEditor.moc"
