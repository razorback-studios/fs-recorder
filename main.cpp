#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Systems/Recording/Recording.hpp"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //QML Register
    qmlRegisterType<Recording>("RecordingController", 1, 0, "Recording");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/FSRecorder/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
