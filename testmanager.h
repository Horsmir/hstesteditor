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


#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtCore/qmath.h>
#include "test.h"
#include "testnode.h"


class TestManager : public QObject
{

public:
	explicit TestManager(QObject *parent = 0);
	virtual ~TestManager();
	
	void createTest(const QString &testName, const QString &testAuthor, const QString &testFileName);
	void openTest(const QString &testFileName);
	void saveTest();
	void saveTest(const QString &testFilePath);
	
	void addTestNode(TestNode testNode);
	bool delTestNode(int index);
	
	quint32 getCount() const;
	const TestNode *getNodeById(quint32 index) const;
	TestNode *getNodeForChange(quint32 index);
	QString getTestName() const;
	QString getTestAuthor() const;
	QString getTestCreateDate() const;
	void testToText(const QString &textFileName);
	
private:
	Test *currentTest;
	QString currentTestFileName;
	quint32 magicNumber;
};

#endif // TESTMANAGER_H
