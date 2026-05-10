#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    listener = new Listener(this);

    connect(listener, &Listener::messageReceived, this, &MainWindow::onMessageReceived);

    // Connexion au localhost avec le port du breaker
    listener->connectToBroker("127.0.0.1", 1234);

    // Abonnement au topic "TEMP"
    listener->subscribeToTopic("TEMP");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Mise à jour du texte
void MainWindow::onMessageReceived(const QString &message)
{
    ui->label->setText(message);
}