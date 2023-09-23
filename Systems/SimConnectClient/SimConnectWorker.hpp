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
    Q_PROPERTY(QString statusMessage READ GetStatusMessage WRITE SetStatusMessage NOTIFY StatusChanged)

public:
    explicit SimConnectWorker(QObject *parent = nullptr);
    void SetConnectionStatus(bool status);
    bool GetConnectionStatus() const { return m_connectionStatus; };
    QString GetStatusMessage() const { return m_statusMessage; };
    void SetStatusMessage(QString statusMessage);

private:
    QTimer* m_timer;
    QString m_statusMessage;
    bool m_connectionStatus;

    void GatherData();

signals:
    void ConnectionChanged();
    void ConnectedSuccessfully();
    void ConnectionInvalid();
    void StatusChanged();

private slots:
    void onTimeout();

};