#ifndef ZCHART_H
#define ZCHART_H

#include <QObject>
#include <QtCharts>

using namespace QtCharts;

class ZChart : public QChart
{
    Q_OBJECT
public:
    ZChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());

signals:

};

#endif // ZCHART_H
