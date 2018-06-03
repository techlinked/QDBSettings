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
    void test();


    /*
     * *
     *     void setHost(const QString& host);
    void setDataBaseName(const QString& dbname);
    void setUserName(const QString& username);
    void setPassword(const QString& password);
    void setTableName(const QString& table_name);
    QString getHost() const;
    QString getDataBaseName() const;
    QString getUserName() const;
    QString getTableName() const;
     */
};

#endif // TDD_H
