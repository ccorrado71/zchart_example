#ifndef GRAPH_H
#define GRAPH_H

#include "plot.h"

class Graph
{
public:
    Graph();
    ~Graph();
    void addPlot(QChart *chart, const Plot& plt);
    void setGridVisibile(bool value);
    bool getGridVisibile() const;
    void draw(QChart *chart);

private:
    bool gridVisibile;    
    QValueAxis *axisX1, *axisX2, *axisY1, *axisY2;
};

#endif // GRAPH_H
