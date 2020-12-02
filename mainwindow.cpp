#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_chart = new ZChart();
    ui->chartView->setChart(m_chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
    ui->actionSelection_Mode->setChecked(true);
    //setAction(Selection);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_chart;
}

QChart *MainWindow::chart() const
{
    return m_chart;
}

ZChartView *MainWindow::chartView() const
{
    return ui->chartView;
}

void MainWindow::on_actionSelection_Mode_triggered()
{
    qInfo() << "Selection mode" << m_action;
    setAction(Selection);
}

void MainWindow::on_actionHorizontal_Zoom_triggered()
{
    setAction(HorizontalZoom);
}

void MainWindow::on_actionZoom_triggered()
{    
    setAction(RectangleZoom);
}

void MainWindow::on_actionReset_Zoom_triggered()
{
    if (ui->chartView->chart()->isZoomed())
        ui->chartView->chart()->zoomReset();
    if (action() == Pan) {
        qInfo() << "Action is Pan";
    }
}

void MainWindow::setActionButton(const MainWindow::ActionMode &action, bool state)
{
    switch (action) {
    case Selection:
        ui->actionSelection_Mode->setChecked(state);
        break;
    case HorizontalZoom:
        ui->actionHorizontal_Zoom->setChecked(state);
        break;
    case RectangleZoom:
        ui->actionZoom->setChecked(state);
        break;
    case Pan:
        ui->actionPan->setChecked(state);
        break;
    }
}

void MainWindow::setAction(const ActionMode &action)
{    
    if (m_action != action) setActionButton(m_action,false);
    m_action = action;
    switch (action) {
    case Selection:
        ui->chartView->setZoomMode(ZChartView::NoZoom);
        break;
    case HorizontalZoom:
        ui->chartView->setZoomMode(ZChartView::HorizontalZoom);
        break;
    case RectangleZoom:
        ui->chartView->setZoomMode(ZChartView::RectangleZoom);
        break;
    case Pan:
        ui->chartView->setZoomMode(ZChartView::Pan);
        break;
    }
}

MainWindow::ActionMode MainWindow::action() const
{
    return m_action;
}

void MainWindow::on_actionPan_triggered()
{
    setAction(Pan);
}

void MainWindow::on_actionlegend_triggered()
{
    if (ui->chartView->chart()->legend()->isVisible())
        ui->chartView->chart()->legend()->setVisible(false);
    else
        ui->chartView->chart()->legend()->setVisible(true);
}
