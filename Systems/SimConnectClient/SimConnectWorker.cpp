#include "SimConnectWorker.hpp"
#include "SimConnectManager.hpp"

SimConnectWorker::SimConnectWorker(QObject *parent) : QObject(parent), m_connectionStatus(false)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SimConnectWorker::onTimeout);

    //Timer shoudl run 5 seconds
    m_timer->start(5000);
}

void SimConnectWorker::onTimeout()
{
    //Create the instance
    SimConnectManager& manager = SimConnectManager::Instance();
    
//     //If it is connected
    if(manager.ConnectToSim())
    {
        SetConnectionStatus(true);
        // We can uncomment this if we want the timer to stop when a connection is found
        //m_timer->stop();

        //Currently, once a conneciton is found we slow down how often we scan, so that if the game is closed or crashes, it can restart looking for a new connection.
        m_timer->setInterval(20000);
        
    }
    else
    {
        SetConnectionStatus(false);
        //Reset the timer back to a 5 second interval
        m_timer->setInterval(5000);
    }
}

void SimConnectWorker::SetConnectionStatus(bool status)
{
    if(m_connectionStatus != status)
    {
        m_connectionStatus = status;
        emit ConnectionChanged();
    }
}