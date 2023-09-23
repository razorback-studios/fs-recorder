// #include "SimConnectWorker.hpp"
// #include <QDebug>

// //Singleton Pattern Instance
// SimConnectWorker& SimConnectWorker::GetInstance()
// {
//     static SimConnectWorker instance;
//     return instance;
// }

// //Constructor
// SimConnectWorker::SimConnectWorker() //: handle(NULL)
// {
//     //Inititalizes a new QTimer
//     connectionTimer = new QTimer(this);

//     //Connects so that every time the connectiontimer timesout, it calls the connection failed function
//     connect(connectionTimer, &QTimer::timeout, this, &SimConnectWorker::onConnectionFailed);

//     //Have timer run every 5 seconds
//     connectionTimer->start(5000);

//     m_connectionStatus = false;
// }

// void SimConnectWorker::SetConnectionStatus(bool status)
// {
//     m_connectionStatus = status;
// }

// void SimConnectWorker::AttemptConnection()
// {
//     //Check if the HRESULT is Success
//     if(SUCCEEDED(SimConnect_Open(&handle, "FSRecorder", NULL, 0, 0, 0)))
//     {
//         //Stop the timer
//         connectionTimer->stop();

//         //Set the new status
//         SetConnectionStatus(true);

//         emit Connected();
//         emit ConnectionChanged();
//         emit LogMessage("Connected To MSFS");
//     } else
//     {
//         SetConnectionStatus(false);
//         emit ConnectionFailed();
//         emit LogMessage("Failed to connect.");
//     }
// }

// void SimConnectWorker::onConnectionFailed()
// {
//     AttemptConnection();
// }