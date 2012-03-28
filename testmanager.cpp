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


#include "testmanager.h"

TestManager::TestManager(QObject *parent):
	QObject(parent)
{
	magicNumber = 0xAAFF452C;
	currentTest = 0;
	currentTestFileName = "";
}

TestManager::~TestManager()
{
	
}

void TestManager::createTest(const QString &testName, const QString &testAuthor, const QString &testFileName)
{
	currentTest = new Test(this);
	currentTest->setName(testName);
	currentTest->setAuthor(testAuthor);
	currentTest->setCreateDate(QDate::currentDate());
	
	currentTestFileName = testFileName;
	saveTest();
}

void TestManager::openTest(const QString &testFileName)
{
	Test test;
	quint32 magic;
	quint16 version;
	
	QFile file(testFileName);
	if(!file.exists())
	{
		qDebug() << "File " << testFileName << " not exists.";
		return;
	}
	if(!file.open(QIODevice::ReadOnly))
	{
		qDebug() << "Can't open file " << testFileName << " for reading. " << file.errorString();
		return;
	}
	
	QDataStream in(&file);
	in >> magic >> version;
	if(magic != magicNumber)
	{
		qDebug() << "File is not recognized by this application";
		return;
	}
	else if(version > in.version())
	{
		qDebug() << "File is from a more recent version of the" << "application";
		return;
	}
	
	if(currentTest == 0)
		currentTest = new Test(this);
	in >> *currentTest;
	currentTestFileName = testFileName;
}

void TestManager::saveTest()
{
	if(currentTestFileName.isEmpty())
		return;
	QFile file(currentTestFileName);
	if(!file.open(QIODevice::WriteOnly))
	{
		qDebug() << "Can't open file " << currentTestFileName << " for writing. " << file.errorString();
		return;
	}
	
	QDataStream out(&file);
	out << quint32(magicNumber) << quint16(out.version());
	out << *currentTest;
}

quint32 TestManager::getCount() const
{
	return currentTest->getCount();
}

const TestNode *TestManager::getNodeById(quint32 index) const
{
	return currentTest->getNodePtr(index);
}

QString TestManager::getTestAuthor() const
{
	return currentTest->getAuthor();
}

QString TestManager::getTestCreateDate() const
{
	return currentTest->getCreateDate().toString("dd.MM.yyyy");
}

QString TestManager::getTestName() const
{
	return currentTest->getName();
}

void TestManager::addTestNode(TestNode testNode)
{
	currentTest->addNode(testNode);
}

TestNode *TestManager::getNodeForChange(quint32 index)
{
	return currentTest->getNodePtrForChange(index);
}
