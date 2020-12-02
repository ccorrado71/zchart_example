#ifndef PLOT_H
#define PLOT_H

#include <QColor>
#include <QList>
#include <QPoint>
#include <QtCharts>
//#include <QDebug>

using namespace QtCharts;

enum {LINEPLOT = 1, SCATTERPLOT, LINESCATTER, BARPLOT};

class Plot
{
public:
    Plot(int plotType = LINEPLOT, QColor plotColor = Qt::black);

    int getType() const;
    QColor getColor() const;
    int getWidth() const;
    qreal getMarkerSize() const;
    QScatterSeries::MarkerShape getMarkerShape() const;
    QList<QPointF> getPoints() const;
    QString getName() const;

    void setColor(const QColor &value);
    void setWidth(int value);
    void setMarkerSize(const qreal &value);
    void setPoints(const QVector<float>& x, const QVector<float>& y);
    void setMarkerShape(const QScatterSeries::MarkerShape &value);
    void setName(const QString &value);    

private:
    QList<QPointF> points;
    int type;
    QColor color;
    int lineWidth;
    qreal markerSize;
    QScatterSeries::MarkerShape markerShape;
    QString name;
};

#endif // PLOT_H
