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


#include "dlgsetting.h"

DlgSetting::DlgSetting(QWidget *parent, Qt::WindowFlags f): QDialog(parent, f),
	ui(new Ui::DlgSetting)
{
	ui->setupUi(this);
	ui->tabWidget->setTabText(0, trUtf8("Общие"));
	ui->tabWidget->setTabText(1, trUtf8("Вид"));
	ui->tabWidget->setCurrentIndex(0);
	
	ui->cbTheme->addItems(QStyleFactory::keys());
	ui->cbTheme->setCurrentIndex(0);
}

DlgSetting::~DlgSetting()
{
	delete ui;
}

void DlgSetting::setAuthor(const QString &author)
{
	ui->leAuthor->setText(author);
}

void DlgSetting::setDir(const QString &dir)
{
	ui->leProjectDir->setText(dir);
}

void DlgSetting::setTheme(const QString &theme)
{
	int id = ui->cbTheme->findText(theme);
	if(id == -1)
		ui->cbTheme->setCurrentIndex(0);
	else
		ui->cbTheme->setCurrentIndex(id);
}

QString DlgSetting::getAuthor() const
{
	return ui->leAuthor->text();
}

QString DlgSetting::getDir() const
{
	return ui->leProjectDir->text();
}

QString DlgSetting::getTheme() const
{
	return ui->cbTheme->currentText();
}

void DlgSetting::on_btnDir_clicked()
{
	QFileDialog::Options options;
	options |= QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::DontUseNativeDialog;
	
	QString testDir = QFileDialog::getExistingDirectory(this, trUtf8("Выбрать каталог"), ui->leProjectDir->text(), options);
	if(!testDir.isEmpty())
		ui->leProjectDir->setText(testDir);
}

#include "dlgsetting.moc"