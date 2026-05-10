#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "listener.h"

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

private:
    Ui::MainWindow *ui;
    Listener *listener;

private slots:
    void onMessageReceived(const QString &message);
};
#endif // MAINWINDOW_H
