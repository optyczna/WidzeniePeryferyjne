#ifndef DATAHANDLING_H
#define DATAHANDLING_H

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QFile>
#include <QIODevice>
#include <QJsonArray>
#include <QDir>

class DataHandling
{
    Q_GADGET

    QString _name;
    QStringList _patients;
    QString _value_json;
    QFile _file;
    QString _local_url;

public:
    DataHandling();

    void read();
    void write();
    QString name() const;
    void setName(const QString &name);
    bool checkIfExists(QString name);

};

#endif // DATAHANDLING_H
