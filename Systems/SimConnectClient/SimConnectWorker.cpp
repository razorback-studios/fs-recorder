#include "SimConnectWorker.hpp"
#include <ctime>

SimConnectWorker::SimConnectWorker()
{
    //Set file to empty
    m_file.open("D:\\Projects\\WhitePicketFence\\FSRecorder\\FSRecorder\\build\\Debug\\SimConnectWorker.txt", std::ios_base::trunc);

    m_csv.open("D:\\Projects\\WhitePicketFence\\FSRecorder\\FSRecorder\\build\\Debug\\SimConnectWorker.csv", std::ios_base::trunc);
    if(m_csv.is_open())
    {
        m_csv << "Time,Title,Altitude,Latitude,Longitude,Pitch,Bank,Heading,VelocityZ,VelocityY,VelocityX" << std::endl;
    }
    else
    {
        LogData("Failed to open CSV");
    }

    LogData("SimConnectWorker Created");
}

SimConnectWorker::~SimConnectWorker()
{
    LogData("SimConnectWorker Destroyed");
    m_file.close();
    m_csv.close();
}

void SimConnectWorker::LogData(std::string data)
{
    //Log with timestamp using
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    m_file << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " - " << data << std::endl;
}

void SimConnectWorker::WriteToCSV(std::string data)
{
    m_csv << data << std::endl;
}

void CALLBACK MyDispatchProc1(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
{
    SimConnectWorker *worker = reinterpret_cast<SimConnectWorker*>(pContext);
    HRESULT hr;

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
                    //Log Time with Chrono High Res Clock
                    //Set var to hold time
                    auto current = std::chrono::high_resolution_clock::now();
                    auto count = std::chrono::duration_cast<std::chrono::microseconds>(current - worker->start).count();
                    // worker->LogData("--------------------------------------------------");
                    // worker->LogData("Time: " + std::to_string(count));
                    // worker->LogData("Title: " + std::string(ps->title));
                    // worker->LogData("Altitude: " + std::to_string(ps->altitude));
                    // worker->LogData("Latitude: " + std::to_string(ps->latitude));
                    // worker->LogData("Longitude: " + std::to_string(ps->longitude));
                    // worker->LogData("Pitch: " + std::to_string(ps->pitch));
                    // worker->LogData("Bank: " + std::to_string(ps->bank));
                    // worker->LogData("Heading: " + std::to_string(ps->heading));
                    // worker->LogData("Velocity Z: " + std::to_string(ps->velocityZ));
                    // worker->LogData("Velocity Y: " + std::to_string(ps->velocityY));
                    // worker->LogData("Velocity X: " + std::to_string(ps->velocityX));
                    // worker->LogData("--------------------------------------------------");

                    //Log to csv
                    worker->WriteToCSV(std::to_string(count) + "," + std::string(ps->title) + "," + std::to_string(ps->altitude) + "," + std::to_string(ps->latitude) + "," + std::to_string(ps->longitude) + "," + std::to_string(ps->pitch) + "," + std::to_string(ps->bank) + "," + std::to_string(ps->heading) + "," + std::to_string(ps->velocityZ) + "," + std::to_string(ps->velocityY) + "," + std::to_string(ps->velocityX));

                    break;

                    worker->start = std::chrono::high_resolution_clock::now();
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
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE ALTITUDE", "feet", SIMCONNECT_DATATYPE_FLOAT64);
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE LATITUDE", "degrees", SIMCONNECT_DATATYPE_FLOAT64);
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE LONGITUDE", "degrees", SIMCONNECT_DATATYPE_FLOAT64);
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE PITCH DEGREES", "degrees", SIMCONNECT_DATATYPE_FLOAT32);
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE BANK DEGREES", "degrees", SIMCONNECT_DATATYPE_FLOAT32);
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE HEADING DEGREES TRUE", "degrees", SIMCONNECT_DATATYPE_FLOAT32);
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "VELOCITY BODY Z", "feet per second", SIMCONNECT_DATATYPE_FLOAT32);
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "VELOCITY BODY Y", "feet per second", SIMCONNECT_DATATYPE_FLOAT32);
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "VELOCITY BODY X", "feet per second", SIMCONNECT_DATATYPE_FLOAT32);
        
        //Request Data
        if(FAILED(hr))
        {
            LogData("Failed to Request Data");
        }

        start = std::chrono::high_resolution_clock::now();

        while (quit == 0)
        {
            hr = SimConnect_RequestDataOnSimObject(manager.GetHandle(), REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

            
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