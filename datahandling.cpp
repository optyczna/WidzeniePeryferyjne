#include "datahandling.h"
#include <QDebug>
#include <QDate>

QString DataHandling::name() const
{
    return _name;
}

void DataHandling::setName(const QString &name)
{
    _name = name;
}

bool DataHandling::checkIfExists(QString name)
{
    read();
     if(std::find_if(_patients.begin(), _patients.end(), [&name](QString el){return el.toLower()==name.toLower();})!=_patients.end())
         return true;
     return false;
}

DataHandling::DataHandling()
{
    _local_url = QDir::currentPath();
    _local_url.append("/data.json");
    _file.setFileName(_local_url);
    if(_file.open(QIODevice::ReadOnly)){
        _value_json = _file.readAll();
        _file.close();
    } else {
        qDebug() << "Reading error";
    }
    QJsonDocument jsonResponse = QJsonDocument::fromJson(_value_json.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["patients"].toArray();

    foreach(const QJsonValue &value, jsonArray){
        QJsonObject obj = value.toObject();
        _patients.append(obj["name"].toString());
    }
}

void DataHandling::read()
{
    _file.setFileName(_local_url);
    if(_file.open(QIODevice::ReadOnly)){
        _value_json = _file.readAll();
        _file.close();
    } else {
        qDebug() << "Reading error";
    }
    QJsonDocument jsonResponse = QJsonDocument::fromJson(_value_json.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["patients"].toArray();

    foreach(const QJsonValue &value, jsonArray){
        QJsonObject obj = value.toObject();
       // qDebug() << obj["name"].toString();
    }
}

void DataHandling::write()
{
    QJsonArray patients_array;
    for(int i = 0; i<_patients.size(); ++i){
        QJsonObject patient;
        patient["name"] = _patients.at(i);
        patients_array.append(patient);
    }
    QJsonObject patient;
    if(!_name.isEmpty()){
        patient["name"] = _name;
        patients_array.append(patient);
    }

    QJsonObject _final_json;
    _final_json.insert("patients", patients_array);

    QString json_msg = QJsonDocument(_final_json).toJson(QJsonDocument::Compact);

    QFile _file_name(_local_url);
    if(_file_name.open(QIODevice::ReadWrite)){
        QTextStream stream(&_file_name);
        stream << json_msg << endl;
        _file.close();
    }    
}
