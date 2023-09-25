#include "SimConnectBridge.hpp"

SimConnectBridge::SimConnectBridge(QObject *parent) : QObject(parent)
{
    m_isConnected = false;

    //Check that the worker is null
    if(m_worker == nullptr)
    {
        //Create new instance of that worker
        m_worker = new SimConnectWorker();
    }

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SimConnectBridge::TryConnection);
    m_timer->start(5000);

    Logger& logger = Logger::Instance();
    logger.Log("SimConnectBridge Created");
}

SimConnectBridge::~SimConnectBridge()
{
    Logger& logger = Logger::Instance();
    logger.Log("SimConnectBridge Destroyed");

    delete m_worker;
    m_worker = nullptr;

    delete m_timer;
    m_timer = nullptr;
}

void SimConnectBridge::TryConnection()
{
    SimConnectManager& manager = SimConnectManager::Instance();

    Logger& logger = Logger::Instance();

    if(manager.ConnectToSim() && m_isConnected == false)
    {
        logger.Log("Bridge found MSFS Connection");
        m_isConnected = true;
        emit connectionChanged();
    }
    else if (!manager.ConnectToSim() && m_isConnected == true) 
    {
        logger.Log("Bridge can't find MSFS connection");
        m_isConnected = false;
        emit connectionChanged();
    }
}

void SimConnectBridge::StartRecording()
{
    Logger& logger = Logger::Instance();
    logger.Log("Recording proccess begun.");

}