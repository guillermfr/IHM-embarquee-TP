#ifndef CAPTEUR_H
#define CAPTEUR_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QMap>
#include <random>
#include <QDebug>

class Capteur : public QObject
{
    Q_OBJECT
public:
    explicit Capteur(QObject *parent = nullptr);
    void connectToServer(const QString host, int port);
    void publishConfig();
    void sendData();
    void addCaptor(QString name, QString color);

    QMap<QString, QString> capteurs;

private slots:
    void onConnected();

private:
    QTcpSocket *TCPsocket;
    QUdpSocket *UDPsocket;

    QString server_address;
    int server_port;

    float randomFloat(float min, float max);

signals:
};

#endif // CAPTEUR_H
