#ifndef EXERCISEWINDOW_H
#define EXERCISEWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QPushButton>
#include <QTime>

namespace Ui {
class ExerciseWindow;
}

class ExerciseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ExerciseWindow(QWidget *parent = nullptr);
    ExerciseWindow(QWidget *parent, bool l_u, bool r_u, bool l_b,bool r_b,
                   double distance, bool r_e, bool l_e,
                   int prev_font_size_R, int prev_font_size_L,
                   int prev_peripheral_size_R, int prev_peripheral_size_L,
                   bool smaller_R, bool smaller_L);
    ~ExerciseWindow();

private:
    Ui::ExerciseWindow *ui;
    QPushButton *_button;
    QPushButton *_dot_button;
    QPropertyAnimation *_animation;
    QMessageBox *_alert_box;
    QTimer *_timer;
    int _dot_ctr;
    int _button_ctr;
    int _missed_ctr;
    int x;
    int y;
    int x_pos;
    int y_pos;
    int _font_size;
    int _font_size_R;
    int _font_size_L;
    int _peripheral_font_size;
    bool _r_e;
    bool _l_e;    
    double _width_of_central_vision_field_in_px;

public slots:
     void randomAnimation();
     void setFontSizeR(bool, int);
     void setPeripheralFontSizeR(bool, int);
     void setFontSizeL(bool, int);
     void setPeripheralFontSizeL(bool, int);

private slots:

    void clickCounterDot();
    void clickCounterButton();
    void clickCounterMissed();
    void messageBox();

signals:
    void infoToMessageBox();
    void clicks_r(int, int);
    void clicks_l(int, int);
    void exercise_ended();
    void font_size_R(int, int);
    void font_size_L(int, int);
};

#endif // EXERCISEWINDOW_H
