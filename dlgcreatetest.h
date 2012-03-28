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


#ifndef DLGCREATETEST_H
#define DLGCREATETEST_H

#include <QtGui/QDialog>
#include <QtCore/QDir>
#include <QtGui/QFileDialog>
#include "ui_dlgcreatetest.h"

namespace Ui {
	class DlgCreateTest;
}

class DlgCreateTest : public QDialog
{
	Q_OBJECT
	
public:
	explicit DlgCreateTest(QWidget *parent = 0, Qt::WindowFlags f = 0);
	virtual ~DlgCreateTest();
	
	QString getTestName() const;
	QString getTestDir() const;
	QString getAuthor() const;
	
private slots:
	void on_toolBtnTestDir_clicked();
	
private:
	Ui::DlgCreateTest *ui;
};

#endif // DLGCREATETEST_H
