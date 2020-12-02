#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "zchart.h"
#include "zchartview.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum ActionMode {
        Selection,
        HorizontalZoom,
        RectangleZoom,
        Pan
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QChart *chart() const;
    ZChartView *chartView() const;

    ActionMode action() const;
    void setAction(const ActionMode &action);

private slots:
    void on_actionReset_Zoom_triggered();
    void on_actionSelection_Mode_triggered();
    void on_actionZoom_triggered();
    void on_actionPan_triggered();
    void on_actionHorizontal_Zoom_triggered();

    void on_actionlegend_triggered();

private:
    Ui::MainWindow *ui;
    ZChart *m_chart = nullptr;
    ActionMode m_action = Selection;
    void setActionButton(const ActionMode &action, bool state);
};
#endif // MAINWINDOW_H
