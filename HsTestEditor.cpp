#include "HsTestEditor.h"

HsTestEditor::HsTestEditor(QWidget *parent, Qt::WindowFlags flags):
	QMainWindow(parent, flags), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QAction *viewDocStruct = ui->dockWidgetStruct->toggleViewAction();
	QAction *viewDocTask = ui->dockWidgetShowTask->toggleViewAction();
	QAction *viewToolBar = ui->toolBar->toggleViewAction();
	viewToolBar->setText(trUtf8("Панель инструментов"));
	ui->menu_4->addAction(viewDocStruct);
	ui->menu_4->addAction(viewDocTask);
	ui->menu_4->addAction(viewToolBar);
	
	appName = windowTitle();
}

HsTestEditor::~HsTestEditor()
{
	delete ui;
}

void HsTestEditor::on_actionExit_triggered()
{
	close();
}

void HsTestEditor::on_actionAbout_triggered()
{
	QString str1, str2, str3, str4;
	
	str1 = trUtf8("<h2>%1</h2><p>Программа <b>%1</b> предназначена для тестирования учеников, студентов и сотрудников учреждений.</p><p>Copyright &copy;  2012 Роман Браун</p><p>Icons: Copyright &copy; <a href=\"http://kde-look.org/usermanager/search.php?username=frag\">frag F-L</a>").arg(appName);
	str2 = trUtf8("<p>Это программа является свободным программным обеспечением. Вы можете распространять и/или модифицировать её согласно условиям Стандартной Общественной Лицензии GNU, опубликованной Фондом Свободного Программного Обеспечения, версии 3 или, по Вашему желанию, любой более поздней версии.</p>");
	str3 = trUtf8("<p>Эта программа распространяется в надежде, что она будет полезной, но БЕЗ ВСЯКИХ ГАРАНТИЙ, в том числе подразумеваемых гарантий ТОВАРНОГО СОСТОЯНИЯ ПРИ ПРОДАЖЕ и ГОДНОСТИ ДЛЯ ОПРЕДЕЛЁННОГО ПРИМЕНЕНИЯ. Смотрите Стандартную Общественную Лицензию GNU для получения дополнительной информации.</p>");
	str4 = trUtf8("<p>Вы должны были получить копию Стандартной Общественной Лицензии GNU вместе с программой. В случае её отсутствия, посмотрите <a href=\"http://www.gnu.org/licenses/\">http://www.gnu.org/licenses/</a>.</p><p>E-Mail: <a href=\"mailto:firdragon76@gmail.com\">firdragon76@gmail.com</a><br>Сайт программы: <a href=\"github.com/Horsmir/hstesteditor\">github.com/Horsmir/hstest</a></p>");
	
	QMessageBox::about(this, trUtf8("О программе"), str1 + str2 + str3 + str4);
}

#include "HsTestEditor.moc"
