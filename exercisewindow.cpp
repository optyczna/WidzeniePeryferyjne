#include "exercisewindow.h"
#include "ui_exercisewindow.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QtMath>
#include <QScreen>
#include <QTimer>

ExerciseWindow::ExerciseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExerciseWindow)
{
    ui->setupUi(this);
}

ExerciseWindow::ExerciseWindow(QWidget *parent, bool l_u, bool r_u, bool l_b, bool r_b,
                               double central_vision_field_px, bool r_e, bool l_e,
                               int prev_font_size_R, int prev_font_size_L,
                               int prev_peripheral_size_R, int prev_peripheral_size_L,
                               bool smaller_R, bool smaller_L) :
    QDialog(parent), ui(new Ui::ExerciseWindow)
{
    ui->setupUi(this);
    this->setGeometry(QDesktopWidget().availableGeometry(this));
    QApplication::setOverrideCursor(Qt::CrossCursor);

    x_pos = (QDesktopWidget().availableGeometry(this).width()-100);
    y_pos = (QDesktopWidget().availableGeometry(this).height()-100);
    _dot_ctr = 0;
    _button_ctr = 0;
    _missed_ctr = 0;
    _r_e = r_e;
    _l_e = l_e;
    _font_size = (prev_font_size_R+prev_font_size_L)/2;
    _peripheral_font_size = (prev_peripheral_size_R+prev_peripheral_size_L)/2;
    qDebug() << "Ex font size: " << _font_size << "Pripheral: " << _peripheral_font_size;
    setFontSizeR(smaller_R, prev_font_size_R);
    setFontSizeL(smaller_L, prev_font_size_L);
    setPeripheralFontSizeR(smaller_R, prev_peripheral_size_R);
    setPeripheralFontSizeL(smaller_L, prev_peripheral_size_L);

    _button = new QPushButton(this);
    _button->move(x_pos/2, y_pos/2);
    _button->setStyleSheet(
        "border: none;"
        "font: bold;");

    _font_size = _font_size_R;
    _peripheral_font_size = _peripheral_font_size_R;

    if(_r_e == false){
        _font_size = _font_size_L;
        _peripheral_font_size = _peripheral_font_size_L;
    }
    //qDebug() << "Exercise WIndow constructor" << _font_size << "R: " << _font_size_R << "L" <<_font_size_L;
//    QFont font("Arial", _font_size);
//    _button->setFont(font);
//    _button->resize(_font_size+15,_font_size+15);

    _dot_button = new QPushButton(this);
    _dot_button->move(x_pos/2, y_pos/2);
    _dot_button->setStyleSheet(
                "background-color: black;"
                "border-radius:15px;"
                "width:30px;"
                "height:30px;");

    _animation = new QPropertyAnimation(_button, "pos");
    _animation->setDuration(0);

    //QScreen *screen = qApp->screens().at(0);
    //_width_of_central_vision_field_in_px = qDegreesToRadians(2.5)*distance*2*screen->physicalDotsPerInch()/25.4;
  //  qDebug() << "Width of central 5 degrees" << _width_of_central_vision_field_in_px;
    _px_central_vis_field = static_cast<int>(central_vision_field_px/2);
//            qDebug() << "KeyEx _prev_peri R: " << prev_peripheral_size_R << "_prev_l" << prev_peripheral_size_L;

    per_x_l = x_pos/2 - _px_central_vis_field;
    per_y_u = y_pos/2 - _px_central_vis_field;
    per_x_r = x_pos/2 + _px_central_vis_field;
    per_y_b = y_pos/2 + _px_central_vis_field;

    _timer = new QTimer;
    _timer->setInterval(3000);

    connect(_button, &QAbstractButton::clicked, this, &ExerciseWindow::randomAnimation);
    connect(_dot_button, &QAbstractButton::clicked, this, &ExerciseWindow::randomAnimation);
    connect(_button, &QAbstractButton::clicked, this, &ExerciseWindow::clickCounterButton);
    connect(_dot_button, &QAbstractButton::clicked, this, &ExerciseWindow::clickCounterDot);
    connect(this, &ExerciseWindow::infoToMessageBox, this, &ExerciseWindow::messageBox);
    connect(_timer, &QTimer::timeout, this, &ExerciseWindow::randomAnimation);
    connect(_timer, &QTimer::timeout, this, &ExerciseWindow::clickCounterMissed);

    if(l_u && !r_u && !l_b && !r_b){
        _dot_button->move(x_pos, y_pos);
        per_x_l = x_pos - _px_central_vis_field;
        per_y_u = y_pos - _px_central_vis_field;
        per_x_r = x_pos;
        per_y_b = y_pos;
    }
    else if(r_u && !l_u && !r_b && !l_b){
        _dot_button->move(20, y_pos);
        per_x_l = 0;
        per_y_u = y_pos - _px_central_vis_field;
        per_x_r = 0 + _px_central_vis_field;
        per_y_b = y_pos;
    }
    else if(r_b && !l_b && !r_u && !l_u){
        _dot_button->move(20, 20);
        per_x_l = 0;
        per_y_u = 0;
        per_x_r = 0 + _px_central_vis_field;
        per_y_b = 0 + _px_central_vis_field;
    }
    else if(l_b && !r_b && !l_u && !r_u){
        _dot_button->move(x_pos,20);
        per_x_l = x_pos - _px_central_vis_field;
        per_y_u = 0;
        per_x_r = x_pos;
        per_y_b = 0 + _px_central_vis_field;
    }
    else if(l_u && r_u && !l_b && !r_b){
        _dot_button->move(x_pos/2, y_pos);
        per_x_l = x_pos/2 - _px_central_vis_field;
        per_y_u = 0;
        per_x_r = x_pos/2 + _px_central_vis_field;
        per_y_b = 0 + _px_central_vis_field;
    }
    else if(l_b && r_b && !l_u && !r_u){
        _dot_button->move(x_pos/2, 20);
        per_x_l = x_pos/2 - _px_central_vis_field;
        per_y_u = y_pos - _px_central_vis_field;
        per_x_r = x_pos/2 + _px_central_vis_field;
        per_y_b = y_pos;
    }
    else if(l_u && l_b && !r_u && ! r_b){
        _dot_button->move(x_pos, y_pos/2);
        per_x_l = x_pos - _px_central_vis_field;
        per_y_u = y_pos/2 - _px_central_vis_field;
        per_x_r = x_pos;
        per_y_b = y_pos/2 + _px_central_vis_field;
    }
    else if(r_u && r_b && !l_u && !l_b){
        _dot_button->move(50, y_pos/2);
        per_x_l = 0;
        per_y_u = y_pos/2 - _px_central_vis_field;
        per_x_r = 0 + _px_central_vis_field;
        per_y_b = y_pos/2 + _px_central_vis_field;
    }
}

ExerciseWindow::~ExerciseWindow()
{
    QApplication::restoreOverrideCursor();
    delete _timer;
    delete _animation;
    delete ui;
}

void ExerciseWindow::randomAnimation()
{
    srand(static_cast<uint>(QTime::currentTime().second()));
    int letter = rand()%25+65;
    _button->setText(static_cast<QString>(letter));

    x = 1+(rand()%(QDesktopWidget().availableGeometry(this).width()-100));
    y = 1+(rand()%(QDesktopWidget().availableGeometry(this).height()-100));

//    if(_font_size<20){
//        x = 1+(rand()%(QDesktopWidget().availableGeometry(this).width()-100));
//        y = 1+(rand()%(QDesktopWidget().availableGeometry(this).height()-100));
//    }
//    else if(_font_size>20 && _font_size<=40){
//        x = 100+(rand()%(QDesktopWidget().availableGeometry(this).width()-200));
//        y = 100+(rand()%(QDesktopWidget().availableGeometry(this).height()-200));
//    }
//    else if(_font_size>40){
//        x = QDesktopWidget().availableGeometry(this).width()/4 + (rand()%(QDesktopWidget().availableGeometry(this).width()/2));
//        y = QDesktopWidget().availableGeometry(this).height()/4 + (rand()%(QDesktopWidget().availableGeometry(this).height()/2));
//    }

    if(x<per_x_l || x>per_x_r || y<per_y_u || y>per_y_b){
        QFont _font("Arial", _peripheral_font_size);
        _button->setFont(_font);
        _button->resize(_peripheral_font_size+15,_peripheral_font_size+15);
        qDebug() << "x: " << x << "per_x_r: " << per_x_r << "per_x_l: " << per_x_l;
                qDebug() << "y: " << y << "per_y_u" << per_y_u << "per_y_b" << per_y_b;
        qDebug() << "Peripheral font " << _peripheral_font_size;
    } else
    {
        QFont _font("Arial", _font_size);
        _button->setFont(_font);
        _button->resize(_font_size+15,_font_size+15);
                qDebug() << "Central font " << _font_size;
    }

    if((_button_ctr+_dot_ctr+_missed_ctr)==30){ //remember to change that value
        infoToMessageBox();
    }

    _timer->start();
    _animation->setEndValue(QPoint(x,y));
    _animation->start();
}

void ExerciseWindow::setFontSizeR(bool _smaller, int _prev_size)
{
    if(_smaller && (_prev_size>=15)){
        _font_size_R = _prev_size-3;
    }
    else{
        _font_size_R = _prev_size;
    }
    qDebug() << "Exercise Window font size R:" << _font_size_R << "prev size: " << _prev_size;
}

void ExerciseWindow::setPeripheralFontSizeR(bool _smaller, int _prev_size)
{
    if(_smaller && (_prev_size>=40)){
        _peripheral_font_size_R = _prev_size-3;
    }
    if(!_smaller){
        _peripheral_font_size_R =_prev_size;
    }
}

void ExerciseWindow::setFontSizeL(bool _smaller, int _prev_size)
{
    if(_smaller && (_prev_size>=15)){
        _font_size_L = _prev_size-3;
    }
    else{
        _font_size_L = _prev_size;
    }
     qDebug() << "Exercise Window font size L:" << _font_size_L << "prev size: " << _prev_size;
}

void ExerciseWindow::setPeripheralFontSizeL(bool _smaller, int _prev_size)
{
    if(_smaller && (_font_size>=40)){
        _peripheral_font_size_L = _prev_size-3;
    }
    if(!_smaller){
        _peripheral_font_size_L =_prev_size;
    }
}

void ExerciseWindow::clickCounterDot()
{
    ++_dot_ctr;
    if(_dot_ctr%10==0){
        if(_font_size<=80){
            _font_size+=5;
            _peripheral_font_size+=10;
        }
    }
}

void ExerciseWindow::clickCounterButton()
{
    ++_button_ctr;
    if(_button_ctr%15==0 && _font_size>=15){
        _font_size -=3;
        if(_peripheral_font_size>=40){
            _peripheral_font_size -=3;
        }
    }
    else if (_font_size<=10){
        infoToMessageBox();
    }
}

void ExerciseWindow::clickCounterMissed()
{
    ++_missed_ctr;
    if(_missed_ctr%10==0){
        if(_font_size<=80 ){
            _font_size+=5;
            _peripheral_font_size+=10;
        }
    }
}

void ExerciseWindow::messageBox()
{
    _alert_box = new QMessageBox;
    _alert_box->setStandardButtons(QMessageBox::Ok);

    if(_r_e&&!_l_e){
        _animation->stop();
        _timer->stop();
        emit clicks_r(_button_ctr, _missed_ctr+_dot_ctr);
        emit font_size_R(_font_size, _peripheral_font_size);
        emit exercise_ended();
                qDebug() << "Exercise Window emitted font size R:" << _font_size;
        QString text;
        text.append("For now we are done! Great job!\n\nGood clicks: ");
        text.append(QString::number(_button_ctr));
        text.append("\nMissed clicks: ");
        text.append(QString::number(_missed_ctr));
        text.append("\nDot clicked: ");
        text.append(QString::number(_dot_ctr));
        text.append(" times.");
        _alert_box->setText(text);
        if(_alert_box->exec()==QMessageBox::Ok){
            _alert_box->close();
            disconnect(_timer, &QTimer::timeout, this, &ExerciseWindow::clickCounterMissed);
            this->close();
        }
    }
    else if(!_r_e&&_l_e){
        _animation->stop();
        _timer->stop();
        QString text;
        emit clicks_l(_button_ctr, _missed_ctr+_dot_ctr);
        emit font_size_L(_font_size, _peripheral_font_size);
                qDebug() << "Exercise Window emitted font size L:" << _font_size;
        emit exercise_ended();
        text.append("For now we are done! Great job!\n\nGood clicks: ");
        text.append(QString::number(_button_ctr));
        text.append("\nMissed clicks: ");
        text.append(QString::number(_missed_ctr));
        text.append("\nDot clicked: ");
        text.append(QString::number(_dot_ctr));
        text.append(" times.");
        _alert_box->setText(text);
        if(_alert_box->exec()==QMessageBox::Ok){
            _alert_box->close();
            disconnect(_timer, &QTimer::timeout, this, &ExerciseWindow::clickCounterMissed);
            this->close();
        }
    }
    else if(_r_e&&_l_e){
        _animation->stop();
        _timer->stop();
        emit clicks_r(_button_ctr, _missed_ctr+_dot_ctr);
        emit font_size_R(_font_size, _peripheral_font_size);
        qDebug() << "Exercise Window emitted font size R:" << _font_size;
        QString text;
        text.append("Good clicks: ");
        text.append(QString::number(_button_ctr));
        text.append("\nMissed clicks: ");
        text.append(QString::number(_missed_ctr));
        text.append("\nDot clicked: ");
        text.append(QString::number(_dot_ctr));
        text.append(" times.\n\nNow cover you right eye");
        _alert_box->setText(text);
        _font_size = _font_size_L;
        _peripheral_font_size = _peripheral_font_size_L;
//        QFont font("Arial", _font_size);
//        _button->setFont(font);
//        _button->resize(_font_size+15, _font_size+15);
        _button_ctr = 0;
        _dot_ctr = 0;
        _missed_ctr = 0;
        _l_e = false;
        _r_e = false;

        if(_alert_box->exec()==QMessageBox::Ok){
            _alert_box->close();
        }
        randomAnimation();
    }
    else if (!_r_e&&!_l_e)
    {
        _animation->stop();
        _timer->stop();
        _timer->destroyed();
        emit clicks_l(_button_ctr, _missed_ctr+_dot_ctr);
        emit font_size_L(_font_size, _peripheral_font_size);

                qDebug() << "Exercise Window emitted font size L:" << _font_size;
        QString text;
        text.append("For now we are done! Great job!\n\nGood clicks: ");
        text.append(QString::number(_button_ctr));
        text.append("\nMissed clicks: ");
        text.append(QString::number(_missed_ctr));
        text.append("\nDot clicked: ");
        text.append(QString::number(_dot_ctr));
        text.append(" times.");
        _alert_box->setText(text);
        if(_alert_box->exec()==QMessageBox::Ok){
            _alert_box->close();
            emit exercise_ended();
            this->close();
        }
    }
}
