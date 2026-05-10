#include "taskpage.h"
#include "ui_taskpage.h"
#include "QMessageBox"

QString getSizeString(QSize windowSize, QPoint windowPosition) {
    QString sizeString = QString("Window Size : %1 x %2 | Window position : %3 & %4")
    .arg(windowSize.width())
        .arg(windowSize.height())
        .arg(windowPosition.x())
        .arg(windowPosition.y());

    return sizeString;
}

taskPage::taskPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::taskPage)
{
    ui->setupUi(this);

    QSize windowSize = size();
    QPoint windowPosition = window()->frameGeometry().topLeft();
    ui->labelWindowSize->setText(getSizeString(windowSize, windowPosition));
}

taskPage::~taskPage()
{
    delete ui;
}

// => La position ne fonctionne plus correctement ? Mais ça marchait bien quand c'était une mainWindow et pas un widget
void taskPage::resizeEvent(QResizeEvent *event)
{
    QSize windowSize = size();
    QPoint windowPosition = window()->frameGeometry().topLeft();

    ui->labelWindowSize->setText(getSizeString(windowSize, windowPosition));

    QWidget::resizeEvent(event);
}

// => NE FONCTIONNE PLUS CORRECTEMENT
// Avant, c'était la mainWindow donc ça marchait bien
// Mais maintenant, c'est un widget, donc la fenêtre ne bouge plus vraiment, elle est contenu dans la mainWindow parent
void taskPage::moveEvent(QMoveEvent *event)
{
    QSize windowSize = size();
    QPoint windowPosition = window()->frameGeometry().topLeft();

    ui->labelWindowSize->setText(getSizeString(windowSize, windowPosition));

    QWidget::moveEvent(event);
}

void taskPage::on_buttonRefresh_clicked()
{
    QSize windowSize = size();
    QPoint windowPosition = window()->frameGeometry().topLeft();

    qDebug() << "Widget at position" << windowPosition;

    ui->labelWindowSize->setText(getSizeString(windowSize, windowPosition));
}

void taskPage::on_buttonAddTask_clicked()
{
    ui->lineEditTaskName->setStyleSheet("border: 1 solid rgb(94, 129, 172)");

    QString taskName = ui->lineEditTaskName->displayText();

    if(taskName.isEmpty()) {
        ui->lineEditTaskName->setStyleSheet("border: 1 solid red");
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Task cannot be empty!");
        msgBox.exec();
    }
    else {
        QList<QListWidgetItem*> tasks = ui->listTasks->findItems(taskName, Qt::MatchExactly);

        if(tasks.isEmpty()) {
            ui->listTasks->addItem(taskName);
        }
        else {
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Warning");
            msgBox.setText("This task already exists!");
            msgBox.exec();
        }
    }
}

void taskPage::on_buttonRemoveTask_clicked()
{
    QList<QListWidgetItem*> selectedTasks = ui->listTasks->selectedItems();

    if(selectedTasks.empty()) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Please select a task to remove");
        msgBox.exec();
    }
    else {
        foreach (QListWidgetItem* item, selectedTasks) {
            delete item;
        }
    }
}

