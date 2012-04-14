#include "HsTestEditor.h"

HsTestEditor::HsTestEditor(const QString &testFilePath, QWidget *parent, Qt::WindowFlags flags):
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
	findDialog = new DlgFind(this);
	settingDialog = new DlgSetting(this);
	
	htmlTemplate = new HtmlTemplate(this);
	
	this->testFilePath = testFilePath;
	if(!this->testFilePath.isEmpty())
	{
		testManager->openTest(this->testFilePath);
		showTree();
		showTest();
	}
	
	ui->actionHelp->setDisabled(true);
	
	settings = new QSettings(QSettings::NativeFormat, QSettings::UserScope, "HsTest", "hstesteditor");
	readSettings();
	
	ui->twStruct->setContextMenuPolicy(Qt::CustomContextMenu);
	
	connect(findDialog, SIGNAL(findNext(QString,Qt::CaseSensitivity)), SLOT(findTextNext(QString,Qt::CaseSensitivity)));
	connect(findDialog, SIGNAL(findPrev(QString,Qt::CaseSensitivity)), SLOT(findTextPrev(QString,Qt::CaseSensitivity)));
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
	
	str1 = trUtf8("<h2>%1 0.2</h2><p><b>%1</b> предназначен для создания, редактирования, просмотра тестов.</p><p>Copyright &copy;  2012 Роман Браун</p><p>Icons: Copyright &copy; <a href=\"http://kde-look.org/usermanager/search.php?username=frag\">frag F-L</a>").arg(appName);
	str2 = trUtf8("<p>Это программа является свободным программным обеспечением. Вы можете распространять и/или модифицировать её согласно условиям Стандартной Общественной Лицензии GNU, опубликованной Фондом Свободного Программного Обеспечения, версии 3 или, по Вашему желанию, любой более поздней версии.</p>");
	str3 = trUtf8("<p>Эта программа распространяется в надежде, что она будет полезной, но БЕЗ ВСЯКИХ ГАРАНТИЙ, в том числе подразумеваемых гарантий ТОВАРНОГО СОСТОЯНИЯ ПРИ ПРОДАЖЕ и ГОДНОСТИ ДЛЯ ОПРЕДЕЛЁННОГО ПРИМЕНЕНИЯ. Смотрите Стандартную Общественную Лицензию GNU для получения дополнительной информации.</p>");
	str4 = trUtf8("<p>Вы должны были получить копию Стандартной Общественной Лицензии GNU вместе с программой. В случае её отсутствия, посмотрите <a href=\"http://www.gnu.org/licenses/\">http://www.gnu.org/licenses/</a>.</p><p>E-Mail: <a href=\"mailto:firdragon76@gmail.com\">firdragon76@gmail.com</a><br>Сайт программы: <a href=\"github.com/Horsmir/hstesteditor\">github.com/Horsmir/hstesteditor</a></p>");
	
	QMessageBox::about(this, trUtf8("О программе"), str1 + str2 + str3 + str4);
}

void HsTestEditor::on_actionNewTest_triggered()
{
	createTestDialog->setAuthor(defaultAuthor);
	createTestDialog->setDir(defaultProjectDirPath);
	if(createTestDialog->exec() == QDialog::Accepted)
	{
		QString testFilePath = createTestDialog->getTestDir() + "/" + createTestDialog->getTestName() + ".tst";
		testManager->createTest(createTestDialog->getTestName(), createTestDialog->getAuthor(), testFilePath);
		
		showTree();
		showTest();
	}
}

void HsTestEditor::on_actionOpen_triggered()
{
	QFileDialog::Options options;
	options |= QFileDialog::DontUseNativeDialog;
	QString filter;
	
	testFilePath = QFileDialog::getOpenFileName(this, trUtf8("Открыть файл с тестом"), "", trUtf8("Файлы с тестами (*tst);;Все файлы (*.*)"), &filter, options);
	if(!testFilePath.isEmpty())
	{
		testManager->openTest(testFilePath);
		showTree();
		showTest();
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
		showTest();
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
	
	ui->actionAddTask->setEnabled(true);
	ui->actionFind->setEnabled(true);
	ui->actionSave->setEnabled(true);
	ui->actionToPDF->setEnabled(true);
	ui->actionToText->setEnabled(true);
	ui->actionSaveAs->setEnabled(true);
	//ui->actionToXML->setEnabled(true);
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
	if(addTaskDialog->exec() == QDialog::Accepted)
		showTest();
}

void HsTestEditor::on_twStruct_itemClicked(QTreeWidgetItem *item, int column)
{
	const TestNode *node = testManager->getNodeById(item->text(0).toUInt() - 1);
	QString content = "", tmp = "", tmp_quest = "";
	int ransw = 0;
	
	switch(node->getType())
	{
		case TYPE_NODE_CLOSE:
			for(int i = 0; i < node->getAnswers().count(); i++)
			{
				ransw = int(node->getRealsInt()) & int(qPow(2, i));
				if(ransw == 0)
				{
					tmp += htmlTemplate->getTemplate("closeTestAnswOff").arg(node->getAnswers().at(i));
				}
				else
				{
					tmp += htmlTemplate->getTemplate("closeTestAnswOn").arg(node->getAnswers().at(i));
				}
			}
			content += htmlTemplate->getTemplate("closeTest").arg(item->text(0).toUInt()).arg(node->getTask()).arg(node->getQuestion()).arg(tmp);
			break;
		case TYPE_NODE_OPEN:
			content += htmlTemplate->getTemplate("openTest").arg(item->text(0).toUInt()).arg(node->getTask()).arg(node->getQuestion()).arg(node->getAnswers().at(0));
			break;
		case TYPE_NODE_CONFORMITY:
			for(int i = 0; i < node->getAnswers().count(); i++)
			{
				if(i >= node->getQuestions().count())
					tmp_quest = "";
				else
					tmp_quest = node->getQuestions().at(i);
		
				int p = QString(node->getReals().at(i)).toInt() - 1;
				if(p == -1)
					p = node->getAnswers().count() - 1;
		
				tmp += htmlTemplate->getTemplate("conformityTestAnsw").arg(tmp_quest).arg(node->getAnswers().at(p));
			}
			content += htmlTemplate->getTemplate("conformityTest").arg(item->text(0).toUInt()).arg(node->getTask()).arg(tmp);
			break;
		case TYPE_NODE_REGULATING:
			for(int i = 0; i < node->getAnswers().count(); i++)
			{
				int p = QString(node->getReals().at(i)).toInt() - 1;
				tmp += htmlTemplate->getTemplate("regulatingTestsAnsw").arg(node->getAnswers().at(p));
			}
			content += htmlTemplate->getTemplate("regulatingTests").arg(item->text(0).toUInt()).arg(node->getTask()).arg(tmp);
			break;
	}
	ui->teTask->clear();
	ui->teTask->setHtml(content);
}

void HsTestEditor::showTest()
{
	QString content = htmlTemplate->getTemplate("head").arg(testManager->getTestName()).arg(testManager->getTestAuthor()).arg(testManager->getTestCreateDate());
	QString tmp_quest, tmp;
	
	for(int i = 0; i < testManager->getCount(); i++)
	{
		tmp = tmp_quest = "";
		const TestNode *node = testManager->getNodeById(i);
		switch(node->getType())
		{
			case TYPE_NODE_CLOSE:
				for(int j = 0; j < node->getAnswers().count(); j++)
				{
					int ransw = int(node->getRealsInt()) & int(qPow(2, j));
					if(ransw == 0)
					{
						tmp += htmlTemplate->getTemplate("closeTestAnswOff").arg(node->getAnswers().at(j));
					}
					else
					{
						tmp += htmlTemplate->getTemplate("closeTestAnswOn").arg(node->getAnswers().at(j));
					}
				}
				content += htmlTemplate->getTemplate("closeTest").arg(i + 1).arg(node->getTask()).arg(node->getQuestion()).arg(tmp);
				break;
			case TYPE_NODE_OPEN:
				content += htmlTemplate->getTemplate("openTest").arg(i + 1).arg(node->getTask()).arg(node->getQuestion()).arg(node->getAnswers().at(0));
				break;
			case TYPE_NODE_CONFORMITY:
				for(int j = 0; j < node->getAnswers().count(); j++)
				{
					if(j >= node->getQuestions().count())
						tmp_quest = "";
					else
						tmp_quest = node->getQuestions().at(j);
		
					int p = QString(node->getReals().at(j)).toInt() - 1;
					if(p == -1)
						p = node->getAnswers().count() - 1;
		
					tmp += htmlTemplate->getTemplate("conformityTestAnsw").arg(tmp_quest).arg(node->getAnswers().at(p));
				}
				content += htmlTemplate->getTemplate("conformityTest").arg(i + 1).arg(node->getTask()).arg(tmp);
				break;
			case TYPE_NODE_REGULATING:
				for(int j = 0; j < node->getAnswers().count(); j++)
				{
					int p = QString(node->getReals().at(j)).toInt() - 1;
					tmp += htmlTemplate->getTemplate("regulatingTestsAnsw").arg(node->getAnswers().at(p));
				}
				content += htmlTemplate->getTemplate("regulatingTests").arg(i + 1).arg(node->getTask()).arg(tmp);
				break;
		}
	}
	content += htmlTemplate->getTemplate("end");
	ui->teTest->clear();
	ui->teTest->setHtml(content);	
}

void HsTestEditor::on_actionToPDF_triggered()
{
	QFileDialog::Options options;
	options |= QFileDialog::DontUseNativeDialog;
	QString filter;
	
	QString pdfFilePath = QFileDialog::getSaveFileName(this, trUtf8("Экспорт в PDF"), QDir::homePath(), trUtf8("Файлы PDF (*pdf);;Все файлы (*.*)"), &filter, options);
	if(!pdfFilePath.isEmpty())
	{
		QPrinter printer;
		printer.setOutputFormat(QPrinter::PdfFormat);
		printer.setOutputFileName(pdfFilePath);
	
		ui->teTest->print(&printer);
	}
}

void HsTestEditor::on_actionToText_triggered()
{
	QFileDialog::Options options;
	options |= QFileDialog::DontUseNativeDialog;
	QString filter;
	
	QString textFilePath = QFileDialog::getSaveFileName(this, trUtf8("Экспорт в текст"), QDir::homePath(), trUtf8("Текстовые файлы (*txt);;Все файлы (*.*)"), &filter, options);
	if(!textFilePath.isEmpty())
	{
		testManager->testToText(textFilePath);
	}
}

void HsTestEditor::on_actionFind_triggered()
{
	findDialog->show();
}

void HsTestEditor::findTextNext(const QString &str, Qt::CaseSensitivity cs)
{
	QTextDocument::FindFlags options;
	if(cs == Qt::CaseSensitive)
		options |= QTextDocument::FindCaseSensitively;
	ui->teTest->find(str, options);
}

void HsTestEditor::findTextPrev(const QString &str, Qt::CaseSensitivity cs)
{
	QTextDocument::FindFlags options;
	options |= QTextDocument::FindBackward;
	if(cs == Qt::CaseSensitive)
		options |= QTextDocument::FindCaseSensitively;
	ui->teTest->find(str, options);
}

void HsTestEditor::on_actionSaveAs_triggered()
{
	QFileDialog::Options options;
	options |= QFileDialog::DontUseNativeDialog;
	QString filter;
	
	QString textFilePath = QFileDialog::getSaveFileName(this, trUtf8("Сохранить тест как..."), QDir::homePath(), trUtf8("Тестовые файлы (*tst);;Все файлы (*.*)"), &filter, options);
	if(!textFilePath.isEmpty())
	{
		testManager->saveTest(textFilePath);
	}
}

void HsTestEditor::readSettings()
{
	defaultAuthor = settings->value("General/Author", QString("")).toString();
	defaultProjectDirPath = settings->value("General/ProjectDirPath", QString(QDir::homePath())).toString();
	ui->dockWidgetStruct->setVisible(settings->value("View/ShowStruct", bool(true)).toBool());
	ui->dockWidgetShowTask->setVisible(settings->value("View/ShowTask", bool(true)).toBool());
	ui->toolBar->setVisible(settings->value("View/ShowToolBar", bool(true)).toBool());
	appStyle = settings->value("View/Style" , QString("default")).toString();
	qApp->setStyle(appStyle);
}

void HsTestEditor::writeSettings()
{
	settings->setValue("General/Author", defaultAuthor);
	settings->setValue("General/ProjectDirPath", defaultProjectDirPath);
	settings->setValue("View/ShowStruct", ui->dockWidgetStruct->isVisible());
	settings->setValue("View/ShowTask", ui->dockWidgetShowTask->isVisible());
	settings->setValue("View/ShowToolBar", ui->toolBar->isVisible());
	settings->setValue("View/Style", appStyle);
}

void HsTestEditor::closeEvent(QCloseEvent *event)
{
	writeSettings();
	QWidget::closeEvent(event);
}

void HsTestEditor::on_actionSetting_triggered()
{
	settingDialog->setAuthor(defaultAuthor);
	settingDialog->setDir(defaultProjectDirPath);
	settingDialog->setTheme(appStyle);
	if(settingDialog->exec() == QDialog::Accepted)
	{
		defaultAuthor = settingDialog->getAuthor();
		defaultProjectDirPath = settingDialog->getDir();
		appStyle = settingDialog->getTheme();
		qApp->setStyle(appStyle);
		writeSettings();
	}
}

void HsTestEditor::on_actionDelTask_triggered()
{
	if(!testManager->delTestNode(ui->twStruct->currentItem()->text(0).toInt() - 1))
	{
		QMessageBox::critical(this, trUtf8("Удаление задания"), trUtf8("Невозможно удалить задание №") + ui->twStruct->currentItem()->text(0));
		return;
	}
	showTree();
	showTest();
}

void HsTestEditor::on_actionEditTask_triggered()
{
	on_twStruct_itemDoubleClicked(ui->twStruct->currentItem(), 0);
}

void HsTestEditor::on_twStruct_customContextMenuRequested(const QPoint &pos)
{
	ui->actionDelTask->setEnabled(true);
	ui->actionEditTask->setEnabled(true);
	QMenu menu(ui->twStruct);
	menu.addAction(ui->actionAddTask);
	menu.addAction(ui->actionEditTask);
	menu.addAction(ui->actionDelTask);
	menu.exec(QCursor::pos());
}

void HsTestEditor::on_twStruct_itemActivated()
{
	ui->actionDelTask->setEnabled(true);
	ui->actionEditTask->setEnabled(true);
}

#include "HsTestEditor.moc"
