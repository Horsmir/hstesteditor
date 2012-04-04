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


#ifndef DLGFIND_H
#define DLGFIND_H

#include <QtGui/QDialog>
#include <QtGui/QCheckBox>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>

class DlgFind : public QDialog
{
	Q_OBJECT
	
public:
	explicit DlgFind(QWidget *parent = 0, Qt::WindowFlags f = 0);
	
signals:
	void findNext(const QString &str, Qt::CaseSensitivity cs);
	void findPrev(const QString &str, Qt::CaseSensitivity cs);
	
private slots:
	void findClicked();
	void enableFindButton(const QString &text);
	
private:
	QLabel *label;
	QLineEdit *lineEdit;
	QCheckBox *caseCheckBox;
	QCheckBox *backwardCheckBox;
	QPushButton *findButton;
	QPushButton *closeButton;
};

#endif // DLGFIND_H
