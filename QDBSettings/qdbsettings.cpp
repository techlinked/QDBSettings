#include "qdbsettings.h"

QDBSettings::QDBSettings()
{
    database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase("QPSQL");
    query = new QSqlQuery();
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
    this->settings_id = "1";
}

QDBSettings::~QDBSettings()
{
    this->disconnect();
    delete query;
    delete database;
}

bool QDBSettings::connect()
{
    database->setHostName(host);
    database->setDatabaseName(dbname);
    database->setUserName(username);
    database->setPassword(password);
    if(!database->open())
    {
        qDebug() << "Unable to connect database: [" << dbname << "] ["
                 << host << "] [" << username << "]";
        return false;
    }
    return true;
}

QPair<bool, QString> QDBSettings::isConnect()
{
    QPair<bool, QString> res(false, "");
    if(database->isOpen())
    {
        res.first = true;
        res.second = database->databaseName();
        return res;
    }
    qDebug() << "No database connection";
    return res;
}

bool QDBSettings::disconnect()
{
    database->setConnectOptions();
    database->close();
    database->removeDatabase(dbname);
    return database->isValid() ? false : true;
}

qint64 QDBSettings::getIntegerValue(const QString &name)
{
    int result = 0;
    QString response =  "SELECT " + name + " FROM " + table_name +
                        " WHERE settings_id = " + settings_id;
    query->setForwardOnly(true);
    result = query->exec(response);
    if(!result)
    {
        qDebug() << " Get integer value response failed: [" << name << "]";
        qDebug() << "Response: [" << response << "]";
        return 0;
    }
    query->next();
    return query->value(0).toInt();
}

QString QDBSettings::getTextValue(const QString &name)
{
    QString response =  "SELECT " + name + " FROM " + table_name +
                        " WHERE settings_id = " + settings_id;
    int result = query->exec(response);
    if(!result)
    {
        qDebug() << "Get text value response failed: [" << name << "]";
        qDebug() << "Response: [" << response << "]";
        return 0;
    }
    query->next();
    return query->value(0).toString();
}

bool QDBSettings::saveIntegerValue(const QString &name, const qint64 value)
{
    database->transaction();
    QString response =  "UPDATE " + table_name + " SET " + name + " = " +
                        QString::number(value) + " WHERE settings_id = " + settings_id;
    int result = query->exec(response);
    if(!result)
    {
        qDebug() << "Save integer value failed: [" << name << "] [" << value << "]";
        qDebug() << "Response: [" << response << "]";
        return false;
    }
    database->commit();
    return true;
}

bool QDBSettings::saveTextValue(const QString &name, const QString &value)
{
    database->transaction();
    QString response =  "UPDATE " + table_name +
                        " SET " + name + " = '" + value +
                        "' WHERE  settings_id = " + settings_id;
    int result = query->exec(response);
    if(!result)
    {
        qDebug() << "Save text value failed: [" << name << "] [" << value << "]";
        qDebug() << "Response: [" << response << "]";
        return false;
    }
    database->commit();
    return true;
}

QHash<QString, QVariant> QDBSettings::getAllSettings()
{
    QHash<QString, QVariant> params;
    QString response =  "SELECT * FROM " + table_name +
                        " WHERE settings_id = " + settings_id;
    int result = query->exec(response);
    QSqlRecord rec = query->record();

    if(!result)
    {
        qDebug() << "Get all settings failed";
        qDebug() << "Response: [" << response << "]";
    }

    while(query->next())
    {
        for(int i = 0; i < rec.count(); ++i)
        {
            params.insert(rec.fieldName(i), query->value(i));
        }
    }
    return params;
}

void QDBSettings::setHost         (const QString &host)       { this->host        = host;       }
void QDBSettings::setDataBaseName (const QString &dbname)     { this->dbname      = dbname;     }
void QDBSettings::setUserName     (const QString &username)   { this->username    = username;   }
void QDBSettings::setPassword     (const QString &password)   { this->password    = password;   }
void QDBSettings::setTableName    (const QString &table_name) { this->table_name  = table_name; }
void QDBSettings::setSettingsID   (const QString &settings_id){ this->settings_id = settings_id;}

QString QDBSettings::getHost()         const { return host;       }
QString QDBSettings::getDataBaseName() const { return dbname;     }
QString QDBSettings::getUserName()     const { return username;   }
QString QDBSettings::getTableName()    const { return table_name; }
QString QDBSettings::getSettingsID()   const { return settings_id;}
