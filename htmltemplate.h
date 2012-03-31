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


#ifndef HTMLTEMPLATE_H
#define HTMLTEMPLATE_H

#include <QtCore/QObject>
#include <QtCore/QMap>


class HtmlTemplate : public QObject
{
public:
	explicit HtmlTemplate(QObject *parent = 0);
	virtual ~HtmlTemplate();
	
	QString getTemplate(const QString &name) const;
	
private:
	QMap<QString, QString>  templates;
};

#endif // HTMLTEMPLATE_H
