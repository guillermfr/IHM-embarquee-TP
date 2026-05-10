#ifndef BROKER_H
#define BROKER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QMap>
#include <QDebug>

class Broker : public QObject
{
    Q_OBJECT
public:
    explicit Broker(QObject *parent = nullptr);
    void start(quint16 port);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    void handleMessage(QTcpSocket *socket, const QString &message);
    void subscribeSocket(QTcpSocket *socket, const QString &topic);
    void publishMessage(const QString &topic, const QString &payload);

    QTcpServer *server;
    QMap<QString, QList<QTcpSocket*>> topicSubscribers;
    QHash<QTcpSocket*, QByteArray> buffers;

signals:
};

#endif // BROKER_H
