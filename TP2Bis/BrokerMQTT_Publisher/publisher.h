#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class Publisher : public QObject
{
    Q_OBJECT
public:
    explicit Publisher(QObject *parent = nullptr);
    void connectToBroker(const QString &host, int port);
    void publishTemperature(float temperature);

private slots:
    void onConnected();

private:
    QTcpSocket *socket;

};

#endif // PUBLISHER_H
