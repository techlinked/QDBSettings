#ifndef TDD_H
#define TDD_H

#include <QtTest/QTest>

class TDD : public QObject
{
    Q_OBJECT
public:
    explicit TDD(QObject *parent = nullptr);

private slots:
    void test();
};

#endif // TDD_H
