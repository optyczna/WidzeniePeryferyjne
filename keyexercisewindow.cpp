#include "keyexercisewindow.h"
#include "ui_keyexercisewindow.h"

#include <QDebug>
KeyExerciseWindow::KeyExerciseWindow(QWidget *parent, bool l_u, bool r_u, bool l_b, bool r_b,
                                     double central_vision_field_ex, bool r_e, bool l_e,
                                     int prev_font_size_R, int prev_font_size_L,
                                     int prev_peripheral_size_R, int prev_peripheral_size_L,
                                     bool smaller_R, bool smaller_L, int ctr) :
    QDialog(parent),
    ui(new Ui::KeyExerciseWindow)
{
    ui->setupUi(this);
    this->setGeometry(QDesktopWidget().availableGeometry(this));
    _clicks_ctr = 0;
    _missed_ctr = 0;
    _dot_ctr = 0;
    _right_eye = r_e;
    _left_eye = l_e;
    _font_size = prev_font_size_R;
    _peripheral_font_size = prev_peripheral_size_R;

    setFontSizeR(smaller_R, prev_font_size_R);
    setFontSizeL(smaller_L, prev_font_size_L);
    setPeripheralFontSizeR(smaller_R, prev_peripheral_size_R);
    setPeripheralFontSizeL(smaller_L, prev_peripheral_size_L);

    _letters_1 << "F" << "J";
    _letters_2 << "D" << "F" << "J" << "K";
    _letters_3 << "S" << "D" << "F" << "J" << "K" << "L";
    _letters << "F" << "J";

    _px_central_vis_field = static_cast<int>(central_vision_field_ex/2);
            qDebug() << "KeyEx _prev_peri R: " << prev_peripheral_size_R << "_prev_l" << prev_peripheral_size_L;

    if(smaller_R == true || smaller_L == true){
        if(ctr<=5){
            _letters = _letters_1;
        }
        else if(ctr>5 && ctr <= 15){
            _letters = _letters_2;
        }
        else if(ctr>15){
            _letters = _letters_3;
        }
    }

    _timer = new QTimer();
    _timer->setInterval(3000);

    x_pos = QDesktopWidget().availableGeometry(this).width()-100;
    y_pos = QDesktopWidget().availableGeometry(this).height()-100;

    per_x_l = x_pos/2 - _px_central_vis_field;
    per_y_u = y_pos/2 - _px_central_vis_field;
    per_x_r = x_pos/2 + _px_central_vis_field;
    per_y_b = y_pos/2 + _px_central_vis_field;

    _dot_button = new QPushButton(this);
    _dot_button->move(x_pos/2, y_pos/2);
    _dot_button->setStyleSheet(
                "background-color: black;"
                "border-radius:15px;"
                "width:30px;"
                "height:30px;");

    _dot_button->setShortcut(QKeySequence(Qt::Key_Space));

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

    _key_button = new QPushButton(this);
    _key_button->move(x_pos/2, y_pos/2);
    _key_button->setStyleSheet(
        "border: none;"
        "font: bold;");

    _font_size = _font_size_R;
    _peripheral_font_size= _peripheral_font_size_R;
            qDebug() << "Key ex perif size" << _peripheral_font_size;
    if(_right_eye == false){
        _font_size = _font_size_L;
        _peripheral_font_size = _peripheral_font_size_L;
        qDebug() << "Key ex perif size" << _peripheral_font_size;
    }

    _animation = new QPropertyAnimation(_key_button, "pos");
    _animation->setDuration(0);

    _message_box = new QMessageBox;

    connect(_key_button, &QPushButton::clicked, this, &KeyExerciseWindow::randomAnimation);
    connect(_dot_button, &QPushButton::clicked, this, &KeyExerciseWindow::randomAnimation);
    connect(_key_button, &QPushButton::clicked, this, &KeyExerciseWindow::clickedCounter);
    connect(_dot_button, &QPushButton::clicked, this, &KeyExerciseWindow::dotCounter);
    connect(_timer, &QTimer::timeout, this, &KeyExerciseWindow::missedCounter);
    connect(_timer, &QTimer::timeout, this, &KeyExerciseWindow::randomAnimation);
}

KeyExerciseWindow::~KeyExerciseWindow()
{
    delete ui;
    delete _timer;
    delete _animation;
}

void KeyExerciseWindow::randomAnimation()
{
    srand(static_cast<uint>(QTime::currentTime().second()));
    std::random_shuffle(_letters.begin(), _letters.end());
    QString letter = _letters.front();
    _key_button->setText(letter);
    if(letter == "S"){
        _key_button->setShortcut(QKeySequence(Qt::Key_S));
    }
    else if(letter== "D"){
        _key_button->setShortcut(QKeySequence(Qt::Key_D));
    }
    else if(letter== "F"){
        _key_button->setShortcut(QKeySequence(Qt::Key_F));
    }
    else if(letter == "J"){
        _key_button->setShortcut(QKeySequence(Qt::Key_J));
    }
    else if(letter == "K"){
        _key_button->setShortcut(QKeySequence(Qt::Key_K));
    }
    else if(letter == "L"){
        _key_button->setShortcut(QKeySequence(Qt::Key_L));
    }

    int x = 1+(rand()%(QDesktopWidget().availableGeometry(this).width()-100));
    int y = 1+(rand()%(QDesktopWidget().availableGeometry(this).height()-100));

    if(x<per_x_l || x>per_x_r || y<per_y_u || y>per_y_b){
        QFont _font("Arial", _peripheral_font_size);
        _key_button->setFont(_font);
        _key_button->resize(_peripheral_font_size+15,_peripheral_font_size+15);
        qDebug() << "x: " << x << "per_x_r: " << per_x_r << "per_x_l: " << per_x_l;
                qDebug() << "y: " << y << "per_y_u" << per_y_u << "per_y_b" << per_y_b;
        qDebug() << "Peripheral font " << _peripheral_font_size;
    } else
    {
        QFont _font("Arial", _font_size);
        _key_button->setFont(_font);
        _key_button->resize(_font_size+15,_font_size+15);
                qDebug() << "Central font " << _font_size;
    }

    if((_clicks_ctr+_dot_ctr+_missed_ctr)==30){
        messageBox();
    }
    _timer->start();
    _animation->setEndValue(QPoint(x,y));
    _animation->start();
}

void KeyExerciseWindow::setFontSizeR(bool _smaller, int _prev_size)
{
    if(_smaller && (_prev_size>=15)){
        _font_size_R = _prev_size-3;
    }
    else{
        _font_size_R = _prev_size;
    }
}

void KeyExerciseWindow::setPeripheralFontSizeR(bool _smaller, int _prev_size)
{
    if(_smaller && (_prev_size>=40)){
        _peripheral_font_size_R = _prev_size-3;
    }
    if(!_smaller){
        _peripheral_font_size_R =_prev_size;
    }
    qDebug() << "set ex" << _peripheral_font_size << "set ex R: " << _peripheral_font_size_R;
}
void KeyExerciseWindow::setFontSizeL(bool _smaller, int _prev_size)
{
    if(_smaller && (_prev_size>=15)){
        _font_size_L = _prev_size-3;
    }
    else{
        _font_size_L = _prev_size;
    }
}

void KeyExerciseWindow::setPeripheralFontSizeL(bool _smaller, int _prev_size)
{
    if(_smaller && (_prev_size>=40)){
        _peripheral_font_size_L = _prev_size-3;
    }
    if(!_smaller){
        _peripheral_font_size_L =_prev_size;
    }
    qDebug() << "set ex" << _peripheral_font_size << "set ex R: " << _peripheral_font_size_R;
}

void KeyExerciseWindow::missedCounter()
{
    ++_missed_ctr;
    if(_missed_ctr%10==0){
        if(_font_size<=80 ){
            _font_size+=5;
            _peripheral_font_size+=10;
        }
    }
}

void KeyExerciseWindow::clickedCounter()
{
    ++_clicks_ctr;
    if(_clicks_ctr%15==0 && _font_size>=15){
        _font_size -=3;
        if(_peripheral_font_size>=40){
            _peripheral_font_size -=3;
        }
    }
    else if (_font_size<=10){
        messageBox();
    }
}

void KeyExerciseWindow::dotCounter()
{
    ++_dot_ctr;
    if(_dot_ctr%10==0){
        if(_font_size<=80){
            _font_size+=5;
            _peripheral_font_size+=10;
        }
    }
}

void KeyExerciseWindow::messageBox()
{
    _message_box->setStandardButtons(QMessageBox::Ok);
    if((_right_eye&&!_left_eye)){
        _animation->stop();
        _animation->destroyed();
        _timer->stop();
        _timer->destroyed();
        emit clicks_r(_clicks_ctr, _missed_ctr+_dot_ctr);
        emit font_size_R(_font_size, _peripheral_font_size);
        QString text;
        text.append("For now we are done. Gerat job!\n\nGood clicks: ");
        text.append(QString::number(_clicks_ctr));
        text.append("\nMissed clicks: ");
        text.append(QString::number(_missed_ctr));
        text.append("\nDot clicked: ");
        text.append(QString::number(_dot_ctr));
        text.append( "times.");
        _message_box->setText(text);
        if(_message_box->exec()==QMessageBox::Ok){
            _message_box->close();
            emit exercise_ended();
            this->close();
        }
    }
    else if((!_right_eye&&_left_eye)){
        _animation->stop();
        _animation->destroyed();
        _timer->stop();
        _timer->destroyed();
        emit clicks_l(_clicks_ctr, _missed_ctr+_dot_ctr);
        emit font_size_L(_font_size, _peripheral_font_size);
        QString text;
        text.append("For now we are done. Gerat job!\n\nGood clicks: ");
        text.append(QString::number(_clicks_ctr));
        text.append("\nMissed clicks: ");
        text.append(QString::number(_missed_ctr));
        text.append("\nDot clicked: ");
        text.append(QString::number(_dot_ctr));
        text.append( "times.");
        _message_box->setText(text);
        if(_message_box->exec()==QMessageBox::Ok){
            _message_box->close();
            emit exercise_ended();
            this->close();
        }
    }
    else if(_right_eye&&_left_eye){
        _animation->stop();
        _timer->stop();
        emit clicks_r(_clicks_ctr, _missed_ctr+_dot_ctr);
        emit font_size_R(_font_size, _peripheral_font_size);
        QString text;
        text.append("Good clicks: ");
        text.append(QString::number(_clicks_ctr));
        text.append("\nMissed clicks: ");
        text.append(QString::number(_missed_ctr));
        text.append("\nDot clicked: ");
        text.append(QString::number(_dot_ctr));
        text.append(" times.\n\nNow cover you right eye");
        _message_box->setText(text);
        _font_size = _font_size_L;
        _peripheral_font_size = _peripheral_font_size_L;
        _clicks_ctr = 0;
        _dot_ctr = 0;
        _missed_ctr = 0;
        _left_eye = false;
        _right_eye = false;

        if(_message_box->exec()==QMessageBox::Ok){
            _message_box->close();
            randomAnimation();
        }
    }
    else if (!_right_eye&&!_left_eye) {
        _animation->stop();
        _timer->stop();
        _timer->destroyed();
        _animation->destroyed();
        emit clicks_l(_clicks_ctr, _missed_ctr+_dot_ctr);
        emit font_size_L(_font_size, _peripheral_font_size);

        QString text;
        text.append("For now we are done. Gerat job!\n\nGood clicks: ");
        text.append(QString::number(_clicks_ctr));
        text.append("\nMissed clicks: ");
        text.append(QString::number(_missed_ctr));
        text.append("\nDot clicked: ");
        text.append(QString::number(_dot_ctr));
        text.append( " times.");
        _message_box->setText(text);
        if(_message_box->exec()==QMessageBox::Ok){
            _message_box->close();
            emit exercise_ended();
            this->close();
        }
    }
}
