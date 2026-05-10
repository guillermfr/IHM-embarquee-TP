#include "loginpage.h"
#include "ui_loginpage.h"

loginPage::loginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginPage)
{
    ui->setupUi(this);
}

loginPage::~loginPage()
{
    delete ui;
}

void loginPage::on_loginButton_clicked()
{
    ui->textEditUsername->setStyleSheet("");
    ui->textEditPassword->setStyleSheet("");
    ui->MessageLabel->setText("");
    ui->MessageLabel->setStyleSheet("");

    QString username = ui->textEditUsername->toPlainText();
    QString password = ui->textEditPassword->toPlainText();

    if(username.isEmpty() || password.isEmpty()) {
        if(username.isEmpty()) {
            ui->textEditUsername->setStyleSheet("border: 1 solid red");
        }
        if(password.isEmpty()) {
            ui->textEditPassword->setStyleSheet("border: 1 solid red");
        }
    }
    else {
        if(username == "test" && password == "test") {
            ui->MessageLabel->setText("correct logins");
            ui->MessageLabel->setStyleSheet("color: green");

            emit changePage();
        }
        else {
            ui->MessageLabel->setText("incorrect logins");
            ui->MessageLabel->setStyleSheet("color: red");
        }
    }
}

