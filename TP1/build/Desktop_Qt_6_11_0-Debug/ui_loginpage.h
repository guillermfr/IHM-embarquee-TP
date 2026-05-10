/********************************************************************************
** Form generated from reading UI file 'loginpage.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINPAGE_H
#define UI_LOGINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginPage
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *UsernameLabel;
    QTextEdit *textEditUsername;
    QLabel *PasswordLabel;
    QTextEdit *textEditPassword;
    QPushButton *loginButton;
    QLabel *MessageLabel;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *loginPage)
    {
        if (loginPage->objectName().isEmpty())
            loginPage->setObjectName("loginPage");
        loginPage->resize(493, 471);
        horizontalLayout = new QHBoxLayout(loginPage);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        UsernameLabel = new QLabel(loginPage);
        UsernameLabel->setObjectName("UsernameLabel");

        verticalLayout->addWidget(UsernameLabel);

        textEditUsername = new QTextEdit(loginPage);
        textEditUsername->setObjectName("textEditUsername");
        textEditUsername->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(textEditUsername);

        PasswordLabel = new QLabel(loginPage);
        PasswordLabel->setObjectName("PasswordLabel");

        verticalLayout->addWidget(PasswordLabel);

        textEditPassword = new QTextEdit(loginPage);
        textEditPassword->setObjectName("textEditPassword");
        textEditPassword->setEnabled(true);
        textEditPassword->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(textEditPassword);

        loginButton = new QPushButton(loginPage);
        loginButton->setObjectName("loginButton");
        loginButton->setStyleSheet(QString::fromUtf8("background-color: rgb(94, 129, 172);"));

        verticalLayout->addWidget(loginButton);

        MessageLabel = new QLabel(loginPage);
        MessageLabel->setObjectName("MessageLabel");

        verticalLayout->addWidget(MessageLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(loginPage);

        QMetaObject::connectSlotsByName(loginPage);
    } // setupUi

    void retranslateUi(QWidget *loginPage)
    {
        loginPage->setWindowTitle(QCoreApplication::translate("loginPage", "Form", nullptr));
        UsernameLabel->setText(QCoreApplication::translate("loginPage", "Username", nullptr));
        PasswordLabel->setText(QCoreApplication::translate("loginPage", "Password", nullptr));
        loginButton->setText(QCoreApplication::translate("loginPage", "Login", nullptr));
        MessageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class loginPage: public Ui_loginPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGE_H
