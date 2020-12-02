#include "mainwindow.h"
#include "fileparser.h"
#include "plot.h"
#include "graph.h"

#include <QApplication>
#include <QDebug>
#include <QString>
#include <QStringList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    QChart *chart = w.chart();  //new QChart();
    Graph grafico;
    QVector<float> xvet, yvet;
    FileParser<float> fp("/home/corrado/expo/merca.xy");

    Plot plt1(SCATTERPLOT,Qt::red);
    fp.readFile(xvet,yvet);
    plt1.setPoints(xvet,yvet);
    plt1.setName("Observed");
    grafico.addPlot(chart,plt1);

    Plot plt2(LINEPLOT,Qt::red);
    fp.setXcol(4);
    fp.readFile(yvet);
    plt2.setPoints(xvet,yvet);
    plt2.setName("Background");
    plt2.setColor(Qt::blue);
    grafico.addPlot(chart,plt2);

    //w.setCentralWidget(chartView);
    w.show();
    grafico.draw(chart);
    return a.exec();
}
