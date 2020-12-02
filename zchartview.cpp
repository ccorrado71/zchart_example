#include "zchartview.h"
#include "rangelimitedvalueaxis.h"

ZChartView::ZChartView(QWidget *parent):
    QChartView(parent)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

ZChartView::ZoomMode ZChartView::zoomMode() const
{
    return m_zoomMode;
}

void ZChartView::setZoomMode(const ZChartView::ZoomMode &zoomMode)
{
    if (m_zoomMode != zoomMode) {
        m_zoomMode = zoomMode;
        switch (zoomMode) {
        case NoZoom:
            setRubberBand(QChartView::NoRubberBand);
            setDragMode(QChartView::NoDrag);
            break;
        case Pan:
            setRubberBand(QChartView::NoRubberBand);
            setDragMode(QChartView::ScrollHandDrag);
            break;
        case RectangleZoom:
            setRubberBand(QChartView::RectangleRubberBand);
            setDragMode(QChartView::NoDrag);
            break;
        case HorizontalZoom:
            setRubberBand(QChartView::HorizontalRubberBand);
            setDragMode(QChartView::NoDrag);
            break;
        case VerticalZoom:
            setRubberBand(QChartView::VerticalRubberBand);
            setDragMode(QChartView::NoDrag);
            break;
        }
    }
}

void ZChartView::zoomX(qreal factor, qreal xcenter)
{
    QRectF rect = chart()->plotArea();
    qreal widthOriginal = rect.width();
    rect.setWidth(widthOriginal / factor);
    qreal centerScale = (xcenter / widthOriginal);

    qreal leftOffset = (xcenter - (rect.width() * centerScale) );

    rect.moveLeft(rect.x() + leftOffset);
    chart()->zoomIn(rect);
}

void ZChartView::zoomX(qreal factor)
{
    QRectF rect = chart()->plotArea();
    qreal widthOriginal = rect.width();
    QPointF center_orig = rect.center();

    rect.setWidth(widthOriginal / factor);

    rect.moveCenter(center_orig);

    chart()->zoomIn(rect);
}

void ZChartView::zoomY(qreal factor, qreal ycenter)
{
    QRectF rect = chart()->plotArea();
    qreal heightOriginal = rect.height();
    rect.setHeight(heightOriginal / factor);
    qreal centerScale = (ycenter / heightOriginal);

    qreal topOffset = (ycenter - (rect.height() * centerScale) );

    rect.moveTop(rect.x() + topOffset);
    chart()->zoomIn(rect);
}

void ZChartView::zoomY(qreal factor)
{
    QRectF rect = chart()->plotArea();
    qreal heightOriginal = rect.height();
    QPointF center_orig = rect.center();

    rect.setHeight(heightOriginal / factor);

    rect.moveCenter(center_orig);

    chart()->zoomIn(rect);
}

void ZChartView::mousePressEvent(QMouseEvent *event)
{
    if (m_zoomMode == NoZoom) return;
    m_isTouching = true;
    m_lastMousePos = event->localPos();
    qWarning() << "Press" << m_lastMousePos;
    QChartView::mousePressEvent(event);
}

void ZChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_isTouching)
        return;

    if (dragMode() == ScrollHandDrag) {
        if (event->buttons() & Qt::LeftButton) {

            bool moveHorizontalAxis = false;
            for (auto axis : chart()->axes()) {
                if (axis->orientation() == Qt::Horizontal && isAxisTypeZoomableWithMouse(axis->type())) {
                    moveHorizontalAxis = true;
                    break;
                }
            }

            if (QGuiApplication::keyboardModifiers() & Qt::KeyboardModifier::ControlModifier)
                moveHorizontalAxis = !moveHorizontalAxis;

            if (moveHorizontalAxis) {
                qreal dx = -(event->localPos().x() - m_lastMousePos.x());
                qWarning() << "Move" << event->localPos().x() << dx;
                for (auto series : this->chart()->series()) {
                    for (auto axis : series->attachedAxes()) {
                        if (axis->orientation() != Qt::Horizontal)
                            continue;
                        if (axis->property("rangeLimited").toBool()) {
                            RangeLimitedValueAxis *rangeLimitedAxis = static_cast<RangeLimitedValueAxis*>(axis);
                            if (rangeLimitedAxis->orientation() != Qt::Horizontal)
                                continue;
                            QPointF oldPoint = getSeriesCoordFromChartCoord(m_lastMousePos, series);
                            QPointF newPoint = getSeriesCoordFromChartCoord(event->localPos(), series);
                            qreal dxAxis = -(newPoint.x() - oldPoint.x());
                            if (rangeLimitedAxis->isLowerRangeLimited()
                                    && (rangeLimitedAxis->min() + dxAxis) < rangeLimitedAxis->lowerLimit()) {
                                dxAxis = -(rangeLimitedAxis->min() - rangeLimitedAxis->lowerLimit());
                                if (qFuzzyIsNull(dxAxis)) {
                                    dx = 0.0;
                                } else {
                                    QPointF dummyCoord(oldPoint.x() - dxAxis, m_lastMousePos.y());
                                    dummyCoord = getChartCoordFromSeriesCoord(dummyCoord, series);
                                    dx = (m_lastMousePos.x() - dummyCoord.x());
                                }
                            }


                            if (rangeLimitedAxis->isUpperRangeLimited()
                                    && (rangeLimitedAxis->max() + dxAxis) > rangeLimitedAxis->upperLimit()) {
                                dxAxis = -(rangeLimitedAxis->upperLimit() - rangeLimitedAxis->max());
                                if (qFuzzyIsNull(dxAxis)) {
                                    dx = 0.0;
                                } else {
                                    QPointF dummyCoord(oldPoint.x() - dxAxis, m_lastMousePos.y());
                                    dummyCoord = getChartCoordFromSeriesCoord(dummyCoord, series);
                                    dx = -(m_lastMousePos.x() - dummyCoord.x());
                                }
                            }
                        }
                    }
                }
                chart()->scroll(dx, 0);
            } else {
                qreal dy = event->pos().y() - m_lastMousePos.y();
                for (auto series : this->chart()->series()) {
                    for (auto axis : series->attachedAxes()) {
                        if (axis->orientation() != Qt::Vertical)
                            continue;
                        if (axis->property("rangeLimited").toBool()) {
                            RangeLimitedValueAxis *rangeLimitedAxis = static_cast<RangeLimitedValueAxis*>(axis);
                            if (rangeLimitedAxis->orientation() != Qt::Vertical)
                                continue;
                            QPointF oldPoint = getSeriesCoordFromChartCoord(m_lastMousePos, series);
                            QPointF newPoint = getSeriesCoordFromChartCoord(event->localPos(), series);
                            qreal dyAxis = -(newPoint.y() - oldPoint.y());
                            if (rangeLimitedAxis->isLowerRangeLimited()
                                    && (rangeLimitedAxis->min() + dyAxis) < rangeLimitedAxis->lowerLimit()) {
                                dyAxis = rangeLimitedAxis->min() - rangeLimitedAxis->lowerLimit();
                                if (qFuzzyIsNull(dyAxis)) {
                                    dy = 0.0;
                                } else {
                                    QPointF dummyCoord(m_lastMousePos.x(), oldPoint.y() - dyAxis);
                                    dummyCoord = getChartCoordFromSeriesCoord(dummyCoord, series);
                                    dy = (m_lastMousePos.y() - dummyCoord.y());
                                }
                            }

                            if (rangeLimitedAxis->isUpperRangeLimited()
                                    && (rangeLimitedAxis->max() + dyAxis) > rangeLimitedAxis->upperLimit()) {
                                dyAxis = rangeLimitedAxis->upperLimit() - rangeLimitedAxis->max();
                                if (qFuzzyIsNull(dyAxis)) {
                                    dy = 0.0;
                                } else {
                                    QPointF dummyCoord(m_lastMousePos.x(), oldPoint.y() - dyAxis);
                                    dummyCoord = getChartCoordFromSeriesCoord(dummyCoord, series);
                                    dy = -(m_lastMousePos.y() - dummyCoord.y());
                                }
                            }
                        }
                    }
                }
                chart()->scroll(0, dy);
            }
        }
        m_lastMousePos = event->pos();

    }

    QChartView::mouseMoveEvent(event);
}

void ZChartView::wheelEvent(QWheelEvent *event)
{
    bool zoomHorizontalAxis = false;
    for (auto axis : chart()->axes()) {
        if (axis->orientation() == Qt::Horizontal && isAxisTypeZoomableWithMouse(axis->type())) {
            zoomHorizontalAxis = true;
            break;
        }
    }

    if (QGuiApplication::keyboardModifiers() & Qt::KeyboardModifier::ControlModifier)
        zoomHorizontalAxis = !zoomHorizontalAxis;

    if (zoomHorizontalAxis) {
        if (event->angleDelta().y() > 0) {
            zoomX(2, event->pos().x() - chart()->plotArea().x());
        } else if (event->angleDelta().y() < 0) {
            zoomX(0.5, event->pos().x() - chart()->plotArea().x());
        }
    } else {
        if (event->angleDelta().y() > 0) {
            zoomY(2, event->pos().y() - chart()->plotArea().y());
        } else if (event->angleDelta().y() < 0) {
            zoomY(0.5, event->pos().y() - chart()->plotArea().y());
        }
    }
}

void ZChartView::mouseReleaseEvent(QMouseEvent *event)
{
    m_isTouching = false;
    QChartView::mouseReleaseEvent(event);
}

void ZChartView::keyPressEvent(QKeyEvent *event)
{
    qInfo() << event->key();
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_0:
        chart()->zoomReset();
        break;
        //![1]
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);        
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}

bool ZChartView::isAxisTypeZoomableWithMouse(const QAbstractAxis::AxisType type)
{
    return (type == QAbstractAxis::AxisTypeValue
            || type == QAbstractAxis::AxisTypeLogValue
            || type == QAbstractAxis::AxisTypeDateTime);
}

QPointF ZChartView::getSeriesCoordFromChartCoord(const QPointF &chartPos, QAbstractSeries *series) const
{
    auto const chartItemPos = chart()->mapFromScene(chartPos);
    auto const valueGivenSeries = chart()->mapToValue(chartItemPos, series);
    return valueGivenSeries;
}

QPointF ZChartView::getChartCoordFromSeriesCoord(const QPointF &seriesPos, QAbstractSeries *series) const
{
    QPointF ret = chart()->mapToPosition(seriesPos, series);
    ret = chart()->mapFromScene(ret);
    return ret;
}
