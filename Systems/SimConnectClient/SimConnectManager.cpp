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

bool SimConnectManager::ConnectToSim()
{
    //If the handle is still not NULL this means we have a valid connection.
    //This also needs to be uncommented if we decide to stop the timer
    // if (handle != NULL)
    // {
    //     //Exit the function
    //     return true;
    // }

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