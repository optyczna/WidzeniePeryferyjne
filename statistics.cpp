#include "statistics.h"
#include "ui_statistics.h"
#include <QDesktopWidget>

Statistics::Statistics(QWidget *parent, QString name, int missed_R, int missed_L, int good_R, int good_L, int ctr) :
    QDialog(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);
    QBoxLayout *main_layout = new QBoxLayout(QBoxLayout::TopToBottom);
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

   this->setGeometry(QRect(800,800,1200,800));
   this->setWindowTitle("Statistics");
   main_layout->addWidget(_chartView);
   //main_layout->setAlignment(Qt::AlignCenter);
   //main_layout->setGeometry(QDesktopWidget().availableGeometry(this));
   setLayout(main_layout);
}

Statistics::~Statistics()
{
    delete ui;
}
