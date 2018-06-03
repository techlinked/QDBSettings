#ifndef QDBSETTINGS_H
#define QDBSETTINGS_H

#include <QtSql>

class QDBSettings
{
public:
    QDBSettings();
    QDBSettings(const QString& host,
                const QString& dbname,
                const QString& username,
                const QString& pass,
                const QString& table_name);
    ~QDBSettings();

    bool connect();
    QPair<bool, QString> isConnect();
    bool disconnect();
    qint64 getIntegerValue( const QString& name);
    QString getTextValue(   const QString& name);
    bool saveIntegerValue(  const QString& name, const qint64 value);
    bool saveTextValue(     const QString& name, const QString& value);

    // TODO: add setter and getter for float param
    // TODO: add setter and getter for double param
    // TODO: add setter and getter for other type params

    QHash<QString, QVariant> getAllSettings();
    bool resetSettings();

    void setHost(           const QString& host);
    void setDataBaseName(   const QString& dbname);
    void setUserName(       const QString& username);
    void setPassword(       const QString& password);
    void setTableName(      const QString& table_name);
    void setSettingsID(     const QString& settings_id);

    QString getHost()       const;
    QString getDataBaseName() const;
    QString getUserName()   const;
    QString getTableName()  const;
    QString getSettingsID() const;

private:
    QSqlDatabase* database;
    QSqlQuery* query;

    QHash<QString, QVariant> allparams;

    QString host;
    QString table_name;
    QString dbname;
    QString username;
    QString password;
    QString settings_id;
};

#endif // QDBSETTINGS_H
