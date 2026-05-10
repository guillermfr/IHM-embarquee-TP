#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    publisher = new Publisher(this);

    // Connection au localhost avec le port du broker
    publisher->connectToBroker("127.0.0.1", 1234);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Génération aléatoire d'un float
// Il faudrait mettre la fonction dans un autre fichier pour que ce soit plus propre
float randomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);

    return dist(gen);
}

// Envoi d'un float random lorsque le bouton est appuyé
void MainWindow::on_pushButton_clicked()
{
    float temp = randomFloat(0.0f, 50.0f);
    publisher->publishTemperature(temp);
}

