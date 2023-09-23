// #pragma once

// #include <QObject>
// #include <QTimer>
// #include <Windows.h>
// #include <SimConnect.h>

// //Singleton Class instance for the application to get the SimConnect Connection
// class SimConnectWorker : public QObject
// {
//     Q_OBJECT 
//     Q_PROPERTY(BOOL connectionStatus READ GetConnectionStatus WRITE SetConnectionStatus NOTIFY ConnectionChanged)

// public:
//     static SimConnectWorker& GetInstance();
//     HANDLE getHandle() const { return handle; };
//     void SetConnectionStatus(bool status);
//     bool GetConnectionStatus() { return m_connectionStatus; };

// private:
//     SimConnectWorker();
//     HANDLE handle;
//     QTimer *connectionTimer;
//     bool m_connectionStatus;

//     void AttemptConnection();

// signals:
//     void Connected();
//     void ConnectionFailed();
//     void ConnectionChanged();
//     void LogMessage(QString message);

// private slots:
//     void onConnectionFailed();

// };