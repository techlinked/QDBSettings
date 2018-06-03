#include "qdbsettings.h"

QDBSettings::QDBSettings()
{
    database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase("QPSQL");
    //query = new QSqlQuery();
}

QDBSettings::QDBSettings(const QString &host,
                         const QString &dbname,
                         const QString &username,
                         const QString &pass,
                         const QString& table_name)
{
    database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase("QPSQL");
    query = new QSqlQuery();

    this->host = host;
    this->dbname = dbname;
    this->username = username;
    this->password = pass;
    this->table_name = table_name;
}

QDBSettings::~QDBSettings()
{
    delete database;
    delete query;
}

bool QDBSettings::connect()
{
    database->setHostName("localhost");
    database->setDatabaseName("settings");
    database->setUserName("qapp");
    database->setPassword("pass");
    if(!database->open())
    {
        qDebug() << "Unable to open database";
        return false;
    }
    return true;
}

bool QDBSettings::disconnect()
{
    database->close();
    return true;
}

qint64 QDBSettings::getIntegerValue(const QString &name)
{
    QString response =  "SELECT " + name + " FROM " + table_name + " WHERE user_id = 1";
    int result = query->exec(response);
    if(!result)
    {
        qDebug() << "sql response error";
    }
    query->next();
    return query->value(0).toInt();
}

QString QDBSettings::getTextValue(const QString &name)
{
    QString response =  "SELECT " + name + " FROM " + table_name + " WHERE user_id = 1";
    int result = query->exec(response);
    if(!result)
    {
        qDebug() << "sql response error";
    }
    query->next();
    return query->value(0).toString();
}

bool QDBSettings::saveIntegerValue(const QString &name, const qint64 value)
{
    // UPDATE qdbsettings SET text_param = 'param' WHERE user_id = 1;
    QString response =  "UPDATE " + table_name + " SET " + name + " + " + QString::number(value) + " WHERE user_id = 1";
    qDebug() << response;
    int result = query->exec(response);
    if(!result)
    {
        qDebug() << "sql response error";
    }
}

bool QDBSettings::saveTextValue(const QString &name, const QString &value)
{

}

bool QDBSettings::resetSettings(){}

void QDBSettings::setHost           (const QString &host)       { this->host        = host;       }
void QDBSettings::setDataBaseName   (const QString &dbname)     { this->dbname      = dbname;     }
void QDBSettings::setUserName       (const QString &username)   { this->username    = username;   }
void QDBSettings::setPassword       (const QString &password)   { this->password    = password;   }
void QDBSettings::setTableName      (const QString &table_name) { this->table_name  = table_name; }

QString QDBSettings::getHost()         const { return host;       }
QString QDBSettings::getDataBaseName() const { return dbname;     }
QString QDBSettings::getTableName()    const { return table_name; }
