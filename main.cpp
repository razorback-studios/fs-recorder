#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <thread>

#include "Systems/Recording/Recording.hpp"
#include "Systems/SimConnectClient/SimConnectWorker.hpp"
#include "Systems/SimConnectClient/SimConnectManager.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //QML Register
    qmlRegisterType<Recording>("Razorback", 1, 0, "Recording");
    //qmlRegisterType<SimConnectWorker>("Razorback", 1, 0, "SimConnectWorker");

    //Create a Worker
    SimConnectWorker worker;
    std::thread t(&SimConnectWorker::dataRequest, &worker);
    t.detach();
    
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/FSRecorder/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
