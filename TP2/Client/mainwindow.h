#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMap>

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void updateGraph(QString message);

private slots:
    void on_graphicsView_rubberBandChanged(
        const QRect &viewportRect,
        const QPointF &fromScenePoint,
        const QPointF &toScenePoint
        );

private:
    Ui::MainWindow *ui;

    QChart *chart;
    QGraphicsScene *scene;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QMap<QString, QLineSeries*> seriesMap;

    int x;

    void initGraph();
};

#endif // MAINWINDOW_H