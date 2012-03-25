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


#include "test.h"

Test::Test(QObject *parent):
	QObject(parent)
{
	name = "";
	author = "";
	createDate = QDate::currentDate();
	count = 0;
	numVis = 0;
	vis = false;
}

Test::Test(const Test &other)
{
	name = other.name;
	author = other.author;
	createDate = other.createDate;
	count = other.count;
	numVis = other.numVis;
	vis = other.vis;
	nodeList = other.nodeList;
}

Test::~Test()
{

}

Test &Test::operator= (const Test &other)
{
	name = other.name;
	author = other.author;
	createDate = other.createDate;
	count = other.count;
	numVis = other.numVis;
	vis = other.vis;
	nodeList = other.nodeList;
	return *this;
}

bool Test::operator== (const Test &other) const
{
	if(name != other.name)
		return false;
	if(author != other.author)
		return false;
	if(createDate != other.createDate)
		return false;
	if(count != other.count)
		return false;
	if(numVis != other.numVis)
		return false;
	if(vis != other.vis)
		return false;
	return true;
}

void Test::setName(const QString &name_test)
{
	name = name_test;
}

void Test::setAuthor(const QString &author_test)
{
	author = author_test;
}

void Test::setCreateDate(QDate date)
{
	createDate = date;
}

void Test::setNumVis(int nvis)
{
	numVis = nvis;
}

void Test::setVis()
{
	vis = true;
}

void Test::setNoVis()
{
	vis = false;
}

void Test::addNode(const TestNode &test_node)
{
	nodeList.append(test_node);
	count += 1;
}

QString Test::getName() const
{
	return name;
}

QString Test::getAuthor() const
{
	return author;
}

QDate Test::getCreateDate() const
{
	return createDate;
}

int Test::getNumVis() const
{
	return numVis;
}

int Test::getCount() const
{
	return count;
}

bool Test::checkVis()
{
	return vis;
}

TestNode Test::getNode(int index) const
{
	if(index >= count)
	{
		qDebug() << "in Test::getNode index >= count";
		return 0;
	}

	return nodeList.at(index);
}

bool Test::readFromText(const QString &text_file)
{
	QFile file(text_file);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "in Test::readFromText file \"" << text_file << "\" not opening";
		return false;
	}

	QTextStream in(&file);
	QString test_all = in.readAll();
	file.close();

	QStringList test_nodes = test_all.split("I:");
	QStringList tmp1 = test_nodes.at(0).split("\n");
	name = tmp1.at(0).split(":").at(1).trimmed();
	author = tmp1.at(1).split(":").at(1).trimmed();
	createDate = QDate::currentDate();

	tmp1.clear();
	for(int i = 1; i < test_nodes.count(); i++)
	{
		if((test_nodes.at(i).indexOf("+:")) != (-1))
			if((test_nodes.at(i).indexOf("-:")) != (-1))
				readNodeCloseFromText(test_nodes[i]);
			else
				readNodeOpenFromText(test_nodes[i]);
		else if((test_nodes.at(i).indexOf("L1:")) != (-1))
			readNodeConformityFromText(test_nodes[i]);
		else if((test_nodes.at(i).indexOf("1:")) != (-1))
			readNodeRegulatingFromText(test_nodes[i]);
		else
			return false;
	}

	count = nodeList.count();
	return true;
}

void Test::readNodeCloseFromText(QString &str_node)
{
	TestNode node(TYPE_NODE_CLOSE);
	QStringList str_list = str_node.split("\n");

	for(int i = 0; i < str_list.count(); i++)
	{
		if(str_list.at(i).isEmpty())
			continue;
		QStringList tmp = str_list.at(i).split(":");
		if(tmp.count() < 2)
			continue;
		if(tmp.at(0) == "Q")
			node.setTaskTest(tmp.at(1).trimmed());
		if(tmp.at(0) == "S")
			node.setQuestion(tmp.at(1).trimmed());
		if(tmp.at(0) == "+")
			node.addAnswer(tmp.at(1).trimmed(), 1);
		if(tmp.at(0) == "-")
			node.addAnswer(tmp.at(1).trimmed(), 0);
	}
	nodeList.append(node);
}

void Test::readNodeOpenFromText(QString &str_node)
{
	TestNode node(TYPE_NODE_OPEN);
	QStringList str_list = str_node.split("\n");

	for(int i = 0; i < str_list.count(); i++)
	{
		if(str_list.at(i).isEmpty())
			continue;
		QStringList tmp = str_list.at(i).split(":");
		if(tmp.count() < 2)
			continue;
		if(tmp.at(0) == "Q")
			node.setTaskTest(tmp.at(1).trimmed());
		if(tmp.at(0) == "S")
			node.setQuestion(tmp.at(1).trimmed());
		if(tmp.at(0) == "+")
			node.addAnswer(tmp.at(1).trimmed());
	}
	nodeList.append(node);
}

void Test::readNodeConformityFromText(QString &str_node)
{
	TestNode node(TYPE_NODE_CONFORMITY);
	QStringList str_list = str_node.split("\n");
	QString real_answ = "";
	QRegExp qu("^L\\d"), an("^R\\d");
	QByteArray q_id, a_id;
	int answ_index = 0;

	for(int i = 0; i < str_list.count(); i++)
	{
		if(str_list.at(i).isEmpty())
			continue;
		QStringList tmp = str_list.at(i).split(":");
		if(tmp.count() < 2)
			continue;
		if(tmp.at(0) == "Q")
			node.setTaskTest(tmp.at(1).trimmed());
		if(qu.exactMatch(tmp.at(0)))
		{
			node.addQuestion(tmp.at(1).trimmed());
			q_id.append(QChar(tmp.at(0).trimmed() [1]));
		}
		if(an.exactMatch(tmp.at(0)))
		{
			node.addAnswer(tmp.at(1).trimmed());
			a_id.append(QChar(tmp.at(0).trimmed() [1]));
		}

	}
	for(int i = 0; i < a_id.count(); i++)
	{
		answ_index = q_id.indexOf(a_id[i]);
		real_answ += QString().setNum(answ_index + 1);
	}
	node.setReals(real_answ);
	nodeList.append(node);
}

void Test::readNodeRegulatingFromText(QString &str_node)
{
	TestNode node(TYPE_NODE_REGULATING);
	QStringList str_list = str_node.split("\n");
	QString real_answ = "";
	QRegExp an("^\\d");

	for(int i = 0; i < str_list.count(); i++)
	{
		if(str_list.at(i).isEmpty())
			continue;
		QStringList tmp = str_list.at(i).split(":");
		if(tmp.count() < 2)
			continue;
		if(tmp.at(0) == "Q")
			node.setTaskTest(tmp.at(1).trimmed());
		if(an.exactMatch(tmp.at(0)))
		{
			node.addAnswer(tmp.at(1).trimmed());
			real_answ += tmp.at(0).trimmed();
		}

	}
	node.setReals(real_answ);
	nodeList.append(node);
}

void Test::clear()
{
	name.clear();
	author.clear();
	createDate = QDate::currentDate();
	count = 0;
	numVis = 0;
	vis = false;
	nodeList.clear();
}

bool Test::getVis() const
{
	return vis;
}

void Test::setCount(int c)
{
	count = c;
}

QList< TestNode > Test::getNodeList() const
{
	return nodeList;
}

void Test::setNodeList(const QList< TestNode >& nodeList)
{
	this->nodeList = nodeList;
}

const TestNode *Test::getNodePtr(int index) const
{
	return &(nodeList[index]);
}

void Test::shuffle()
{
	for(int i = 0; i < nodeList.count(); i++)
		nodeList[i].shuffle();
}

//===============================================================================================//

QDataStream &operator << (QDataStream &out, const Test &test)
{
	out << test.getName() << test.getAuthor() << test.getCreateDate() << int (test.getCount())
		<< int (test.getNumVis()) << bool (test.getVis()) << test.getNodeList();
	return out;
}
QDataStream &operator >> (QDataStream &in, Test &test)
{
	QString name, author;
	int count, numVis, nodeType;
	bool vis;
	QDate createDate;
	TestNode node;
	QList<TestNode> nodeList;

	test.clear();
	in >> name >> author >> createDate >> count >> numVis >> vis >> nodeList;
	test.setName(name);
	test.setAuthor(author);
	test.setCreateDate(createDate);
	test.setCount(count);
	test.setNumVis(numVis);
	if(vis)
		test.setVis();
	else
		test.setNoVis();
	test.setNodeList(nodeList);

	return in;
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs off; tab-width 4; 
