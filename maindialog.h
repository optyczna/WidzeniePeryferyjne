#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "exercisewindow.h"
#include "distancecalculator.h"
#include "datahandling.h"
#include "keyexercisewindow.h"
#include "personaldata.h"
#include "statistics.h"
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QCheckBox>
#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

private:
    Ui::MainDialog *ui;
    QVBoxLayout *_main_layout;
    QComboBox *_name_combo_box;
    QHBoxLayout *_name_box;
    QLabel *_name_label;
    QLineEdit *_name_line_edit;
    QPushButton *_statistics_button;
    QDialogButtonBox *_dialog_button_box;
    QGridLayout *_ex_grid_layout;
    QGroupBox *_ex_group_box;
    QLabel *_ex_label;
    QCheckBox *_other_check_box;
    QCheckBox *_just_ex_check_box;
    QCheckBox *_after_stroke_check_box;
    QLabel *_quadrant_label;
    QGridLayout *_quadrant_grid_box;
    QGroupBox *_quadrant_group_box;
    QCheckBox *_left_up_box;
    QCheckBox *_left_bot_box;
    QCheckBox *_right_up_box;
    QCheckBox *_right_bot_box;
    QCheckBox *_all_box;
    QGridLayout *_eye_grid_layout;
    QGroupBox *_eye_group_box;
    QLabel *_eye_label;
    QCheckBox *_right_eye_check_box;
    QCheckBox *_left_eye_check_box;
    QGridLayout *_method_grid_layout;
    QGroupBox *_method_group_box;
    QLabel *_method_label;
    QCheckBox *_keybord_check_box;
    QCheckBox *_mouse_check_box;
    QCheckBox *_touch_screen_box;
    QCheckBox *_touch_pad_box;

    QMessageBox *_first_message;
    QMessageBox *_fix_message_for_calculator;
    DistanceCalculator *_calculator;
    ExerciseWindow *_window;
    KeyExerciseWindow *_key_window;
    DataHandling *_data;
    PersonalData *_personal_data;
    Statistics *_stats;
    double _bad_good_ratio_r;
    double _bad_good_ratio_l;
    int _ex_ctr;
    bool _smaller_R;
    bool _smaller_L;
    int _prev_font_size_R;
    int _prev_font_size_L;
    int _prev_peripheral_font_size_R;
    int _prev_peripheral_font_size_L;

    void quadrant();
    void exercises();
    void eye();
    void methods();
    void name();
    double _visual_field;

private slots:
    void checkInitialValues();
    void calculate();
    void statistics();
    void excercise(double, double, double);

public slots:
    void clicksR(int, int);
    void clicksL(int, int);
    void fontSizeR(int, int);
    void fontSizeL(int, int);
    void keyClicksR(int, int);
    void keyClicksL(int, int);
    void saveData();
};

#endif // MAINDIALOG_H
