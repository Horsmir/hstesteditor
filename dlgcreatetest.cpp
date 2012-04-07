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


#include "dlgcreatetest.h"

DlgCreateTest::DlgCreateTest(QWidget *parent, Qt::WindowFlags f): QDialog(parent, f), ui(new Ui::DlgCreateTest)
{
	ui->setupUi(this);
	
	QDir testDirectory = QDir::home();
	ui->leTestDir->setText(testDirectory.absolutePath());
}

DlgCreateTest::~DlgCreateTest()
{
	delete ui;
}

QString DlgCreateTest::getTestName() const
{
	return ui->leTestName->text();
}

QString DlgCreateTest::getAuthor() const
{
	return ui->leAuthor->text();
}

QString DlgCreateTest::getTestDir() const
{
	return ui->leTestDir->text();
}

void DlgCreateTest::on_toolBtnTestDir_clicked()
{
	QFileDialog::Options options;
	options |= QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::DontUseNativeDialog;
	
	QString testDir = QFileDialog::getExistingDirectory(this, trUtf8("Выбрать каталог"), ui->leTestDir->text(), options);
	if(!testDir.isEmpty())
		ui->leTestDir->setText(testDir);
}

void DlgCreateTest::setAuthor(const QString &author)
{
	ui->leAuthor->setText(author);
}

void DlgCreateTest::setDir(const QString &dir)
{
	ui->leTestDir->setText(dir);
}

#include "dlgcreatetest.moc"