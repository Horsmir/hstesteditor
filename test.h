/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

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


#ifndef TEST_H
#define TEST_H

#include <QDebug>
#include <QObject>
#include <QDate>
#include <QFile>
#include "testnode.h"


class Test : public QObject
{

public:
	Test(QObject *parent = 0);
	Test(const Test &other);
	virtual ~Test();
	virtual Test &operator= (const Test &other);
	virtual bool operator== (const Test &other) const;

	void setName(const QString &name_test);
	void setAuthor(const QString &author_test);
	void setCreateDate(QDate date);
	void setNumVis(int nvis);
	void setVis();
	void setNoVis();
	void setCount(int c);
	void setNodeList(const QList<TestNode> &nodeList);

	void addNode(const TestNode &test_node);

	QString getName() const;
	QString getAuthor() const;
	QDate getCreateDate() const;
	int getNumVis() const;
	int getCount() const;
	bool checkVis();
	TestNode getNode(int index) const;
	const TestNode *getNodePtr(int index) const;
	bool getVis() const;
	QList<TestNode> getNodeList() const;

	bool readFromText(const QString &text_file);

	void clear();
	void shuffle();

private:
	QString name;       // Название.
	QString author;      // Автор.
	QDate createDate;   // Дата создания.
	int count;          // Количество заданий.
	int numVis;         // Количество отображаемых заданий.
	bool vis;           // Включить "true" в тренировочный режим или нет - "false".
	QList<TestNode> nodeList; // Список заданий.

	void readNodeCloseFromText(QString &str_node);
	void readNodeOpenFromText(QString &str_node);
	void readNodeConformityFromText(QString &str_node);
	void readNodeRegulatingFromText(QString &str_node);
};

QDataStream &operator << (QDataStream &out, const Test &test);
QDataStream &operator >> (QDataStream &in, Test &test);

#endif // TEST_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs off; tab-width 4; 
