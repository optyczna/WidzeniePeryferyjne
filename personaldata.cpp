#include "personaldata.h"
#include <QDebug>

PersonalData::PersonalData()
{
}

void PersonalData::readData()
{
    QString data;
    _local_url = QCoreApplication::applicationDirPath();
    _local_url.append("/");
    _local_url.append(_name.toLower());
    _local_url.append(".json");
    if(QFile::exists(_local_url)){
        QFile file;
        qDebug() << "exists: f.read " <<_local_url;
        file.setFileName(_local_url);
        file.open(QIODevice::ReadOnly);
        data = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject jsonObj = jsonDoc.object();
        _missed_l_ctr = jsonObj["missed_l_ctr"].toInt();
        _missed_r_ctr = jsonObj["missed_r_ctr"].toInt();
        _good_l_ctr = jsonObj["good_l_ctr"].toInt();
        _good_r_ctr = jsonObj["good_r_ctr"].toInt();
        _exercise_ctr = jsonObj["exercise_ctr"].toInt();
        _exercise_ctr_L = jsonObj["exercise_ctr_L"].toInt();
        _exercise_ctr_R = jsonObj["exercise_ctr_R"].toInt();
        _prev_font_size_R = jsonObj["prev_font_R"].toInt();
        _prev_font_size_L = jsonObj["prev_font_L"].toInt();
        _visual_field_R_L = jsonObj["visual_field_R_L"].toInt();
        _visual_field_R = jsonObj["visual_field_R"].toInt();
        _visual_filed_L = jsonObj["visual_field_L"].toInt();
//        _prev_peripheral_font_size_R = jsonObj["prev_peri_font_R"].toInt();
//        _prev_peripheral_font_size_L = jsonObj["prev_peri_font_L"].toInt();
        qDebug() << "Prev R " << _prev_font_size_R << "Prev L " << _prev_font_size_L;
    }
    else{
        QFile file;
        file.setFileName(_local_url);
        qDebug() << "doesn't exist f.read" <<_local_url;
        file.open(QIODevice::ReadWrite);
        file.close();
        _missed_l_ctr = 0;
        _missed_r_ctr = 0;
        _good_l_ctr = 0;
        _good_r_ctr = 0;
        _exercise_ctr = 0;
        _exercise_ctr_R = 0;
        _exercise_ctr_L = 0;
        _prev_font_size_R = 40;
        _prev_font_size_L = 40;
        _visual_field_R = 0;
        _visual_field_R_L = 0;
        _visual_filed_L = 0;
//        _prev_peripheral_font_size_R = 40;
//        _prev_peripheral_font_size_L = 40;
    }
}

void PersonalData::writeData()
{
    QJsonObject jsonObj;
    jsonObj["name"] = _name;
    jsonObj["missed_l_ctr"] = _missed_l_ctr;
    jsonObj["missed_r_ctr"] = _missed_r_ctr;
    jsonObj["good_l_ctr"] = _good_l_ctr;
    jsonObj["good_r_ctr"] = _good_r_ctr;
    jsonObj["exercise_ctr"] = _exercise_ctr;
    jsonObj["exercise_ctr_L"] = _exercise_ctr_L;
    jsonObj["exercise_ctr_R"] = _exercise_ctr_R;
    jsonObj["prev_font_R"] = _prev_font_size_R;
    jsonObj["prev_font_L"] = _prev_font_size_L;
    jsonObj["visual_field_R_L"] = _visual_field_R_L;
    jsonObj["visual_field_R"] = _visual_field_R;
    jsonObj["visual_field_L"] = _visual_filed_L;
    jsonObj["prev_peri_font_R"] = _prev_peripheral_font_size_R;
    jsonObj["prev_peri_font_L"] = _prev_peripheral_font_size_L;

    QString msg = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
    QFile file;
    file.setFileName(_local_url);
    qDebug() << "f.write " << _local_url;
    if(file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << msg << endl;
        file.close();
    }
}

void PersonalData::setValuesR(int good, int bad)
{
    _missed_r_ctr += bad;
    _good_r_ctr += good;
}

void PersonalData::setValuesL(int good, int bad)
{
    _missed_l_ctr += bad;
    _good_l_ctr += good;
}

void PersonalData::setFontValuesR(int font_size, int peripheral_font_size)
{
    _prev_font_size_R = font_size;
    _prev_peripheral_font_size_R = peripheral_font_size;
}

void PersonalData::setFontValuesL(int font_size, int peripheral_font_size)
{
    _prev_font_size_L = font_size;
    _prev_peripheral_font_size_L = peripheral_font_size;
}

void PersonalData::setName(QString name)
{
    _name = name;
}

void PersonalData::setExerciseCtr()
{
    _exercise_ctr += 1;
}

void PersonalData::setExerciseCtrR()
{
    _exercise_ctr_R += 1;
}

void PersonalData::setExerciseCtrL()
{
    _exercise_ctr_L += 1;
}

void PersonalData::setVisualFieldRL(int field)
{
    _visual_field_R_L+=field;
}

void PersonalData::setVisualFieldR(int field)
{
    _visual_field_R +=field;
}

void PersonalData::setVisualFieldL(int field)
{
    _visual_filed_L += field;
}

int PersonalData::getFontSizeR()
{
    return _prev_font_size_R;
}

int PersonalData::getFontSizeL()
{
    return _prev_font_size_L;
}

int PersonalData::getPerFontSizeR()
{
    return _prev_peripheral_font_size_R;
}

int PersonalData::getPerFontSizeL()
{
    return  _prev_peripheral_font_size_L;
}

int PersonalData::getMissedR()
{
    return _missed_r_ctr;
}

int PersonalData::getMissedL()
{
    return  _missed_l_ctr;
}

int PersonalData::getGoodR()
{
    return _good_r_ctr;
}

int PersonalData::getGoodL()
{
    return _good_l_ctr;
}

int PersonalData::getExCtr()
{
    return _exercise_ctr;
}

int PersonalData::getVisualFieldRL()
{
    return _visual_field_R_L/_exercise_ctr;
}

int PersonalData::getVisualFieldR()
{
    return _visual_field_R;
}

int PersonalData::getVisualFieldL()
{
    return _visual_filed_L;
}
