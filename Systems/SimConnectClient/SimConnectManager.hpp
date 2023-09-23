#pragma once

//Includes
#include <Windows.h>
#include <SimConnect.h>
#include <string>

//Singleton for SimConnect to pass the handler arround with only one instance running
class SimConnectManager
{
public:
    static SimConnectManager& Instance();
    HANDLE GetHandle() const { return handle; };
    bool ConnectToSim();

    std::string GetOutputMessage() { return m_outputMessage; };
    void SetOutputMessage(std::string outputMessage);

    //Destructor
    ~SimConnectManager();

private:
    SimConnectManager();
    HANDLE handle;
    std::string m_outputMessage;
};