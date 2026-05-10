#include "capteur.h"

#include <QDebug>
#include <QMap>
#include <cmath>
#include <random>

Capteur::Capteur(QObject *parent)
    : QObject{parent}
    , TCPsocket(new QTcpSocket(this))
    , UDPsocket(new QUdpSocket(this))
{
    connect(TCPsocket, &QTcpSocket::connected,
            this, &Capteur::onConnected);
}

void Capteur::connectToServer(const QString host, int port)
{
    server_address = host;
    server_port = port;

    TCPsocket->connectToHost(server_address, server_port);

    if (!TCPsocket->waitForConnected(5000)) {
        qDebug() << "TCP Connection failed:" << TCPsocket->errorString();
    }
}

void Capteur::onConnected()
{
    qDebug() << "Publisher Connected to broker";
    publishConfig();
}

void Capteur::publishConfig()
{
    if (!TCPsocket || TCPsocket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "TCP socket not connected";
        return;
    }

    QString message = "REGISTER_SENSOR!";

    for (auto it = capteurs.constBegin(); it != capteurs.constEnd(); ++it) {
        message += it.key() + ":" + it.value() + "!";
    }

    TCPsocket->write(message.toUtf8());
    TCPsocket->flush();

    qDebug() << "Capteur published:" << message;
}

void Capteur::addCaptor(QString name, QString color)
{
    capteurs.insert(name, color);
    publishConfig();
}

float Capteur::randomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

void Capteur::sendData()
{
    static int n = 0;
    static QMap<QString, double> phases;

    QString message = "DATA!";

    double amplitude = 40.0;
    double offset = 50.0;
    double frequence = 0.08;
    double bruitMax = 3.0;

    for (auto it = capteurs.constBegin(); it != capteurs.constEnd(); ++it) {
        QString capteurType = it.key();
        QString couleur = it.value();

        if (!phases.contains(capteurType)) {
            phases[capteurType] = randomFloat(0.0f, 2.0f * M_PI);
        }

        double phase = phases[capteurType];
        double bruit = randomFloat(-bruitMax, bruitMax);

        double value =
            offset +
            amplitude * std::sin(2.0 * M_PI * frequence * n + phase) +
            bruit;

        if (value < 0.0) {
            value = 0.0;
        }
        else if (value > 100.0) {
            value = 100.0;
        }

        message += capteurType + ":" + couleur + ":" + QString::number(value, 'f', 2) + "!";
    }

    n++;

    UDPsocket->writeDatagram(
        message.toUtf8(),
        QHostAddress(server_address),
        server_port
        );

    qDebug() << "UDP sent:" << message;
}