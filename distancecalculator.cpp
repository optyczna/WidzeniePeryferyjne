#include "distancecalculator.h"
#include "ui_distancecalculator.h"
#include <QDebug>
#include <QtMath>
#include <QScreen>

DistanceCalculator::DistanceCalculator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DistanceCalculator)
{
    ui->setupUi(this);
    this->setGeometry(QDesktopWidget().availableGeometry(this));
    int x_pos = (QDesktopWidget().availableGeometry(this).width());
    int y_pos = (QDesktopWidget().availableGeometry(this).height());
  //  qDebug() << "Screen Width: "<< x_pos << "\nScreen height " << y_pos;
    _move_button = new QPushButton(this);
    _look_at_button = new QPushButton(this);
    _move_button->setStyleSheet(
                "background-color: black;"
                "border-radius:15px;"
                "width:30px;"
                "height:30px;");
    _move_button->move((x_pos/2-200), (y_pos/2-50));
    _look_at_button->setStyleSheet(
            "background-color: red;"
            "border-radius:15px;"
            "width:30px;"
            "height:30px;");
    _look_at_button->setShortcut(QKeySequence(Qt::Key_Space));
    _look_at_button->move((x_pos/2-200), (y_pos/2-50));
    _pos_animation = new QPropertyAnimation(_move_button, "pos");
    _pos_animation->setDuration(8000);

    connect(_move_button, &QAbstractButton::clicked, this, &DistanceCalculator::positionAnimation);
    connect(_look_at_button, &QAbstractButton::clicked, this, &DistanceCalculator::animationStopped);
}

DistanceCalculator::~DistanceCalculator()
{
    delete ui;
}

void DistanceCalculator::animationStopped()
{
    _pos_animation->stop();
    _info_box = new QMessageBox;
    QScreen *screen = qApp->screens().at(0); // for main screen, for second screen should be .at(1)
    //screen distance in cm
    double _screen_distance = (_move_button->x()-_look_at_button->x())*25/screen->physicalDotsPerInch()*19.5/4.76;

    //whole angle
    double _angle = 2*qRadiansToDegrees(qAtan2(((QDesktopWidget().availableGeometry(this).width()-100)*0.25)/2, _screen_distance ));

    //width in px for central vision field(10 deg)
    double _central_vis_field_px = qDegreesToRadians(5.0)*(_move_button->x()-_look_at_button->x())*19.5*2/4.76;
    qDebug() << "Central 10 degrees in px" << _central_vis_field_px;
    emit computations(_screen_distance, _angle, _central_vis_field_px);
}

void DistanceCalculator::positionAnimation()
{
    int x_pos2 = (QDesktopWidget().availableGeometry(this).width());
    int y_pos2 = (QDesktopWidget().availableGeometry(this).height());
   // qDebug() << "Screen Width2: "<< x_pos2 << "\nScreen height2 " << y_pos2;
     _move_button->move((x_pos2/2-200), (y_pos2/2-50));
     _look_at_button->move((x_pos2/2-200), (y_pos2/2-50));
    int x = x_pos2-50;
    int y = (y_pos2/2)-50;
    _pos_animation->setEndValue(QPoint(x,y));
    _pos_animation->start();
}
