#include "SimConnectWorker.hpp"
#include "SimConnectManager.hpp"
#include <QDebug>

SimConnectWorker::SimConnectWorker(QObject *parent) : QObject(parent), m_connectionStatus(false)
{
    m_statusMessage = "Idle";
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SimConnectWorker::onTimeout);

    //Timer should run 10 times per second
    m_timer->start(500);
}

void SimConnectWorker::onTimeout()
{
    //Create the instance
    SimConnectManager& manager = SimConnectManager::Instance();
    
//     //If it is connected
    if(manager.ConnectToSim())
    {
        SetConnectionStatus(true);
    }
    else
    {
        SetConnectionStatus(false);
    }
}

void SimConnectWorker::SetConnectionStatus(bool status)
{
    //Connection has been made
    if(m_connectionStatus == false && status == true)
    {
        m_connectionStatus = status;
        m_statusMessage = "Connection Made.";
        emit ConnectionChanged();
        emit ConnectedSuccessfully();  
        emit StatusChanged();    
    }
    else if(m_connectionStatus == true && status == false) //Connection failed
    {
        m_connectionStatus = status;
        m_statusMessage = "No Connection.";
        qWarning() << "Test";
        emit ConnectionChanged();
        emit ConnectionInvalid();
        emit StatusChanged();    
    }
    else //Other Disagree?
    {
        SetStatusMessage("Error: Status Disagree");
    }

    // if(m_connectionStatus != status)
    // {
    //     m_connectionStatus = status;
    //     emit ConnectionChanged();
    // }
}

void SimConnectWorker::SetStatusMessage(QString statusMessage)
{
    m_statusMessage = statusMessage;
}