#ifndef STATISTICS_H
#define STATISTICS_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieLegendMarker>
#include <QDialog>
#include <QBoxLayout>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Statistics;
}

class Statistics : public QDialog
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent, QString name, int missed_R, int missed_L, int good_R, int good_L, int ctr);
    ~Statistics();

private:
    Ui::Statistics *ui;
    QPieSeries *_series;
    QPieSlice *_slice_R;
    QPieSlice *_slice_L;
    QPieSlice *_slice_missed_R;
    QPieSlice *_slice_missed_L;
    QChart *_chart;
    QChartView *_chartView;
};

#endif // STATISTICS_H
