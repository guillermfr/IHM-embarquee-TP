#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QStringList>
#include <QColor>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chart(nullptr)
    , scene(nullptr)
    , axisX(nullptr)
    , axisY(nullptr)
    , x(0)
{
    ui->setupUi(this);
    initGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGraph()
{
    chart = new QChart();
    chart->setTitle("Données des capteurs");
    chart->legend()->setVisible(true);

    axisX = new QValueAxis();
    axisX->setRange(0, 100);
    axisX->setTitleText("Temps");

    axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setTitleText("Valeur");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    scene = new QGraphicsScene(this);
    scene->addItem(chart);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    chart->resize(ui->graphicsView->size());
}



void MainWindow::updateGraph(QString message)
{
    if (!message.startsWith("DATA!"))
        return;

    QStringList parts = message.split("!", Qt::SkipEmptyParts);

    for (int i = 1; i < parts.size(); ++i) {
        QStringList data = parts[i].split(":");

        if (data.size() != 3)
            continue;

        QString capteur = data[0];
        QString couleur = data[1];
        double valeur = data[2].toDouble();

        if (!seriesMap.contains(capteur)) {
            QLineSeries *serie = new QLineSeries();
            serie->setName(capteur);

            QPen pen;
            pen.setWidth(2);
            pen.setColor(QColor(couleur));
            serie->setPen(pen);

            chart->addSeries(serie);
            serie->attachAxis(axisX);
            serie->attachAxis(axisY);

            seriesMap[capteur] = serie;
        }

        seriesMap[capteur]->append(x, valeur);

        if (seriesMap[capteur]->count() > 100) {
            seriesMap[capteur]->remove(0);
        }
    }

    x++;

    if (x > 100) {
        axisX->setRange(x - 100, x);
    }

    chart->resize(ui->graphicsView->size());
}

void MainWindow::on_graphicsView_rubberBandChanged(
    const QRect &viewportRect,
    const QPointF &fromScenePoint,
    const QPointF &toScenePoint
    )
{
    Q_UNUSED(viewportRect);
    Q_UNUSED(fromScenePoint);
    Q_UNUSED(toScenePoint);
}