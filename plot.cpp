#include "plot.h"

Plot::Plot(int plotType, QColor plotColor) :
    type(plotType),
    color(plotColor),
    lineWidth(1),
    markerSize(5.0),
    markerShape(QScatterSeries::MarkerShapeCircle),
    name(" ")
{

}

int Plot::getType() const
{
    return type;
}

QColor Plot::getColor() const
{
    return color;
}

void Plot::setWidth(int value)
{
    lineWidth = value;
}

int Plot::getWidth() const
{
    return lineWidth;
}

qreal Plot::getMarkerSize() const
{
    return markerSize;
}

void Plot::setMarkerSize(const qreal &value)
{
    markerSize = value;
}

void Plot::setPoints(const QVector<float> &x, const QVector<float> &y)
{
    points.clear();
    for (int i = 0; i < x.size(); i++) {
        QPointF point(x[i], y[i]);
        points.append(point);
    }
}

void Plot::setMarkerShape(const QScatterSeries::MarkerShape &value)
{
    markerShape = value;
}

void Plot::setName(const QString &value)
{
    name = value;
}

void Plot::setColor(const QColor &value)
{
    color = value;
}

QString Plot::getName() const
{
    return name;
}

QList<QPointF> Plot::getPoints() const
{
    return points;
}

QScatterSeries::MarkerShape Plot::getMarkerShape() const
{
    return markerShape;
}
