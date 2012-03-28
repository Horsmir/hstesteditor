#include "HsTestEditor.h"

HsTestEditor::HsTestEditor(QWidget *parent, Qt::WindowFlags flags):
	QMainWindow(parent, flags), ui(new Ui::MainWindow), root(0)
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
	
	testManager = new TestManager(this);
	createTestDialog = new DlgCreateTest(this);
	addTaskDialog = new DlgAddTask(this);
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

void HsTestEditor::on_actionNewTest_triggered()
{
	if(createTestDialog->exec() == QDialog::Accepted)
	{
		QString testFilePath = createTestDialog->getTestDir() + "/" + createTestDialog->getTestName() + ".tst";
		testManager->createTest(createTestDialog->getTestName(), createTestDialog->getAuthor(), testFilePath);
		
		showTree();
	}
}

void HsTestEditor::on_actionOpen_triggered()
{
	QFileDialog::Options options;
	options |= QFileDialog::DontUseNativeDialog;
	QString filter;
	
	QString testFilePath = QFileDialog::getOpenFileName(this, trUtf8("Открыть файл с тестом"), "", trUtf8("Файлы с тестами (*tst);;Все файлы (*.*)"), &filter, options);
	if(!testFilePath.isEmpty())
	{
		testManager->openTest(testFilePath);
		showTree();
	}
}

void HsTestEditor::on_actionAddTask_triggered()
{
	TestNode node;
	addTaskDialog->setNode(&node);
	if(addTaskDialog->exec() == QDialog::Accepted)
	{
		testManager->addTestNode(node);
		showTree();
	}
}

void HsTestEditor::showTree()
{
	ui->twStruct->clear();
	root = new QTreeWidgetItem;
	root->setText(0, testManager->getTestName());
	ui->twStruct->addTopLevelItem(root);
	
	int n = testManager->getCount();
	for(int i = 0; i < n; i++)
	{
		QTreeWidgetItem *item = new QTreeWidgetItem;
		item->setText(0, QString("%1").arg(i + 1));
		root->addChild(item);
	}
}

void HsTestEditor::on_actionSave_triggered()
{
	testManager->saveTest();
}

void HsTestEditor::on_twStruct_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
	QString strid = item->text(0);
	addTaskDialog->setNode(testManager->getNodeForChange(strid.toUInt() - 1));
	addTaskDialog->setEdit(true);
	addTaskDialog->exec();
}

#include "HsTestEditor.moc"
