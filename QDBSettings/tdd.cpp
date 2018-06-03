#include "tdd.h"
#include <QDebug>

/*
 * Before start test need create database with following parameters
 * HostName: 'localhost'
 * DatabaseName: 'settings'
 * UserName: 'qapp'
 * Password: 'pass'
 * TableName: 'qdbsettings'
 * Table:
 *
 *   d | settings_id | text_param | int_param |
 * ----+-------------+------------+-----------+
 *   1 |           1 | param      |       100 |
 *
 *
 * And.. Action!
 * */

TDD::TDD(QObject *parent) : QObject(parent)
{

}

void TDD::test_connect()
{
    QString dbname("settings");
    QDBSettings settings("localhost", dbname, "qapp", "pass", "qdbsettings");
    settings.connect();
    QVERIFY(settings.isConnect().first == true);
    QVERIFY(settings.isConnect().second == dbname);
}

void TDD::test_getAllSettings()
{
    QDBSettings settings("localhost", "settings", "qapp", "pass", "qdbsettings");
    settings.connect();
    QHash<QString, QVariant> all_P = settings.getAllSettings();

    QHash<QString, QVariant>::const_iterator params_i = all_P.constBegin();
    while (params_i != all_P.constEnd()) {
        qDebug() << params_i.key() << ": " << params_i.value();
        ++params_i;
    }
}

void TDD::test_save_get_IntegerParam()
{
    QDBSettings settings("localhost", "settings", "qapp", "pass", "qdbsettings");
    settings.connect();
    int first_param = settings.getIntegerValue("int_param");
    int second_param = 1298;
    QVERIFY(settings.saveIntegerValue("int_param", second_param) == true);
    QVERIFY(first_param != settings.getIntegerValue("int_param"));
    QVERIFY(second_param == settings.getIntegerValue("int_param"));
    QVERIFY(settings.saveIntegerValue("int_param", first_param) == true);
    QVERIFY(first_param == settings.getIntegerValue("int_param"));
}

void TDD::test_save_get_TextParam()
{
    QDBSettings settings("localhost", "settings", "qapp", "pass", "qdbsettings");
    settings.connect();
    QString first_param = settings.getTextValue("text_param");
    QString second_param("second_param");
    QVERIFY(settings.saveTextValue("text_param", second_param) == true);
    QVERIFY(first_param != settings.getTextValue("text_param"));
    QVERIFY(second_param == settings.getTextValue("text_param"));
    QVERIFY(settings.saveTextValue("text_param", first_param) == true);
    QVERIFY(first_param == settings.getTextValue("text_param"));
}

void TDD::test_setgetHost()
{
    QDBSettings settings;
    QString host("host");
    settings.setHost(host);
    QCOMPARE(host, settings.getHost());
}

void TDD::test_setgetDataBaseName()
{
    QDBSettings settings;
    QString dataBaseName("dataBaseName");
    settings.setDataBaseName(dataBaseName);
    QCOMPARE(dataBaseName, settings.getDataBaseName());
}

void TDD::test_setgetUserName()
{
    QDBSettings settings;
    QString userName("userName");
    settings.setUserName(userName);
    QCOMPARE(userName, settings.getUserName());
}

void TDD::test_setgetTableName()
{
    QDBSettings settings;
    QString tableName("name");
    settings.setTableName(tableName);
    QCOMPARE(tableName, settings.getTableName());
}

QTEST_MAIN(TDD)
