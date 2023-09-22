#pragma once

#include <QObject>

#include <Windows.h>
#include <SimConnect.h>

class SimConnectWorker : public QObject
{
    Q_OBJECT 

public:
    explicit SimConnectWorker(QObject *parent = nullptr);
    void attemptConnect();

signals:
    void Connected();
    void ConnectionFailed();
    void LogMessage(QString message);

public slots:
    void DoWork();

};