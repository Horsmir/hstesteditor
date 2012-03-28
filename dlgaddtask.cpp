/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Роман Браун <firdragon76@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "dlgaddtask.h"

DlgAddTask::DlgAddTask(QWidget *parent, Qt::WindowFlags f): QDialog(parent, f), ui(new Ui::DlgAddTask)
{
	ui->setupUi(this);
	
	pageSetUp = false;
	ui->stackedWidget->setCurrentIndex(0);
	node = 0;
	edit = false;
	ui->rbtnClose->setChecked(true);
}

DlgAddTask::~DlgAddTask()
{
	delete ui;
}

void DlgAddTask::on_rbtnClose_clicked()
{
	node->setType(TYPE_NODE_CLOSE);
}

void DlgAddTask::on_rbtnOpen_clicked()
{
	node->setType(TYPE_NODE_OPEN);
}

void DlgAddTask::on_rbtnConform_clicked()
{
	node->setType(TYPE_NODE_CONFORMITY);
}

void DlgAddTask::on_rbtnReg_clicked()
{
	node->setType(TYPE_NODE_REGULATING);
}

void DlgAddTask::on_btnNext_clicked()
{
	if(pageSetUp)
	{
		node->clear();
		switch(node->getType())
		{
			case TYPE_NODE_CLOSE:
				setCloseNode();
				break;
			case TYPE_NODE_OPEN:
				setOpenNode();
				break;
			case TYPE_NODE_CONFORMITY:
				setConformNode();
				break;
			case TYPE_NODE_REGULATING:
				setRegNode();
				break;
			default:
				break;
		}
		
		ui->btnNext->setText(trUtf8("Далее >"));
		pageSetUp = false;
		clear();
		ui->stackedWidget->setCurrentIndex(0);
		ui->rbtnClose->setChecked(true);
		accept();
	}
	else
	{
		switch(node->getType())
		{
			case TYPE_NODE_CLOSE:
				ui->stackedWidget->setCurrentIndex(1);
				break;
			case TYPE_NODE_OPEN:
				ui->stackedWidget->setCurrentIndex(2);
				break;
			case TYPE_NODE_CONFORMITY:
				ui->stackedWidget->setCurrentIndex(3);
				break;
			case TYPE_NODE_REGULATING:
				ui->stackedWidget->setCurrentIndex(4);
				break;
			default:
				node->setType(TYPE_NODE_CLOSE);
				ui->stackedWidget->setCurrentIndex(1);
				break;
		}
		ui->btnNext->setText(trUtf8("Добавить"));
		pageSetUp = true;
	}
}

void DlgAddTask::setCloseNode()
{
	node->setTaskTest(ui->leCloseTask->text());
	node->setQuestion(ui->teCloseQuest->toPlainText());
	
	for(int i = 0; i < ui->lwCloseAnswers->count(); i++)
	{
		QString tmp = ui->lwCloseAnswers->item(i)->text();
		QChar f = tmp[0];
		if(f == '+')
		{
			node->addAnswer(tmp.remove(0, 2), 1);
		}
		else
		{
			node->addAnswer(tmp.remove(0, 2), 0);
		}
	}
}

void DlgAddTask::setOpenNode()
{
	node->setTaskTest(ui->leOpenTask->text());
	node->setQuestion(ui->teOpenQuest->toPlainText());
	
	for(int i = 0; i < ui->lwOpenAnswers->count(); i++)
	{
		QString tmp = ui->lwOpenAnswers->item(i)->text();
		node->addAnswer(tmp);
	}
}

void DlgAddTask::setConformNode()
{
	QString sreal = "";
	node->setTaskTest(ui->leConformTask->text());
	int n = ui->twConformQuestAnsw->rowCount();
	for(int i = 0; i < n; i++)
	{
		if(ui->twConformQuestAnsw->item(i, 0) != 0)
		{
			node->addQuestion(ui->twConformQuestAnsw->item(i, 0)->text());
			sreal += QString().setNum(i + 1);
		}
		if(ui->twConformQuestAnsw->item(i, 1) != 0)
			node->addAnswer(ui->twConformQuestAnsw->item(i, 1)->text());
	}
	if(sreal.length() < n)
		for(int i = 0; i < (n - sreal.length()); i++)
			sreal += QString().setNum(0);
	
		node->setReals(sreal);
}

void DlgAddTask::setRegNode()
{
	QString sreal = "";
	node->setTaskTest(ui->leRegTask->text());
	
	for(int i = 0; i < ui->lwRegAnswers->count(); i++)
	{
		node->addAnswer(ui->lwRegAnswers->item(i)->text());
		sreal += QString().setNum(i + 1);
	}
	node->setReals(sreal);
}

void DlgAddTask::on_btnCloseAddAnsw_clicked()
{
	QString str = "";
	if(ui->chbCloseReal->isChecked())
		str = "+ ";
	else
		str = "- ";
	str += ui->leCloseAnswer->text();
	ui->lwCloseAnswers->addItem(str);
	ui->leCloseAnswer->clear();
	ui->chbCloseReal->setCheckState(Qt::Unchecked);
}

void DlgAddTask::on_btnOpenAddAnsw_clicked()
{
	ui->lwOpenAnswers->addItem(ui->leOpenAnswer->text());
	ui->leOpenAnswer->clear();
}

void DlgAddTask::on_btnConformAdd_clicked()
{
	int n = ui->twConformQuestAnsw->rowCount();
	ui->twConformQuestAnsw->insertRow(n);
	
	if(!ui->teConformQuest->toPlainText().isEmpty())
	{
		QTableWidgetItem *questItem = new QTableWidgetItem(ui->teConformQuest->toPlainText());
		ui->twConformQuestAnsw->setItem(n, 0, questItem);
		ui->teConformQuest->clear();
	}
	
	if(!ui->teConformAnswer->toPlainText().isEmpty())
	{
		QTableWidgetItem *answItem = new QTableWidgetItem(ui->teConformAnswer->toPlainText());
		ui->twConformQuestAnsw->setItem(n, 1, answItem);
		ui->teConformAnswer->clear();
	}
}

void DlgAddTask::on_btnRegAdd_clicked()
{
	ui->lwRegAnswers->addItem(ui->teRegAnswer->toPlainText());
	ui->teRegAnswer->clear();
}

TestNode * DlgAddTask::getTestNode() const
{
	return node;
}

void DlgAddTask::on_btnCancel_clicked()
{
	clear();
	pageSetUp = false;
	edit = false;
	ui->stackedWidget->setCurrentIndex(0);
	ui->btnNext->setText(trUtf8("Далее >"));
	ui->rbtnClose->setChecked(true);
	reject();
}

void DlgAddTask::setNode(TestNode *node)
{
	this->node = node;
}

void DlgAddTask::clear()
{
	ui->leCloseTask->clear();
	ui->leConformTask->clear();
	ui->leOpenTask->clear();
	ui->leRegTask->clear();
	
	ui->teCloseQuest->clear();
	ui->teOpenQuest->clear();
	ui->teConformQuest->clear();
	
	ui->leCloseAnswer->clear();
	ui->leOpenAnswer->clear();
	ui->teConformAnswer->clear();
	ui->teRegAnswer->clear();
	
	ui->lwCloseAnswers->clear();
	ui->lwOpenAnswers->clear();
	ui->lwRegAnswers->clear();
	int n = ui->twConformQuestAnsw->rowCount();
	for(int i = --n; i >= 0; i--)
		ui->twConformQuestAnsw->removeRow(i);
}

void DlgAddTask::on_lwCloseAnswers_clicked()
{
	QString str = ui->lwCloseAnswers->currentItem()->text();
	
	if(str.at(0) == '+')
		ui->chbCloseReal->setCheckState(Qt::Checked);
	else
		ui->chbCloseReal->setCheckState(Qt::Unchecked);
	
	ui->leCloseAnswer->setText(str.remove(0, 2));
}

void DlgAddTask::on_btnCloseDel_clicked()
{
	delete ui->lwCloseAnswers->currentItem();
	ui->chbCloseReal->setCheckState(Qt::Unchecked);
	ui->leCloseAnswer->clear();
}

void DlgAddTask::on_btnCloseEdit_clicked()
{
	QString str;
	if(ui->chbCloseReal->isChecked())
		str = "+ ";
	else
		str = "- ";
	str += ui->leCloseAnswer->text();
	
	ui->lwCloseAnswers->currentItem()->setText(str);
}

void DlgAddTask::on_lwOpenAnswers_clicked()
{
	ui->leOpenAnswer->setText(ui->lwOpenAnswers->currentItem()->text());
}

void DlgAddTask::on_btnOpenEdit_clicked()
{
	ui->lwOpenAnswers->currentItem()->setText(ui->leOpenAnswer->text());
}

void DlgAddTask::on_btnOpenDel_clicked()
{
	delete ui->lwOpenAnswers->currentItem();
	ui->leOpenAnswer->clear();
}

void DlgAddTask::on_btnConformDel_clicked()
{
	ui->twConformQuestAnsw->removeRow(ui->twConformQuestAnsw->currentRow());
}

void DlgAddTask::on_btnRegDel_clicked()
{
	delete ui->lwRegAnswers->currentItem();
	ui->teRegAnswer->clear();
}

void DlgAddTask::on_lwRegAnswers_clicked()
{
	ui->teRegAnswer->setText(ui->lwRegAnswers->currentItem()->text());
}

void DlgAddTask::on_btnRegEdit_clicked()
{
	ui->lwRegAnswers->currentItem()->setText(ui->teRegAnswer->toPlainText());
}

int DlgAddTask::exec()
{
	if(edit)
	{
		clear();
		int nq, na;
		switch(node->getType())
		{
			case TYPE_NODE_CLOSE:
				ui->stackedWidget->setCurrentIndex(1);
				ui->leCloseTask->setText(node->getTask());
				ui->teCloseQuest->setText(node->getQuestion());
				for(int i = 0; i < node->getAnswers().count(); i++)
				{
					int n = qPow(2, i);
					if((n & node->getRealsInt()) == 0)
						ui->lwCloseAnswers->addItem("- " + node->getAnswers().at(i));
					else
						ui->lwCloseAnswers->addItem("+ " + node->getAnswers().at(i));
				}
				break;
			case TYPE_NODE_OPEN:
				ui->stackedWidget->setCurrentIndex(2);
				ui->leOpenTask->setText(node->getTask());
				ui->teOpenQuest->setText(node->getQuestion());
				ui->lwOpenAnswers->addItems(node->getAnswers());
				break;
			case TYPE_NODE_CONFORMITY:
				ui->stackedWidget->setCurrentIndex(3);
				ui->leConformTask->setText(node->getTask());
				nq = node->getQuestions().count();
				na = node->getAnswers().count();
				ui->twConformQuestAnsw->setRowCount(na);
				for(int i = 0; i < nq; i++)
					ui->twConformQuestAnsw->setItem(i, 0, new QTableWidgetItem(node->getQuestions().at(i)));
				for(int i = 0; i < na; i++)
					ui->twConformQuestAnsw->setItem(i, 1, new QTableWidgetItem(node->getAnswers().at(i)));
				break;
			case TYPE_NODE_REGULATING:
				ui->stackedWidget->setCurrentIndex(4);
				ui->leRegTask->setText(node->getTask());
				ui->lwRegAnswers->addItems(node->getAnswers());
				break;
			default:
				node->setType(TYPE_NODE_CLOSE);
				ui->stackedWidget->setCurrentIndex(1);
				break; 
		}
		
		ui->btnNext->setText(trUtf8("Изменить"));
		pageSetUp = true;
		edit = false;
	}
	return QDialog::exec();
}

void DlgAddTask::setEdit(bool edit)
{
	this->edit = edit;
}

#include "dlgaddtask.moc"