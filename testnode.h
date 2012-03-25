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


#ifndef TESTNODE_H
#define TESTNODE_H

#include <QObject>
#include <QStringList>
#include <QTime>
#include <cmath>

#define TYPE_NODE_UNKNOWN -1 // Неизвестный тип
#define TYPE_NODE_CLOSE 0 //Закрытый тип
#define TYPE_NODE_OPEN 1 // Открытый тип
#define TYPE_NODE_CONFORMITY 2 // тип на соответствие
#define TYPE_NODE_REGULATING 3 // тип на упорядоче


/**
 * @brief Базовый класс заданий для теста.
 **/
class TestNode : public QObject
{

public:
    TestNode();
    TestNode ( const TestNode& other );
    TestNode ( int typeNode );
    virtual ~TestNode();
    virtual TestNode& operator= ( const TestNode& other );
    virtual bool operator== ( const TestNode& other ) const;

    void addAnswer ( const QString &answ, qint8 real );
    void addAnswer ( const QString &answ );
    void addQuestion ( const QString& quest );
    
    void setTaskTest ( const QString& sTask );
    void setType ( int typeNode );
    void setQuestion ( const QString& quest );
    void setReals ( const QString& real );
    void setRealsInt ( qint8 real );
    void setAnswers ( const QStringList& answers );
    void setQuestions ( const QStringList& questions );
    
    QString getTask() const;
    int getType() const;
    QString getQuestion() const;
    const QStringList getAnswers() const;
    qint8 getRealsInt() const;
    QString getReals() const;
    QStringList getQuestions() const;
    
    bool checkAnswer ( const qint8 &answ ) const;
    bool checkAnswer ( const QString& answ ) const;
    bool checkAnswerOpen(const QString &answ) const;
    
    void shuffle();

private:
    int type;
    QString task;
    QString question;
    QStringList answers;
    qint8 reals;
    QString sreals;
    QStringList questions;
    
    void shuffleClose();
    void shuffleOpen();
    void shuffleConformity();
    void shuffleRegulating();
};

//===================== Перегруженные операторы =====================================//

QDataStream &operator << ( QDataStream &out, const TestNode &node );
QDataStream &operator >> ( QDataStream &in, TestNode &node );

#endif // TESTNODE_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
