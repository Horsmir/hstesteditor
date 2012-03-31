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


#include "htmltemplate.h"

HtmlTemplate::HtmlTemplate(QObject *parent): QObject(parent)
{
	templates.insert("head", trUtf8("<html>\n<head>\n<meta name=\"qrichtext\" content=\"1\" />\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\n<title>%1</title>\n<style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style>\n</head>\n<body style=\" font-size:12pt; font-weight:400; font-style:normal; text-decoration:none;\">\n<center>\n<h1>%1</h2>\n</center>\n<hr />\n<p align=\"left\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\n<b>Автор:</b> %2<br />\n<b>Дата создания:</b> %3<hr />\n"));
	
	templates.insert("closeTestAnswOn", trUtf8("<img src=\":/icons/chbon.png\" /> %1<br />\n"));
	templates.insert("closeTestAnswOff", trUtf8("<img src=\":/icons/chboff.png\" /> %1<br />\n"));
	
	templates.insert("closeTest", trUtf8("<h3>Задание №%1</h3>\n<p align=\"left\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\n<i>%2</i><br />\n<b>Вопрос:</b> %3<br />\n\%4\n</p>\n<hr />\n"));
	
	templates.insert("openTest", trUtf8("<h3>Задание №%1</h3>\n<p align=\"left\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\n<i>%2</i><br />\n<b>Вопрос:</b> %3<br />\n<b>Ответ:</b> %4\n</p>\n<hr />\n"));
	
	templates.insert("conformityTest", trUtf8("<h3>Задание №%1</h3>\n<i>%2</i><br />\n<table border=\"1\" align=\"left\" cellspacing=\"0\" cellpadding=\"4\">\n%3\n</table>\n<hr />\n"));
	
	templates.insert("conformityTestAnsw", trUtf8("<tr><td>%1</td>\n<td>%2</td>\n</tr>"));
	templates.insert("regulatingTests", trUtf8("<h3>Задание №%1</h3>\n<i>%2</i><br />\n<ol style=\"-qt-list-indent: 1;\">\n%3\n</ol>\n<hr />\n"));
	
	templates.insert("regulatingTestsAnsw", trUtf8("<li>%1</li>\n"));
	
	templates.insert("end", "</body></html>");
}

HtmlTemplate::~HtmlTemplate()
{

}

QString HtmlTemplate::getTemplate(const QString &name) const
{
	return templates.value(name);
}
