#ifndef DISTANCECALCULATOR_H
#define DISTANCECALCULATOR_H

#include "exercisewindow.h"

#include <QDialog>
#include <QDesktopWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QMessageBox>

namespace Ui {
class DistanceCalculator;
}

class DistanceCalculator : public QDialog
{
    Q_OBJECT

public:
    explicit DistanceCalculator(QWidget *parent = nullptr);
    ~DistanceCalculator();

private:
    Ui::DistanceCalculator *ui;
    QPushButton *_look_at_button;
    QPushButton *_move_button;
    QPropertyAnimation *_pos_animation;
    QMessageBox *_info_box;

public slots:
    void animationStopped();
    void positionAnimation();

signals:
    void distanceCalculated();
    void computations(double, double, double);
};

#endif // DISTANCECALCULATOR_H
