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


#include "dlgfind.h"

DlgFind::DlgFind(QWidget *parent, Qt::WindowFlags f): QDialog(parent, f)
{
	label = new QLabel(trUtf8("&Что искать:"), this);
	lineEdit = new QLineEdit(this);
	label->setBuddy(lineEdit);
	
	caseCheckBox = new QCheckBox(trUtf8("&Учитывать регистр"), this);
	backwardCheckBox = new QCheckBox(trUtf8("&Обратный поиск"), this);
	
	findButton = new QPushButton(trUtf8("&Найти"), this);
	findButton->setDefault(true);
	findButton->setEnabled(false);
	
	closeButton = new QPushButton(trUtf8("&Закрыть"), this);
	
	connect(lineEdit, SIGNAL(textChanged(QString)), SLOT(enableFindButton(QString)));
	connect(findButton, SIGNAL(clicked(bool)), SLOT(findClicked()));
	connect(closeButton, SIGNAL(clicked(bool)), SLOT(close()));
	
	QHBoxLayout *topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(label);
	topLeftLayout->addWidget(lineEdit);
	
	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addLayout(topLeftLayout);
	leftLayout->addWidget(caseCheckBox);
	leftLayout->addWidget(backwardCheckBox);
	
	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addWidget(findButton);
	rightLayout->addWidget(closeButton);
	rightLayout->addStretch();
	
	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);
	setLayout(mainLayout);
	
	setWindowTitle(trUtf8("Поиск"));
	setFixedHeight(sizeHint().height());
}

void DlgFind::findClicked()
{
	QString text = lineEdit->text();
	Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
	if(backwardCheckBox->isChecked())
	{
		emit findPrev(text, cs);
	}
	else
	{
		emit findNext(text, cs);
	}
}

void DlgFind::enableFindButton(const QString &text)
{
	findButton->setEnabled(!text.isEmpty());
}

#include "dlgfind.moc"
