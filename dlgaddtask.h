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


#ifndef DLGADDTASK_H
#define DLGADDTASK_H

#include <QtGui/QDialog>
#include <QtCore/qmath.h>
#include "ui_dlgaddtask.h"
#include "testnode.h"

namespace Ui {
	class DlgAddTask;
}

class DlgAddTask : public QDialog
{
	Q_OBJECT
	
public:
	explicit DlgAddTask(QWidget *parent = 0, Qt::WindowFlags f = 0);
	virtual ~DlgAddTask();
	
	void setNode(TestNode *node);
	TestNode *getTestNode() const;
	void setEdit(bool edit);
	
	int exec();
	
private slots:
	void on_rbtnClose_clicked();
	void on_rbtnOpen_clicked();
	void on_rbtnConform_clicked();
	void on_rbtnReg_clicked();
	void on_btnNext_clicked();
	void on_btnCloseAddAnsw_clicked();
	void on_btnOpenAddAnsw_clicked();
	void on_btnConformAdd_clicked();
	void on_btnRegAdd_clicked();
	void on_btnCancel_clicked();
	void on_lwCloseAnswers_clicked();
	void on_btnCloseDel_clicked();
	void on_btnCloseEdit_clicked();
	void on_lwOpenAnswers_clicked();
	void on_btnOpenEdit_clicked();
	void on_btnOpenDel_clicked();
	void on_btnConformDel_clicked();
	void on_btnRegDel_clicked();
	void on_lwRegAnswers_clicked();
	void on_btnRegEdit_clicked();
	
private:
	Ui::DlgAddTask *ui;
	TestNode *node;
	bool pageSetUp;
	bool edit;
	
	void setCloseNode();
	void setOpenNode();
	void setConformNode();
	void setRegNode();
	void clear();
};

#endif // DLGADDTASK_H
