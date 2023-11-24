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

}


void CALLBACK MyDispatchProc1(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
{

    #include "../FileHandler/CSVHandler.hpp"
    #include  "../FileHandler/CustomFileHandler.hpp"
    #include "../Logger/Logger.hpp"

    //Instance of file handler
    CSVHandler& csvHandler = CSVHandler::Instance();
    CustomFileHandler& customFileHandler = CustomFileHandler::Instance();
    Logger& logger = Logger::Instance();

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
                    
                    //Write to CSV
                    customFileHandler.WriteFile(*ps);
                    csvHandler.WriteCSV(std::to_string(count) + "," + std::string(ps->title) + "," + std::to_string(ps->altitude) + "," + std::to_string(ps->latitude) + "," + std::to_string(ps->longitude) + "," + std::to_string(ps->heading) /* + "," + std::to_string(ps->pitch) + "," + std::to_string(ps->bank) + "," + std::to_string(ps->heading) + "," + std::to_string(ps->velocityZ) + "," + std::to_string(ps->velocityY) + "," + std::to_string(ps->velocityX)*/);

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
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE LATITUDE", "degrees", SIMCONNECT_DATATYPE_FLOAT64);
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE LONGITUDE", "degrees", SIMCONNECT_DATATYPE_FLOAT64);
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE ALTITUDE", "feet");
        hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE HEADING DEGREES MAGNETIC", "degrees", SIMCONNECT_DATATYPE_FLOAT64);
        // hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE PITCH DEGREES", "radians", SIMCONNECT_DATATYPE_INT32);
        // hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "PLANE BANK DEGREES", "radians", SIMCONNECT_DATATYPE_FLOAT32);
        // hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "VELOCITY BODY Z", "feet per second", SIMCONNECT_DATATYPE_FLOAT32);
        // hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "VELOCITY BODY Y", "feet per second", SIMCONNECT_DATATYPE_FLOAT32);
        // hr = SimConnect_AddToDataDefinition(manager.GetHandle(), DEFINITION_1, "VELOCITY BODY X", "feet per second", SIMCONNECT_DATATYPE_FLOAT32);
        
        //Request Data
        if(FAILED(hr))
        {
            logger.Log("Failed to Request Data");
            return;
        }

        start = std::chrono::high_resolution_clock::now();

        if(FAILED(hr))
        {
            logger.Log("Failed to Subscribe to System Event");
            return;
        };

        logger.Log("Start recording loop.");
        while (!m_quit)
        {
            hr = SimConnect_RequestDataOnSimObject(manager.GetHandle(), REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

            if(manager.GetHandle() == NULL)
            {
                logger.Log("Handle is NULL");
                return;
            }


            SimConnect_CallDispatch(manager.GetHandle(), MyDispatchProc1, &m_self);

            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }

        logger.Log("End recording loop.");

        return;
    }
    else
    {
        logger.Log("Failed to Connect to MSFS");
        return;
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
            m_readFiles.emplace_back(std::move(tmpfile));
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

    //Instance of dataTypes
    dataTypes data;

    m_initPosition = std::make_shared<SIMCONNECT_DATA_INITPOSITION>();

    //For each file in the vector, open it
    for(auto& file : m_readFiles)
    {
        //Open the file
        if(!file.is_open())
        {
            logger.Log("Failed to open file");
        }

        //Set the initial position
        if(!setInitData(data, file))
        {
            logger.Log("Failed to set initial position");
        }

        logger.Log("Init position" + std::to_string(m_initPosition->Latitude));
        logger.Log("Title: " + m_aircraftTitle);

        SpawnNewAirplane();

        //Read the file while there is still data
        while(readNextLine(data, file))
        {
            //logger.Log("Altitude: " + std::to_string(data.altitude));
        }

    }
}

void SimConnectWorker::SpawnNewAirplane()
{
    //Get reference to sim
    SimConnectManager& manager = SimConnectManager::Instance();

    Logger& logger = Logger::Instance();

    HRESULT hr;

    if(manager.ConnectToSim())
    {
        hr = SimConnect_AICreateNonATCAircraft(manager.GetHandle(), m_aircraftTitle.c_str(), "NA", *m_initPosition, REQUEST_2);

        if(FAILED(hr))
        {
            logger.Log("Failed to spawn new aircraft");
        }
        else
        {
            logger.Log("Spawned new aircraft");
        }
    }
    else
    {
        logger.Log("Failed to connect to sim");
    }
}

bool SimConnectWorker::readNextLine(dataTypes& data, std::ifstream& file)
{
    //Logger
    Logger& logger = Logger::Instance();

    if(!file.read(reinterpret_cast<char*>(&data), sizeof(dataTypes)))
    {
        if(file.eof())
        {
            //End of file reached
            return false;
        }
        else
        {
            //Other error
            logger.Log("Error reading file");
            return false;
        }
    }
    //Read was successful
    return true;

}

bool SimConnectWorker::setInitData(dataTypes& data, std::ifstream& file)
{
    //Logger
    Logger& logger = Logger::Instance();


    if(!file.read(reinterpret_cast<char*>(&data), sizeof(dataTypes)))
    {
        if(file.eof())
        {
            logger.Log("End of file reached");
            //End of file reached
            return false;
        }
        else
        {
            //Other error
            logger.Log("Error reading file");
            return false;
        }
    }

    m_initPosition->Latitude = data.latitude;
    m_initPosition->Longitude = data.longitude;
    m_initPosition->Altitude = data.altitude;
    m_initPosition->Heading = data.heading;
    m_initPosition->Pitch = 0;
    m_initPosition->Bank = 0;
    m_initPosition->OnGround = 1;
    m_initPosition->Airspeed = 0;

    m_aircraftTitle = data.title;

    logger.Log("Title: " + m_aircraftTitle);

    logger.Log("Initial Position Set");
    return true;
}