#ifndef ZCHARTVIEW_H
#define ZCHARTVIEW_H

#include <QtCharts>

using namespace QtCharts;

class ZChartView : public QChartView
{

public:
    enum ZoomMode {
        NoZoom,
        Pan,
        RectangleZoom,
        VerticalZoom,
        HorizontalZoom
    };

    ZChartView(QWidget *parent = 0);

    void zoomX(qreal factor, qreal xcenter);
    void zoomX(qreal factor);

    void zoomY(qreal factor, qreal ycenter);
    void zoomY(qreal factor);

    ZoomMode zoomMode() const;
    void setZoomMode(const ZoomMode &zoomMode);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    bool m_isTouching = false;
    QPointF m_lastMousePos;
    ZoomMode m_zoomMode = NoZoom;

    static bool isAxisTypeZoomableWithMouse(const QAbstractAxis::AxisType type);
    QPointF getSeriesCoordFromChartCoord(const QPointF & mousePos, QAbstractSeries *series) const;
    QPointF getChartCoordFromSeriesCoord(const QPointF & seriesPos, QAbstractSeries *series) const;
};

#endif // ZCHARTVIEW_H
