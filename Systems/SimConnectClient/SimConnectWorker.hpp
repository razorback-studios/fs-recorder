#pragma once

#include <QObject>
#include <QTimer>
#include <Windows.h>
#include <SimConnect.h>

// //Singleton Class instance for the application to get the SimConnect Connection
class SimConnectWorker : public QObject
{
    Q_OBJECT 
    Q_PROPERTY(BOOL connectionStatus READ GetConnectionStatus WRITE SetConnectionStatus NOTIFY ConnectionChanged)

public:
    explicit SimConnectWorker(QObject *parent = nullptr);
    void SetConnectionStatus(bool status);
    bool GetConnectionStatus() const { return m_connectionStatus; };

private:
    QTimer* m_timer;
    bool m_connectionStatus;

signals:
    void ConnectionChanged();

private slots:
    void onTimeout();

};