#include "SimConnectManager.hpp"

SimConnectManager& SimConnectManager::Instance()
{
    static SimConnectManager instance;
    return instance;
}

SimConnectManager::SimConnectManager() : handle(NULL)
{
    m_outputMessage = "Not Connected.";
}

SimConnectManager::~SimConnectManager()
{
    if(handle != NULL)
    {
        SimConnect_Close(handle);
        handle = NULL;
    }
}

bool SimConnectManager::ConnectToSim()
{
    //Attempt a connection to MSFS
    if(SUCCEEDED(SimConnect_Open(&handle, "FSRecorder", NULL, 0, 0, 0)))
    {
        m_outputMessage = "Successfully Connected.";
        return true;
    }
    else
    {
        m_outputMessage = "Failed to Connect.";
        handle = NULL;
        return false;
    }
}

void SimConnectManager::SetOutputMessage(std::string outputMessage)
{
    m_outputMessage = outputMessage;
}