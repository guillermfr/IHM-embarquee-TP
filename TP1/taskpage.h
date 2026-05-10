#ifndef TASKPAGE_H
#define TASKPAGE_H

#include <QWidget>

namespace Ui {
class taskPage;
}

class taskPage : public QWidget
{
    Q_OBJECT

public:
    explicit taskPage(QWidget *parent = nullptr);
    ~taskPage();

private slots:
    void on_buttonAddTask_clicked();

    void on_buttonRemoveTask_clicked();

    void on_buttonRefresh_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;

private:
    Ui::taskPage *ui;
};

#endif // TASKPAGE_H
