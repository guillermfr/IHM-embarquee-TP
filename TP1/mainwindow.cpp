#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    taskPage* taskPageWidget = new taskPage(this);
    loginPage* loginPageWidget = new loginPage(this);

    ui->stackedWidget->addWidget(taskPageWidget);
    ui->stackedWidget->addWidget(loginPageWidget);

    QObject::connect(loginPageWidget, &loginPage::changePage, this, [=]() {
        ui->stackedWidget->setCurrentWidget(taskPageWidget);
    });

    ui->stackedWidget->setCurrentWidget(loginPageWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}