#ifndef KEYEXERCISEWINDOW_H
#define KEYEXERCISEWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QFont>
#include <QDesktopWidget>
#include <QTime>
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class KeyExerciseWindow;
}

class KeyExerciseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit KeyExerciseWindow(QWidget *parent, bool l_u, bool r_u, bool l_b, bool r_b, double central_vision_field_ex, bool r_e, bool l_e,
                               int prev_font_size_R, int prev_font_size_L,
                               int prev_peripheral_size_R, int prev_peripheral_size_L,
                               bool smaller_R, bool smaller_L, int ctr);
    ~KeyExerciseWindow();

public slots:
    void randomAnimation();
    void setFontSizeR(bool, int);
    void setPeripheralFontSizeR(bool, int);
    void setFontSizeL(bool, int);
    void setPeripheralFontSizeL(bool, int);

private slots:
    void missedCounter();
    void clickedCounter();
    void dotCounter();
    void messageBox();

private:
    Ui::KeyExerciseWindow *ui;
    QPushButton *_key_button;
    QPushButton *_dot_button;
    QPropertyAnimation *_animation;
    QStringList _letters;
    QStringList _letters_1;
    QStringList _letters_2;
    QStringList _letters_3;
    QTimer *_timer;
    QMessageBox *_message_box;
    int _font_size;
    int _font_size_R;
    int _font_size_L;
    int _peripheral_font_size;
    int _peripheral_font_size_R;
    int _peripheral_font_size_L;
    int _clicks_ctr;
    int _missed_ctr;
    int _dot_ctr;
    bool _right_eye;
    bool _left_eye;
    int _px_central_vis_field;
    int x_pos;
    int y_pos;
    int per_x_l;
    int per_y_u;
    int per_x_r;
    int per_y_b;

signals:
    void clicks_r(int, int);
    void clicks_l(int, int);
    void font_size_R(int, int);
    void font_size_L(int, int);
    void exercise_ended();
};

#endif // KEYEXERCISEWINDOW_H
