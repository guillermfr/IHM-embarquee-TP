/********************************************************************************
** Form generated from reading UI file 'taskpage.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKPAGE_H
#define UI_TASKPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_taskPage
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelWindowSize;
    QPushButton *buttonRefresh;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEditTaskName;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *buttonAddTask;
    QPushButton *buttonRemoveTask;
    QListWidget *listTasks;

    void setupUi(QWidget *taskPage)
    {
        if (taskPage->objectName().isEmpty())
            taskPage->setObjectName("taskPage");
        taskPage->resize(551, 424);
        horizontalLayout = new QHBoxLayout(taskPage);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        labelWindowSize = new QLabel(taskPage);
        labelWindowSize->setObjectName("labelWindowSize");
        labelWindowSize->setMargin(0);

        horizontalLayout_2->addWidget(labelWindowSize);

        buttonRefresh = new QPushButton(taskPage);
        buttonRefresh->setObjectName("buttonRefresh");
        QPalette palette;
        QBrush brush(QColor(94, 129, 172, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        QBrush brush1(QColor(31, 155, 93, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush1);
        buttonRefresh->setPalette(palette);
        buttonRefresh->setStyleSheet(QString::fromUtf8("background-color: rgb(94, 129, 172);"));

        horizontalLayout_2->addWidget(buttonRefresh);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        lineEditTaskName = new QLineEdit(taskPage);
        lineEditTaskName->setObjectName("lineEditTaskName");
        lineEditTaskName->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 66, 82); border: 1 solid rgb(94, 129, 172);"));

        verticalLayout->addWidget(lineEditTaskName);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        buttonAddTask = new QPushButton(taskPage);
        buttonAddTask->setObjectName("buttonAddTask");
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush1);
        QBrush brush2(QColor(48, 140, 198, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Link, brush2);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Link, brush2);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Link, brush2);
        buttonAddTask->setPalette(palette1);
        buttonAddTask->setStyleSheet(QString::fromUtf8("background-color: rgb(94, 129, 172);"));

        horizontalLayout_3->addWidget(buttonAddTask);

        buttonRemoveTask = new QPushButton(taskPage);
        buttonRemoveTask->setObjectName("buttonRemoveTask");
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush1);
        buttonRemoveTask->setPalette(palette2);
        buttonRemoveTask->setStyleSheet(QString::fromUtf8("background-color: rgb(94, 129, 172);"));

        horizontalLayout_3->addWidget(buttonRemoveTask);


        verticalLayout->addLayout(horizontalLayout_3);

        listTasks = new QListWidget(taskPage);
        listTasks->setObjectName("listTasks");
        listTasks->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 86, 106);"));

        verticalLayout->addWidget(listTasks);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(taskPage);

        QMetaObject::connectSlotsByName(taskPage);
    } // setupUi

    void retranslateUi(QWidget *taskPage)
    {
        taskPage->setWindowTitle(QCoreApplication::translate("taskPage", "Form", nullptr));
        labelWindowSize->setText(QString());
        buttonRefresh->setText(QCoreApplication::translate("taskPage", "Refresh", nullptr));
        lineEditTaskName->setText(QString());
        lineEditTaskName->setPlaceholderText(QCoreApplication::translate("taskPage", "Enter a task...", nullptr));
        buttonAddTask->setText(QCoreApplication::translate("taskPage", "Add Task", nullptr));
        buttonRemoveTask->setText(QCoreApplication::translate("taskPage", "Remove Task", nullptr));
    } // retranslateUi

};

namespace Ui {
    class taskPage: public Ui_taskPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKPAGE_H
