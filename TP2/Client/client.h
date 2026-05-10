#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    void start(const QString &host, int port);

private slots:
    void onReadyRead();

signals:
    void messageReceived(QString message);

private:
    QUdpSocket *socket;
    QHostAddress serverAddress;
    quint16 serverPort;
};

#endif // CLIENT_H