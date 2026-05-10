#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QMap>
#include <QList>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void start(int TCPport, int UDPport);

private slots:
    void onNewConnection();
    void onReadyReadTCP();
    void onReadyReadUDP();
    // void onDisconnected();

private:
    void handleMessage(QTcpSocket *socket, const QString &message);
    void publishMessage(const QString &topic, const QString &payload);

    QTcpServer *TCPserver;
    QUdpSocket *UDPsocket;

    QMap<QString, QString> capteurs;
    QSet<QString> clients;

signals:
};

#endif // SERVER_H
