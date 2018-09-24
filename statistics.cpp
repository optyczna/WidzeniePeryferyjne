#include "statistics.h"

Statistics::Statistics(QString name, int missed_R, int missed_L, int good_R, int good_L, int ctr)
{
    _series = new QPieSeries();

    _series->append("Good (right eye)", good_R);
    _series->append("Missed (right eye)", missed_R);
    _series->append("Missed (left eye)", missed_L);
    _series->append("Good (left eye)", good_L);

    _slice_missed_R = _series->slices().at(1);
    _slice_missed_R->setLabelVisible();

    _slice_missed_L = _series->slices().at(2);
    _slice_missed_L->setLabelVisible();

    _slice_R = _series->slices().at(0);
    _slice_R->setLabelVisible();

    _slice_L = _series->slices().at(3);
    _slice_L->setLabelVisible();



    _chart = new QChart();
    _chart->addSeries(_series);
    _chart->setTitle(name);
    _chart->setTitleFont(QFont("Arial", 15));
    _chart->legend()->setAlignment(Qt::AlignRight);
    _chart->setAnimationOptions(QChart::AllAnimations);
    _chartView = new QChartView(_chart);
    _chartView->setRenderHint(QPainter::Antialiasing);

    const auto markers = _chart->legend()->markers(_series);
    for (QLegendMarker *marker : markers) {
        QPieLegendMarker *pieMarker = qobject_cast<QPieLegendMarker *>(marker);
            pieMarker->setLabel(QString("%1 %2")
                                .arg(pieMarker->slice()->label())
                                .arg(pieMarker->slice()->value()));
            pieMarker->setFont(QFont("Arial", 10));
    }

    window.setCentralWidget(_chartView);
    window.setWindowTitle("Statistics");
    window.resize(900, 600);
}
