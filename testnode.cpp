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


#include "testnode.h"

TestNode::TestNode() :
    QObject()
{
    type = TYPE_NODE_UNKNOWN;
    task = "";
    question = "";
    reals = 0;
    sreals = "";
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

TestNode::TestNode ( int typeNode ) :
    QObject()
{
    type = typeNode;
    task = "";
    question = "";
    reals = 0;
    sreals = "";
}

TestNode::TestNode ( const TestNode& other ) :
    QObject()
{
    type = other.type;
    task = other.task;
    question = other.question;
    reals = other.reals;
    sreals = other.sreals;
    answers = other.answers;
    questions = other.questions;
}

TestNode::~TestNode()
{

}

TestNode& TestNode::operator= ( const TestNode& other )
{
    type = other.type;
    task = other.task;
    question = other.question;
    reals = other.reals;
    sreals = other.sreals;
    answers = other.answers;
    questions = other.questions;
    return *this;
}

bool TestNode::operator== ( const TestNode& other ) const
{
    if(type != other.type)
        return false;
    if(task != other.task)
        return false;
    if(question != other.question)
        return false;
    if(reals != other.reals)
        return false;
    if(sreals != other.sreals)
        return false;
    if(answers != other.answers)
        return false;
    if(questions != other.questions)
        return false;
    return true;
}

QString TestNode::getTask() const
{
    return task;
}

void TestNode::setTaskTest ( const QString &sTask )
{
    task = sTask;
}

int TestNode::getType() const
{
    return type;
}

QString TestNode::getQuestion() const
{
    return question;
}

const QStringList TestNode::getAnswers() const
{
    return answers;
}

qint8 TestNode::getRealsInt() const
{
    return reals;
}

QString TestNode::getReals() const
{
    return sreals;
}

QStringList TestNode::getQuestions() const
{
    return questions;
}

void TestNode::setQuestion ( const QString &quest )
{
    question = quest;
}

void TestNode::addAnswer ( const QString &answ, qint8 real )
{
    int count = answers.count();
    answers << answ;
    reals += real * std::pow ( 2, count );
}

void TestNode::addAnswer ( const QString &answ )
{
    answers << answ;
}

bool TestNode::checkAnswer ( const qint8 &answ ) const
{
    return ( reals == answ );
}

bool TestNode::checkAnswer ( const QString &answ ) const
{
    return ( sreals == answ );
}

void TestNode::setReals (const QString &real )
{
    sreals = real;
}

void TestNode::addQuestion ( const QString &quest )
{
    questions << quest;
}

void TestNode::setAnswers ( const QStringList &answers )
{
    this->answers = answers;
}

void TestNode::setQuestions ( const QStringList &questions )
{
    this->questions = questions;
}

void TestNode::setRealsInt ( qint8 real )
{
    this->reals = real;
}

void TestNode::setType ( int typeNode )
{
    this->type = typeNode;
}

bool TestNode::checkAnswerOpen ( const QString &answ ) const
{
    int count = answers.count();
    for ( int i = 0; i < count; i++ )
    {
        QRegExp rx(answers.at(i));
        rx.setPatternSyntax(QRegExp::WildcardUnix);
        if ( rx.exactMatch(answ) )
            return true;
    }
    return false;
}

void TestNode::shuffle()
{
    switch(type)
    {
        case TYPE_NODE_CLOSE:
            shuffleClose();
            break;
        case TYPE_NODE_OPEN:
            shuffleOpen();
            break;
        case TYPE_NODE_CONFORMITY:
            shuffleConformity();
            break;
        case TYPE_NODE_REGULATING:
            shuffleRegulating();
            break;
        default:
            return;
    }
}

void TestNode::shuffleClose()
{
    quint32 num = answers.count();
    quint32 a = 0, b = 0, c = 0, j = 0, i = 0;
    quint32 *d = new quint32[num];
    QStringList tmp1, tmp2;
    QString sep = "&$";
    
    for(i = 0; i < num; i++)
    {
        qint8 ans = qint8(std::pow(2, i)) & reals;
        if(ans > 0)
            ans = 1;
        tmp1.append(answers.at(i) + sep + QString().setNum(ans));
    }
    
    for(i = 0; i < num; i ++)
        d[i] = i;
    
    while(j < (num * 2))
    {
        a = qrand() % num;
        b = qrand() % num;
        c = d[a];
        d[a] = d[b];
        d[b] = c;
        j++;
    }
    
    for(i = 0; i < num; i++)
    {
        tmp2.append(tmp1.at(d[i]));
    }
    
    answers.clear();
    reals = 0;
    
    for(i = 0; i < num; i++)
    {
        QStringList tmp3 = tmp2.at(i).split(sep);
        answers.append(tmp3.at(0));
        reals += tmp3.at(1).toUInt() * std::pow(2, i);
    }
    delete[] d;
}

void TestNode::shuffleConformity()
{
    quint32 numQuestion = questions.count();
    quint32 numAnswers = answers.count();
    quint32 a = 0, b = 0, c = 0, j = 0, i = 0;
    quint32 *d1 = new quint32[numQuestion];
    quint32 *d2 = new quint32[numAnswers];
    QStringList tmp1, tmp2, tmp3, tmp4;
    QString sep = "&$";
    
    for(i = 0; i < numQuestion; i++)
        tmp1.append(questions.at(i) + sep + QString().setNum(i + 1));
    
    for(i = 0; i < numAnswers; i++)
        tmp2.append(answers.at(i) + sep + sreals[i]);
    
    for(i = 0; i < numQuestion; i++)
        d1[i] = i;
    for(i = 0; i < numAnswers; i++)
        d2[i] = i;
    
    while(j < (numQuestion * 2))
    {
        a = qrand() % numQuestion;
        b = qrand() % numQuestion;
        c = d1[a];
        d1[a] = d1[b];
        d1[b] = c;
        j++;
    }
    j = 0;
    while(j < (numAnswers * 2))
    {
        a = qrand() % numAnswers;
        b = qrand() % numAnswers;
        c = d2[a];
        d2[a] = d2[b];
        d2[b] = c;
        j++;
    }
    
    for(i = 0; i < numQuestion; i++)
    {
        tmp3.append(tmp1.at(d1[i]));
    }
    for(i = 0; i < numAnswers; i++)
    {
        tmp4.append(tmp2.at(d2[i]));
    }
    
    sreals = "";
    for(i = 0; i < numAnswers; i++)
    {
        quint32 n = tmp4.at(i).split(sep).at(1).toUInt();
        quint32 id = 0;
        for(j = 0; j < numQuestion; j++)
        {
            if(tmp3.at(j).split(sep).at(1).toUInt() == n)
            {
                id = j + 1;
                break;
            }
        }
        sreals += QString().setNum(id);
    }
    
    questions.clear();
    answers.clear();
    for(i = 0; i < numQuestion; i++)
        questions.append(tmp3.at(i).split(sep).at(0));
    for(i = 0; i < numAnswers; i++)
        answers.append(tmp4.at(i).split(sep).at(0));
    
    delete[] d1;
    delete[] d2;
}

void TestNode::shuffleOpen()
{
    return;
}

void TestNode::shuffleRegulating()
{
    quint32 num = answers.count();
    quint32 a = 0, b = 0, c = 0, j = 0, i = 0;
    quint32 *d = new quint32[num];
    QStringList tmp1, tmp2;
    QString sep = "&$";
    
    for(i = 0; i < num; i++)
    {
        tmp1.append(answers.at(i) + sep + sreals[i]);
    }
    
    for(i = 0; i < num; i ++)
        d[i] = i;
    
    while(j < (num * 2))
    {
        a = qrand() % num;
        b = qrand() % num;
        c = d[a];
        d[a] = d[b];
        d[b] = c;
        j++;
    }
    
    for(i = 0; i < num; i++)
    {
        tmp2.append(tmp1.at(d[i]));
    }
    
    answers.clear();
    sreals = "";
    
    for(i = 0; i < num; i++)
    {
        QStringList tmp3 = tmp2.at(i).split(sep);
        answers.append(tmp3.at(0));
        sreals += tmp3.at(1);
    }
    delete[] d;
}

//=========================================================================================//

QDataStream &operator << ( QDataStream &out, const TestNode &node )
{
    out << qint32 ( node.getType() ) << node.getTask() << node.getQuestion() << node.getQuestions()
        << node.getAnswers() << qint8 ( node.getRealsInt() ) << node.getReals();

    return out;
}

QDataStream &operator >> ( QDataStream &in, TestNode &node )
{
    qint32 type;
    QString task, quest, sreal;
    qint8 real;
    QStringList answers, quests;

    in >> type >> task >> quest >> quests >> answers >> real >> sreal;
    node.setType ( type );
    node.setTaskTest ( task );
    node.setQuestion ( quest );
    node.setQuestions ( quests );
    node.setAnswers ( answers );
    node.setRealsInt ( real );
    node.setReals ( sreal );

    return in;
}

///////////////////////////////////////////////////////////////////////////////
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
