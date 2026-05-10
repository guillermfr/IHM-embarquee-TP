/**
 * @file main.cpp
 * @brief Application entry point and QML bootstrapping.
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "loginbackend.h"
#include "mainbackend.h"
#include "tcpmanager.h"

/**
 * @brief Application entry point.
 * @param argc Number of command-line arguments.
 * @param argv Command-line argument vector.
 * @return Qt event loop exit code.
 */
int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    TcpManager tcpManager;
    LoginBackend loginBackend(&tcpManager);
    MainBackend mainBackend(&tcpManager);

    QObject::connect(&loginBackend, &LoginBackend::loginSuccess, &app, [&mainBackend, &loginBackend]() {
        mainBackend.setCurrentUsername(loginBackend.currentUsername());
    });

    engine.rootContext()->setContextProperty("loginBackend", &loginBackend);
    engine.rootContext()->setContextProperty("mainBackend", &mainBackend);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
	);
    engine.loadFromModule("lab_ihm_client", "Main");

    return QCoreApplication::exec();
}