#ifndef STATISTICS_H
#define STATISTICS_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieLegendMarker>

QT_CHARTS_USE_NAMESPACE

class Statistics
{
    Q_GADGET
    QPieSeries *_series;
    QPieSlice *_slice_R;
    QPieSlice *_slice_L;
    QPieSlice *_slice_missed_R;
    QPieSlice *_slice_missed_L;
    QChart *_chart;
    QChartView *_chartView;

public:
    Statistics(QString name, int missed_R, int missed_L, int good_R, int good_L, int ctr);
    QMainWindow window;
};

#endif // STATISTICS_H
