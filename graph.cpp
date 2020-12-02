#include "graph.h"

Graph::Graph() :
    gridVisibile(false),    
    axisX1(new QValueAxis),
    axisX2(new QValueAxis),
    axisY1(new QValueAxis),
    axisY2(new QValueAxis)
{

}

Graph::~Graph()
{
    delete axisY1;
}

void Graph::addPlot(QChart *chart, const Plot &plt)
{
    switch (plt.getType()) {
    case LINEPLOT:
      {
        QLineSeries *series = new QLineSeries();
        if (!plt.getName().isEmpty()) series->setName(plt.getName());
        series->append(plt.getPoints());
        QPen pen(plt.getColor());
        pen.setWidth(plt.getWidth());
        series->setPen(pen);
        //series->attachAxis(axisY);
//        chart->addSeries(series);
//        chart->setAxisY(axisY,series);
//        axisY->setMinorTickCount(5);
//        axisY->applyNiceNumbers();

        chart->addSeries(series);
        chart->addAxis(axisY1,Qt::AlignLeft);
        chart->addAxis(axisX1,Qt::AlignBottom);
        series->attachAxis(axisX1);
        series->attachAxis(axisY1);

        break;
      }
    case SCATTERPLOT:
      {
        QScatterSeries *series = new QScatterSeries();
        if (!plt.getName().isEmpty()) series->setName(plt.getName());
        series->append(plt.getPoints());
        series->setColor(plt.getColor());
        series->setBorderColor(plt.getColor());
        series->setMarkerSize(plt.getMarkerSize());
        series->setMarkerShape(plt.getMarkerShape());
        chart->addSeries(series);
        chart->addAxis(axisX1,Qt::AlignBottom);
        chart->addAxis(axisX2,Qt::AlignTop);
        chart->addAxis(axisY1,Qt::AlignLeft);
        chart->addAxis(axisY2,Qt::AlignRight);

        series->attachAxis(axisX1);
        series->attachAxis(axisX2);
        series->attachAxis(axisY1);
        series->attachAxis(axisY2);
        //axisY->setMinorGridLineVisible(true);
        //chart->addAxis(axisY, Qt::AlignLeft);
        //QValueAxis *axisY = new QValueAxis;
        //axisY->setMinorTickCount(2);

        //axisY->setGridLineVisible(false);
        //chart->setAxisY(axisY,series);
        //axisY->applyNiceNumbers();

        //QValueAxis *axisX = new QValueAxis;
        //axisX->setRange(10, 20.5);
        //axisX->setTickCount(10);
        //axisX->setLabelFormat("%.2f");
        //chart->setAxisX(axisX, series);


        //series->attachAxis(axisY);


        break;
      }
    }

}

void Graph::setGridVisibile(bool value)
{
    gridVisibile = value;
}

bool Graph::getGridVisibile() const
{
    return gridVisibile;
}

void Graph::draw(QChart *chart)
{
    // Ticks
    axisY1->applyNiceNumbers();
    axisX2->setLabelsVisible(false);
    axisY2->setLabelsVisible(false);
    axisX2->setVisible(false);
    axisY2->setVisible(false);
    //axisX1->setMinorTickCount(5);  //Bug in qtcharts
    //axisY1->setMinorTickCount(5);

    // Axis color
    QPen axisPen(QRgb(0xd18952));
    axisPen.setWidth(2);
    axisX1->setLinePen(axisPen);
    axisX2->setLinePen(axisPen);
    axisY1->setLinePen(axisPen);
    axisY2->setLinePen(axisPen);

    // Grid
    axisX1->setGridLineVisible(gridVisibile);
    axisX2->setGridLineVisible(gridVisibile);
    axisY1->setGridLineVisible(gridVisibile);
    axisY2->setGridLineVisible(gridVisibile);
    axisX1->setMinorGridLineVisible(false);
    axisX2->setMinorGridLineVisible(false);
    axisY1->setMinorGridLineVisible(false);
    axisY2->setMinorGridLineVisible(false);

    // Legend
    QLegend *legend = chart->legend();
    legend->setVisible(true);
//    legend->detachFromChart();
//    qreal legendWidth = 400;
//    qreal legendHeight = 200;
//    QRectF chartViewRect = chartView->rect();
//    qInfo() << "View: " << chartViewRect.width() << chartView->height();
//    qreal legendPosX = chartViewRect.width()-legendWidth;
//    qreal legendPosY = 0;
//    legend->setGeometry(QRectF(legendPosX,legendPosY,legendWidth,legendHeight));
}
