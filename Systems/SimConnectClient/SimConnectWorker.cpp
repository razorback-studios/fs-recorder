#include "SimConnectWorker.hpp"
#include <ctime>

SimConnectWorker::SimConnectWorker()
{
    //Instance of logger
    Logger& logger = Logger::Instance();
    logger.Log("SimConnectWorker Created");
}

SimConnectWorker::~SimConnectWorker()
{
    //Log Close
    Logger& logger = Logger::Instance();
    logger.Log("SimConnectWorker Destroyed");

    //Close CSV
    m_csv.close();

    //Remove the temp file
    std::remove("tmp.csv");

    // //Close the read file if they are open
    // for(auto& file : m_readFiles)
    // {
    //     file.close();
    // }
}

void SimConnectWorker::WriteToCSV(std::string data)
{
    std::lock_guard<std::mutex> lock(csv_mtx);
    m_csv << data << std::endl;
}

void CALLBACK MyDispatchProc1(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
{

    #include "../FileHandler/CSVHandler.hpp"
    #include  "../FileHandler/CustomFileHandler.hpp"

    //Instance of file handler
    CSVHandler& csvHandler = CSVHandler::Instance();
    CustomFileHandler& customFileHandler = CustomFileHandler::Instance();

    std::shared_ptr<SimConnectWorker> worker = reinterpret_cast<std::weak_ptr<SimConnectWorker>*>(pContext)->lock();
    
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

                    //Log to csv
                    //worker->WriteToCSV(std::to_string(count) + "," + std::string(ps->title) + "," + std::to_string(ps->altitude) + "," + std::to_string(ps->latitude) + "," + std::to_string(ps->longitude) + "," + std::to_string(ps->pitch) + "," + std::to_string(ps->bank) + "," + std::to_string(ps->heading) + "," + std::to_string(ps->velocityZ) + "," + std::to_string(ps->velocityY) + "," + std::to_string(ps->velocityX));
                    
                    //Write to CSV
                    customFileHandler.WriteFile(*ps);
                    csvHandler.WriteCSV(std::to_string(count) + "," + std::string(ps->title) + "," + std::to_string(ps->altitude) + "," + std::to_string(ps->latitude) + "," + std::to_string(ps->longitude) + "," + std::to_string(ps->pitch) + "," + std::to_string(ps->bank) + "," + std::to_string(ps->heading) + "," + std::to_string(ps->velocityZ) + "," + std::to_string(ps->velocityY) + "," + std::to_string(ps->velocityX));

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

    //Logger
    Logger& logger = Logger::Instance();


    if(manager.ConnectToSim())
    {
        logger.Log("Connected to MSFS");

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
            logger.Log("Failed to Request Data");
        }

        start = std::chrono::high_resolution_clock::now();

        while (!m_quit)
        {
            logger.Log("Start");
            hr = SimConnect_RequestDataOnSimObject(manager.GetHandle(), REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

            


            if(manager.GetHandle() == NULL)
            {
                logger.Log("Handle is NULL");
            }


            SimConnect_CallDispatch(manager.GetHandle(), MyDispatchProc1, &m_self);

            logger.Log("End");

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        return;
    }
    else
    {
        logger.Log("Failed to Connect to MSFS");
    }
}

void SimConnectWorker::StageFiles(const std::vector<std::string>& files)
{
    //Instance Logger
    Logger& logger = Logger::Instance();

    //Push each file into the vector to be read
    for(const auto& file : files)
    {
        //Open the file and push it into the vector
        std::ifstream tmpfile(file, std::ios::binary);
        if(!tmpfile)
        {
            logger.Log("Failed to open file: " + file);
        }
        else
        {
            m_readFiles.push_back(std::move(tmpfile));
            logger.Log("Opened file: " + file);
        }
    }

    logger.Log("Files: " + std::to_string(m_readFiles.size()) + " Staged");

}

void SimConnectWorker::Replay()
{
    //Instance of logger
    Logger& logger = Logger::Instance();
    logger.Log("Replay Started");

    //Instance of file handler
    CustomFileHandler& customFileHandler = CustomFileHandler::Instance();

    //For each file in the vector, open it
    for(auto& file : m_readFiles)
    {
        //Open the file
        if(!file.is_open())
        {
            logger.Log("Failed to open file");
        }
        else
        {
            logger.Log("Opened file");
        }
    }
}