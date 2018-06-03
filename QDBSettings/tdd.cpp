#include "tdd.h"
#include <QDebug>


TDD::TDD(QObject *parent) : QObject(parent)
{

}

void TDD::test()
{
    QDBSettings settings("localhost", "settings", "qapp", "pass", "qdbsettings");
    settings.connect();
    qDebug() << settings.getIntegerValue("int_param");
    qDebug() << settings.getTextValue("text_param");
}

QTEST_MAIN(TDD)
