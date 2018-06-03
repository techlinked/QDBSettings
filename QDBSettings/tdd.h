#ifndef TDD_H
#define TDD_H

#include <QtTest/QTest>
#include "qdbsettings.h"

class TDD : public QObject
{
    Q_OBJECT
public:
    explicit TDD(QObject *parent = nullptr);

private slots:
    void test_connect();

    void test_getAllSettings();
    void test_save_get_IntegerParam();
    void test_save_get_TextParam();

    void test_setgetHost();
    void test_setgetDataBaseName();
    void test_setgetUserName();
    void test_setgetTableName();
};

#endif // TDD_H
