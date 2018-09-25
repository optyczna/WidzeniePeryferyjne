#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDebug>
#include <QScreen>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    _data = new DataHandling();
    _personal_data = new PersonalData();
    //QScreen *screen = qApp->screens().at(0);
   // qDebug() << screen->geometry() << screen->physicalSize() << screen->physicalDotsPerInch();
    _calculator = new DistanceCalculator;
    _main_layout = new QVBoxLayout;
    _ex_group_box = new QGroupBox;
    _quadrant_group_box = new QGroupBox;
    _eye_group_box = new QGroupBox;
    _method_group_box = new QGroupBox;
    name();
    exercises();
    quadrant();
    eye();
    methods();

    connect(_after_stroke_check_box, &QCheckBox::stateChanged, _left_bot_box, &QCheckBox::setEnabled);
    connect(_after_stroke_check_box, &QCheckBox::stateChanged, _left_up_box, &QCheckBox::setEnabled);
    connect(_after_stroke_check_box, &QCheckBox::stateChanged, _right_bot_box, &QCheckBox::setEnabled);
    connect(_after_stroke_check_box, &QCheckBox::stateChanged, _right_up_box, &QCheckBox::setEnabled);
    connect(_other_check_box, &QCheckBox::stateChanged, _left_bot_box, &QCheckBox::setEnabled);
    connect(_other_check_box, &QCheckBox::stateChanged, _left_up_box, &QCheckBox::setEnabled);
    connect(_other_check_box, &QCheckBox::stateChanged, _right_bot_box, &QCheckBox::setEnabled);
    connect(_other_check_box, &QCheckBox::stateChanged, _right_up_box, &QCheckBox::setEnabled);
    connect(_after_stroke_check_box, &QCheckBox::stateChanged, _other_check_box, &QCheckBox::setDisabled);
    connect(_after_stroke_check_box, &QCheckBox::stateChanged, _just_ex_check_box, &QCheckBox::setDisabled);
    connect(_other_check_box, &QCheckBox::stateChanged, _after_stroke_check_box, &QCheckBox::setDisabled);
    connect(_other_check_box, &QCheckBox::stateChanged, _just_ex_check_box, &QCheckBox::setDisabled);
    connect(_just_ex_check_box, &QCheckBox::stateChanged, _other_check_box, &QCheckBox::setDisabled);
    connect(_just_ex_check_box, &QCheckBox::stateChanged, _after_stroke_check_box, &QCheckBox::setDisabled);
    connect(_just_ex_check_box, &QCheckBox::stateChanged, _all_box, &QCheckBox::setChecked);
    connect(_touch_screen_box, &QCheckBox::stateChanged, _touch_pad_box, &QCheckBox::setDisabled);
    connect(_touch_screen_box, &QCheckBox::stateChanged, _keybord_check_box, &QCheckBox::setDisabled);
    connect(_touch_screen_box, &QCheckBox::stateChanged, _mouse_check_box, &QCheckBox::setDisabled);
    connect(_touch_pad_box, &QCheckBox::stateChanged, _keybord_check_box, &QCheckBox::setDisabled);
    connect(_touch_pad_box, &QCheckBox::stateChanged, _mouse_check_box, &QCheckBox::setDisabled);
    connect(_touch_pad_box, &QCheckBox::stateChanged, _touch_screen_box, &QCheckBox::setDisabled);
    connect(_mouse_check_box, &QCheckBox::stateChanged, _touch_pad_box, &QCheckBox::setDisabled);
    connect(_mouse_check_box, &QCheckBox::stateChanged, _keybord_check_box, &QCheckBox::setDisabled);
    connect(_mouse_check_box, &QCheckBox::stateChanged, _touch_screen_box, &QCheckBox::setDisabled);
    connect(_keybord_check_box, &QCheckBox::stateChanged, _touch_pad_box, &QCheckBox::setDisabled);
    connect(_keybord_check_box, &QCheckBox::stateChanged, _mouse_check_box, &QCheckBox::setDisabled);
    connect(_keybord_check_box, &QCheckBox::stateChanged, _touch_screen_box, &QCheckBox::setDisabled);

    _dialog_button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(_dialog_button_box, &QDialogButtonBox::accepted, this, &MainDialog::checkInitialValues);
    connect(_dialog_button_box, &QDialogButtonBox::rejected, this, &MainDialog::close);
    connect(_calculator, &DistanceCalculator::computations, this, &MainDialog::excercise);
    connect(_statistics_button, &QPushButton::clicked, this, &MainDialog::statistics);
    _main_layout->addLayout(_name_box);
    _main_layout->addWidget(_ex_group_box);
    _main_layout->addWidget(_quadrant_group_box);
    _main_layout->addWidget(_eye_group_box);
    _main_layout->addWidget(_method_group_box);
    _main_layout->addWidget(_dialog_button_box);


    setLayout(_main_layout);
    setWindowTitle("Visual Field Expander");
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::quadrant()
{
    _quadrant_grid_box = new QGridLayout;
    _quadrant_label = new QLabel("Which quadrant would you like to expand?");
    _left_up_box = new QCheckBox("Left-Upper Quadrant");
    _left_bot_box = new QCheckBox("Left-Bottom Quadrant");
    _right_up_box = new QCheckBox("Right-Upper Quadrant");
    _right_bot_box = new QCheckBox("Right-Bottom Quadrant");
    _all_box = new QCheckBox("Whole Vision Field");
    _quadrant_grid_box->addWidget(_quadrant_label, 0, 0, 1, 2);
    _quadrant_grid_box->addWidget(_left_up_box, 1, 0);
    _quadrant_grid_box->addWidget(_right_up_box, 1, 1);
    _quadrant_grid_box->addWidget(_left_bot_box, 2, 0);
    _quadrant_grid_box->addWidget(_right_bot_box, 2, 1);
    _quadrant_grid_box->addWidget(_all_box, 3 ,0);
    _left_up_box->setEnabled(false);
    _left_bot_box->setEnabled(false);
    _right_bot_box->setEnabled(false);
    _right_up_box->setEnabled(false);
    _quadrant_group_box->setLayout(_quadrant_grid_box);
}

void MainDialog::exercises()
{
    _ex_grid_layout = new QGridLayout;
    _ex_label = new QLabel("Why would you like to expand your vision field?");
    _after_stroke_check_box = new QCheckBox("Brain Damage after Stroke");
    _other_check_box = new QCheckBox("Other Brain Damage");
    _just_ex_check_box = new QCheckBox("Just want to exercise");
    _ex_grid_layout->addWidget(_ex_label, 0, 0, 1, 2);
    _ex_grid_layout->addWidget(_after_stroke_check_box, 1,0);
    _ex_grid_layout->addWidget(_other_check_box, 1,1);
    _ex_grid_layout->addWidget(_just_ex_check_box, 2, 0);
    _ex_group_box->setLayout(_ex_grid_layout);
}

void MainDialog::eye()
{
    _eye_grid_layout = new QGridLayout;
    _eye_label = new QLabel("Which eye would you like to exercise?");
    _right_eye_check_box = new QCheckBox("right");
    _left_eye_check_box = new QCheckBox("left");
    _eye_grid_layout->addWidget(_eye_label,0,0,1,2);
    _eye_grid_layout->addWidget(_left_eye_check_box,1,0);
    _eye_grid_layout->addWidget(_right_eye_check_box,1,1);
    _eye_group_box->setLayout(_eye_grid_layout);
}

void MainDialog::methods()
{
    _method_grid_layout = new QGridLayout;
    _method_label = new QLabel("What would you like to use during exercises?");
    _keybord_check_box = new QCheckBox("keybord");
    _touch_screen_box = new QCheckBox("touch screen");
    _mouse_check_box = new QCheckBox("mouse");
    _touch_pad_box = new QCheckBox("touchpad");
    _method_grid_layout->addWidget(_method_label, 0, 0, 1, 2);
    _method_grid_layout->addWidget(_keybord_check_box, 1, 0);
    _method_grid_layout->addWidget(_mouse_check_box, 1, 1);
    _method_grid_layout->addWidget(_touch_screen_box, 2, 0);
    _method_grid_layout->addWidget(_touch_pad_box, 2, 1);
    _method_group_box->setLayout(_method_grid_layout);
}

void MainDialog::name()
{
    _data->write();
    _data->read();
    _name_label = new QLabel("Name: ");
    _name_combo_box = new QComboBox;
    _name_combo_box->addItems(_data->names());
    _name_combo_box->setEditable(true);
    _name_combo_box->setCurrentText("");
//    _name_line_edit = new QLineEdit;
    _statistics_button = new QPushButton("Statistics");
    _name_box = new QHBoxLayout;
    _name_box->addWidget(_name_label);
//    _name_box->addWidget(_name_line_edit);
    _name_box->addWidget(_name_combo_box);
    _name_box->addWidget(_statistics_button);
}

void MainDialog::checkInitialValues()
{
    if((_keybord_check_box->checkState()==0&&
            _touch_pad_box->checkState()==0&&
            _touch_screen_box->checkState()==0&&
            _mouse_check_box->checkState()==0) ||
            (_name_combo_box->currentText() == "")){

        QMessageBox _message_box;
        QString text;
        text.append("Error: ");

        if((_keybord_check_box->checkState()==0&&
            _touch_pad_box->checkState()==0&&
            _touch_screen_box->checkState()==0&&
            _mouse_check_box->checkState()==0)){
           text.append("\n-You need to check what would you like to use during exercise");
        }

        if(_name_combo_box->currentText() == ""){
            text.append("\n-You need to write your name");
        }
        _message_box.setText(text);
        _message_box.setStandardButtons(QMessageBox::Ok);
        if(_message_box.exec()==QMessageBox::Ok){
            _message_box.close();
        }
    }
    else{
        if(_left_up_box->checkState()==0 &&
            _right_up_box->checkState()==0 &&
            _left_bot_box->checkState()==0 &&
            _right_bot_box->checkState()==0 &&
            _all_box->checkState()==0){
            _all_box->setCheckState(Qt::Checked);
        }
        if(_left_eye_check_box->checkState()==0&& _right_eye_check_box->checkState()==0){
            _left_eye_check_box->setCheckState(Qt::Checked);
            _right_eye_check_box->setCheckState(Qt::Checked);
        }
        if(!_data->checkIfExists(_name_combo_box->currentText())){
            _data->setName(_name_combo_box->currentText());
            _data->write();
            _personal_data->setName(_name_combo_box->currentText());
            _personal_data->readData();
            _prev_font_size_R = 40;
            _prev_font_size_L = 40;
            _prev_peripheral_font_size_R = 40;
            _prev_peripheral_font_size_L = 40;
            _smaller_R = false;
            _smaller_L = false;
        }
        if(_data->checkIfExists(_name_combo_box->currentText())){
            _personal_data->setName(_name_combo_box->currentText());
            _personal_data->readData();
            int good_r = _personal_data->getGoodR();
            int bad_r = _personal_data->getMissedR();
            int good_l = _personal_data->getGoodL();
            int bad_l = _personal_data->getMissedL();
            _bad_good_ratio_r = bad_r/good_r;
            _bad_good_ratio_l = bad_l/good_l;
            _prev_font_size_L = _personal_data->getFontSizeL();
            _prev_font_size_R = _personal_data->getFontSizeR();


            _prev_peripheral_font_size_R = _personal_data->getPerFontSizeR();
            _prev_peripheral_font_size_L = _personal_data->getPerFontSizeL();
            qDebug() << "Main Dialog _prev_peri R: " << _prev_peripheral_font_size_R << "_prev_l" << _prev_peripheral_font_size_L;
            if(_bad_good_ratio_r<0.5){
                _smaller_R = true;
            }else{
                _smaller_R = false;
            }
            if(_bad_good_ratio_l<0.5){
                _smaller_L = true;
            }else{
                _smaller_L = false;
            }
        }
        calculate();
    }
}

void MainDialog::clicksR(int good, int bad)
{
    _personal_data->setValuesR(good, bad);
}

void MainDialog::clicksL(int good, int bad)
{
    _personal_data->setValuesL(good, bad);

}

void MainDialog::fontSizeR(int font, int peripheral_font)
{
    _personal_data->setFontValuesR(font, peripheral_font);
    qDebug() << "Main Dialog peri font size R: " << peripheral_font;
}

void MainDialog::fontSizeL(int font, int peripheral_font)
{
    _personal_data->setFontValuesL(font, peripheral_font);
    qDebug() << "Main Dialog peri font size R: " << peripheral_font;
}

void MainDialog::keyClicksR(int good, int bad)
{
    _personal_data->setValuesR(good, bad);
}

void MainDialog::keyClicksL(int good, int bad)
{
    _personal_data->setValuesR(good, bad);
}

void MainDialog::saveData()
{
    if(_right_eye_check_box->checkState()==Qt::Checked && _left_eye_check_box->checkState()==Qt::Checked){
        _personal_data->setExerciseCtr();
        _personal_data->setVisualFieldRL(static_cast<int>(_visual_field));
        qDebug() << "RE && LE";
    }
    else if(_right_eye_check_box->checkState()==Qt::Checked && _left_eye_check_box->checkState()==Qt::Unchecked){
        _personal_data->setExerciseCtrR();
        _personal_data->setVisualFieldR(static_cast<int>(_visual_field));
    }
    else if(_right_eye_check_box->checkState()==Qt::Unchecked && _left_eye_check_box->checkState()==Qt::Checked){
        _personal_data->setExerciseCtrL();
        _personal_data->setVisualFieldL(static_cast<int>(_visual_field));
    }
    _personal_data->writeData();
}

void MainDialog::calculate()
{
    _fix_message_for_calculator = new QMessageBox;
    _fix_message_for_calculator->setText("Cover your left eye and place your right eye in front of red dot.\n"
                                         "Fix your eye on red dot.\n"
                                         "Click it (or key SPACE) when black dot disappear");
    _fix_message_for_calculator->setStandardButtons(QMessageBox::Ok);
    if(_fix_message_for_calculator->exec()==QMessageBox::Ok){
        _calculator->show();
      //  _calculator->resize(QDesktopWidget().availableGeometry(this).size());
        _calculator->positionAnimation();
    }
}

void MainDialog::statistics()
{
    if(_name_combo_box->currentText() == ""){
        QMessageBox messageBox;
        messageBox.setText("You need to enter your name");
        messageBox.setStandardButtons(QMessageBox::Ok);
        if(messageBox.exec()==QMessageBox::Ok){
            messageBox.close();
        }
    }
    else{
        _personal_data->setName(_name_combo_box->currentText());
        _personal_data->readData();
        if(_personal_data->getExCtr()!=0){
            _stats = new Statistics(nullptr, _name_combo_box->currentText(), _personal_data->getMissedR(), _personal_data->getMissedL(),
                                    _personal_data->getGoodR(), _personal_data->getGoodL(), _personal_data->getExCtr());
            _stats->show();
        }
        else{
            QMessageBox messageBox;
            messageBox.setText("Statistics cannot be displayed, you have not pactice yet.");
            messageBox.setStandardButtons(QMessageBox::Ok);
            if(messageBox.exec()==QMessageBox::Ok){
                messageBox.close();
            }
        }

    }
}

void MainDialog::excercise(double _screen_distance, double _angle, double _central_vis_field_px)
{
    _visual_field = _angle;
    if(_keybord_check_box->checkState()==Qt::Checked){
        _key_window = new KeyExerciseWindow(
                     nullptr,
                     _left_up_box->checkState(),
                     _right_up_box->checkState(),
                     _left_bot_box->checkState(),
                     _right_bot_box->checkState(),
                     _central_vis_field_px,
                     _right_eye_check_box->checkState(),
                     _left_eye_check_box->checkState(),
                     _prev_font_size_R, _prev_font_size_L,
                     _prev_peripheral_font_size_R, _prev_peripheral_font_size_L,
                     _smaller_R, _smaller_L, _personal_data->getExCtr());

        connect(_key_window, &KeyExerciseWindow::clicks_r, this, &MainDialog::clicksR);
        connect(_key_window, &KeyExerciseWindow::clicks_l, this, &MainDialog::clicksL);
        connect(_key_window, &KeyExerciseWindow::font_size_R, this, &MainDialog::fontSizeR);
        connect(_key_window, &KeyExerciseWindow::font_size_L, this, &MainDialog::fontSizeL);
        connect(_key_window, &KeyExerciseWindow::exercise_ended, this, &MainDialog::saveData);
        _first_message = new QMessageBox;
        QString text = "Your distance from screen is: ";
        text.append(QString::number(_screen_distance/10, 'f', 1));
        text.append(" cm.  \n");
        if(_right_eye_check_box->checkState()&& !_left_eye_check_box->checkState()){
            text.append("\n\nCover your left eye.\n");
        }
        if(!_right_eye_check_box->checkState()&& _left_eye_check_box->checkState()){
            text.append("\n\nCover your right eye\n");
        }
        if(_right_eye_check_box->checkState()&&_left_eye_check_box->checkState()){
            text.append("You will be train ");
            text.append(QString::number(_angle, 'f', 0));
            text.append("° of your visual field.    \n\n");
            text.append("Firstly cover your left eye, after 30 changes we will change eye\n");
        }
        if(!_right_eye_check_box->checkState()&&!_left_eye_check_box->checkState()){
            text.append("You will be train ");
            text.append(QString::number(_angle, 'f', 0));
            text.append("° of your visual field.    \n\n");
            text.append("Firstly cover your left eye, after 30 changes we will change eye\n");
        }
        text.append("Place your uncovered eye in front of black dot. \nThrough exercise you should look only at that dot.\n"
                    "If you can't see letter just click on dot or press SPACE.");
        _first_message->setText(text);
        _first_message->setStandardButtons(QMessageBox::Ok);
        if(_first_message->exec()==QMessageBox::Ok){
            _key_window->show();
            _key_window->randomAnimation();
            _calculator->close();
            //_key_window->resize(QDesktopWidget().availableGeometry(this).size());
            //this->close();
        }
    }
    else{
       _window = new ExerciseWindow(
                    nullptr,
                    _left_up_box->checkState(), _right_up_box->checkState(),
                    _left_bot_box->checkState(), _right_bot_box->checkState(),
                    _central_vis_field_px,
                    _right_eye_check_box->checkState(),
                    _left_eye_check_box->checkState(),
                    _prev_font_size_R, _prev_font_size_L,
                    _prev_peripheral_font_size_R, _prev_peripheral_font_size_L,
                    _smaller_R, _smaller_L);

      // qDebug() << "Window constructor R: " << _prev_font_size_R << "L: " << _prev_font_size_L;

       connect(_window, &ExerciseWindow::clicks_r, this, &MainDialog::clicksR);
       connect(_window, &ExerciseWindow::clicks_l, this, &MainDialog::clicksL);
       connect(_window, &ExerciseWindow::font_size_R, this, &MainDialog::fontSizeR);
       connect(_window, &ExerciseWindow::font_size_L, this, &MainDialog::fontSizeL);
       connect(_window, &ExerciseWindow::exercise_ended, this, &MainDialog::saveData);

       _first_message = new QMessageBox;
       QString text = "Your distance from screen is: ";
       text.append(QString::number(_screen_distance/10, 'f', 1));
       text.append(" cm.  \n");
       if(_right_eye_check_box->checkState()&& !_left_eye_check_box->checkState()){
           text.append("\n\nCover your left eye.\n");
       }
       if(!_right_eye_check_box->checkState()&& _left_eye_check_box->checkState()){
           text.append("\n\nCover your right eye\n");
       }
       if(_right_eye_check_box->checkState()&&_left_eye_check_box->checkState()){
           text.append("You will be train ");
           text.append(QString::number(_angle, 'f', 0));
           text.append("° of your visual field.    \n\n");
           text.append("Firstly cover your left eye, after 30 changes we will change eye\n");
       }
       if(!_right_eye_check_box->checkState()&&!_left_eye_check_box->checkState()){
           text.append("You will be train ");
           text.append(QString::number(_angle, 'f', 0));
           text.append("° of your visual field.    \n\n");
           text.append("Firstly cover your left eye, after 30 changes we will change eye\n");
       }
       text.append("Place your uncovered eye in front of black dot. \nThrough exercise you should look only at that dot.\n"
                   "If you can't see letter just click on dot or press SPACE.");
       _first_message->setText(text);
       _first_message->setStandardButtons(QMessageBox::Ok);
       if(_first_message->exec()==QMessageBox::Ok){
           _window->show();
           _window->randomAnimation();
           _calculator->close();
           //_key_window->resize(QDesktopWidget().availableGeometry(this).size());
           //this->close();
       }
    }
    _dialog_button_box->button( QDialogButtonBox::Ok )->setEnabled( false );
    _dialog_button_box->button(QDialogButtonBox::Cancel)->setEnabled(false);
    _dialog_button_box->addButton(QDialogButtonBox::Close);
}
