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

void TestManager::testToText(const QString &textFileName)
{
	QFile file(textFileName);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Can't open file " << textFileName << " " << file.errorString();
		return;
	}
	
	QTextStream out(&file);
	out << "F1: ";
	out << currentTest->getName() << "\n";
	out << "F2: ";
	out << currentTest->getAuthor() << "\n";
	out << "F3: ";
	out << getTestCreateDate() << "\n";
	
	for(int i = 0; i < currentTest->getCount(); i++)
	{
		TestNode node = currentTest->getNode(i);
		out << "I:\n";
		out << "Q: " << node.getTask() << "\n";
		switch(node.getType())
		{
			case TYPE_NODE_CLOSE:
				out << "S: " << node.getQuestion() << "\n";
				for(int j = 0; j < node.getAnswers().count(); j++)
				{
					int ransw = int(node.getRealsInt()) & int(qPow(2, j));
					if(ransw == 0)
					{
						out << "-: " << node.getAnswers().at(j) << "\n";
					}
					else
					{
						out << "+: " << node.getAnswers().at(j) << "\n";
					}
				}
				break;
			case TYPE_NODE_OPEN:
				out << "S: " << node.getQuestion() << "\n";
				for(int j = 0; j < node.getAnswers().count(); j++)
				{
					out << "+: " << node.getAnswers().at(j) << "\n";
				}
				break;
			case TYPE_NODE_CONFORMITY:
				for(int j = 0; j < node.getAnswers().count(); j++)
				{
					if(j < node.getQuestions().count())
						out << "L" << (j + 1) << ": " << node.getQuestions().at(j) << "\n";
		
					int p = QString(node.getReals().at(j)).toInt() - 1;
					if(p == -1)
						p = node.getAnswers().count() - 1;
		
					out << "R" << (j + 1) << ": " << node.getAnswers().at(p) << "\n";
				}
				break;
			case TYPE_NODE_REGULATING:
				for(int j = 0; j < node.getAnswers().count(); j++)
				{
					int p = QString(node.getReals().at(j)).toInt() - 1;
					out << (j + 1) << ": " << node.getAnswers().at(p) << "\n";
				}
				break;
		}
	}
}

void TestManager::saveTest(const QString &testFilePath)
{
	QFile file(testFilePath);
	if(!file.open(QIODevice::WriteOnly))
	{
		qDebug() << "Can't open file " << testFilePath << " for writing. " << file.errorString();
		return;
	}
	
	QDataStream out(&file);
	out << quint32(magicNumber) << quint16(out.version());
	out << *currentTest;
}
