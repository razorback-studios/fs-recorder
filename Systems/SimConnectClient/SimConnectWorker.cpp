#include "SimConnectWorker.hpp"
#include <ctime>

SimConnectWorker::SimConnectWorker()
{
    //Set file to empty
    m_file.open("D:\\Projects\\WhitePicketFence\\FSRecorder\\FSRecorder\\build\\Debug\\SimConnectWorker.txt", std::ios_base::trunc);
    m_file.close();

    LogData("SimConnectWorker Created");
}

SimConnectWorker::~SimConnectWorker()
{
    LogData("SimConnectWorker Destroyed");
}

void SimConnectWorker::LogData(std::string data)
{
    m_file.open("D:\\Projects\\WhitePicketFence\\FSRecorder\\FSRecorder\\build\\Debug\\SimConnectWorker.txt", std::ios_base::app);
    //Log with timestamp using
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    m_file << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " - " << data << std::endl;
    m_file.close();
}

void CALLBACK MyDispatchProc1(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
{
    SimConnectWorker *worker = reinterpret_cast<SimConnectWorker*>(pContext);
    HRESULT hr;

    worker->LogData("Data Received");

    switch (pData->dwID)
    {
        case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
        {
            SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

            switch(pObjData->dwRequestID)
            {
                case REQUEST_1:
                {
                    dataTypes* ps = (dataTypes*)&pObjData->dwData;
                    worker->LogData("Title: " + std::string(ps->title));
                    worker->LogData("Altitude: " + std::to_string(ps->altitude));
                    break;
                }
            }
            break;
        }

        case SIMCONNECT_RECV_ID_QUIT:
        {
            worker->SetQuit(1);
            break;
        }

        default:
            break;
    }
}

void SimConnectWorker::dataRequest()
{
    HRESULT hr;
    //Check that we are connected to msfs
    SimConnectManager& manager = SimConnectManager::Instance();


    if(manager.ConnectToSim())
    {
        LogData("Connected to MSFS");

        //Request Data
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "TITLE", NULL, SIMCONNECT_DATATYPE_STRING256);
        if(FAILED(hr))
        {
            LogData("Failed to Add to Data Definition");
        }

        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE ALTITUDE", "feet");
        if(FAILED(hr))
        {
            LogData("Failed to Add to Data Definition");
        }

        //Request Data
        hr = SimConnect_RequestDataOnSimObject(manager.GetHandle(), REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
        if(FAILED(hr))
        {
            LogData("Failed to Request Data");
        }

        while (quit == 0)
        {
            
            if(manager.GetHandle() == NULL)
            {
                LogData("Handle is NULL");
            }


            SimConnect_CallDispatch(manager.GetHandle(), MyDispatchProc1, this);
            Sleep(500);
        }

        return;
    }
}

// void SimConnectWorker::dataRequest()
// {
//     LogData("Data Requested");

//     //Create the instance
//     SimConnectManager& manager = SimConnectManager::Instance();

//     SetHandle(manager.GetHandle());
    
//     //Log Conneciton Status
//     if(!manager.ConnectToSim())
//     {
//         LogData("Failed to Connect to MSFS");
//         dataRequest();
//     }

//     HRESULT hr;

//     if(SUCCEEDED(manager.ConnectToSim()))
//     {
//         LogData("Connected to MSFS");

//         //Setup Data Definition
//         hr = SimConnect_AddToDataDefinition(m_handle, AIRCRAFT_DATA, "Title", NULL, SIMCONNECT_DATATYPE_STRING256);
//         hr = SimConnect_AddToDataDefinition(m_handle, AIRCRAFT_DATA, "Plane Altitude", "feet");

//         hr = SimConnect_SubscribeToSystemEvent(m_handle, EVENT_SIM_START, "SimStart");
//         if(FAILED(hr))
//         {
//             LogData("Failed to Subscribe to SimStart");

//             //Try again
//             dataRequest();

//         } else {
//             LogData("Subscribed to SimStart");
//         }

//         LogData("Launch Flight");

//         while (0 == quit)
//         {
//             SimConnect_CallDispatch(m_handle, ProcessData, this);
//             Sleep(1000);
//         };
//     }
//}