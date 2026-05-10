#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class Listener : public QObject
{
    Q_OBJECT
public:
    explicit Listener(QObject *parent = nullptr);
    void connectToBroker(const QString &host, int port);
    void subscribeToTopic(QString topic);

signals:
    void messageReceived(const QString message);

private slots:
    void onConnected();
    void onReadyRead();

private:
    QTcpSocket *socket;
    QByteArray buffer;

};

#endif // LISTENER_H