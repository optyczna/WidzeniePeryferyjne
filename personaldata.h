#ifndef PERSONALDATA_H
#define PERSONALDATA_H

#include <QObject>
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTextStream>

class PersonalData
{
    Q_GADGET
    QString _name;
    QString _local_url;
    int _missed_r_ctr;
    int _missed_l_ctr;
    int _good_r_ctr;
    int _good_l_ctr;
    int _exercise_ctr;
    int _exercise_ctr_R;
    int _exercise_ctr_L;
    int _prev_font_size_R;
    int _prev_font_size_L;
    int _visual_field_R_L;
    int _visual_field_R;
    int _visual_filed_L;
    int _prev_peripheral_font_size_R;
    int _prev_peripheral_font_size_L;

public:
    PersonalData();

public slots:
    void readData();
    void writeData();
    void setValuesR(int, int);
    void setValuesL(int, int);
    void setFontValuesR(int, int);
    void setFontValuesL(int, int);
    void setName(QString);
    void setExerciseCtr();
    void setExerciseCtrR();
    void setExerciseCtrL();
    void setVisualFieldRL(int);
    void setVisualFieldR(int);
    void setVisualFieldL(int);
    int getFontSizeR();
    int getFontSizeL();
    int getPerFontSizeR();
    int getPerFontSizeL();
    int getMissedR();
    int getMissedL();
    int getGoodR();
    int getGoodL();
    int getExCtr();
    int getVisualFieldRL();
    int getVisualFieldR();
    int getVisualFieldL();
};

#endif // PERSONALDATA_H
