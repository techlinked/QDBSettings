#include "tdd.h"
#include <QDebug>

TDD::TDD(QObject *parent) : QObject(parent)
{

}

void TDD::test()
{
    qDebug() << "Test run";
}

QTEST_MAIN(TDD)
