#include "SimConnectBridge.hpp"

SimConnectBridge::SimConnectBridge(QObject *parent) : QObject(parent)
{
    Logger& logger = Logger::Instance();

    m_isConnected = false;
    m_isRecording = false;  

    //Check that the worker is null
    if(m_worker == nullptr)
    {
        //Create new instance of that worker
        
        m_worker = std::make_shared<SimConnectWorker>();
        m_worker->SetSelf(m_worker);
        logger.Log("Instance of Worker created");
    }
    else {
        logger.Log("Worker not null.");
    }

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SimConnectBridge::TryConnection);
    m_timer->start(5000);

    logger.Log("SimConnectBridge Created");
}

SimConnectBridge::~SimConnectBridge()
{
    Logger& logger = Logger::Instance();
    logger.Log("SimConnectBridge Destroyed");

    delete m_timer;
    m_timer = nullptr;

    if(m_workerThread.joinable())
    {
        m_workerThread.join();
    }
}

void SimConnectBridge::TryConnection()
{
    SimConnectManager& manager = SimConnectManager::Instance();

    Logger& logger = Logger::Instance();

    if(manager.ConnectToSim() && m_isConnected == false)
    {
        logger.Log("Bridge found MSFS Connection");
        SetIsConnected(true);
        m_timer->stop();
    }
    else if (!manager.ConnectToSim() && m_isConnected == true) 
    {
        logger.Log("Lost MSFS connection");
        SetIsConnected(false);
    }
    else if(manager.ConnectToSim() && m_isConnected == true)
    {
        logger.Log("Bridge still connected to MSFS");
    }
    else if(!manager.ConnectToSim() && m_isConnected == false)
    {
        logger.Log("No Active MSFS Connection");
    }
}

void SimConnectBridge::StartRecording()
{
    Logger& logger = Logger::Instance();
    CSVHandler& csvHandler = CSVHandler::Instance();
    CustomFileHandler& customFileHandler = CustomFileHandler::Instance();

    if(m_isConnected && !m_isRecording) //If recording is being started
    {
        m_worker->SetQuit(false);
        SetIsRecording(true);

        csvHandler.ClearTmp();
        customFileHandler.ClearTmp();
        
        m_workerThread = std::thread([this] {m_worker->dataRequest(); });
        logger.Log("Recording Begun.");


    }
    else //If we are not connected
    {
        logger.Log("Not Connected to MSFS");
    }
}

void SimConnectBridge::StopRecording()
{
    Logger& logger = Logger::Instance();

    if(m_isRecording) //If we are already recording, regardless of connection state
    {
        logger.Log("Recording Ended.");
        SetIsRecording(false);
        m_worker->SetQuit(true);
        if(m_workerThread.joinable())
        {
            m_workerThread.join();
        }
    }
    else //If we are not connected
    {
        logger.Log("Not Connected to MSFS");
    }
}

void SimConnectBridge::SaveCSV(const QString& destFolder, const QString& tmpFile, const QString& fileName)
{
    Logger& logger = Logger::Instance();
    logger.Log("SaveFile Called");

    CustomFileHandler& CustomFileHandler = CustomFileHandler::Instance();

    std::string destFolderStr = destFolder.toStdString();
    std::string tmpFileStr = tmpFile.toStdString();
    std::string fileNameStr = fileName.toStdString();

    if(CustomFileHandler.SaveFile(destFolderStr, tmpFileStr, fileNameStr))
    {
        logger.Log("File Saved");
    }
    else
    {
        logger.Log("File Failed to Save");
    }
}

void SimConnectBridge::StageFiles()
{
    Logger& logger = Logger::Instance();
    logger.Log("StageFiles Called");

    //Create new temp vector
    std::vector<std::string> filesToOpen;

    //Add a file
    filesToOpen.push_back("C:\\Users\\w_can\\OneDrive\\Desktop\\Test\\test.frc");

    //Call the worker to stage the files
    m_worker->StageFiles(filesToOpen);
}

void SimConnectBridge::StartReplay()
{
    Logger& logger = Logger::Instance();
    logger.Log("StartReplay Called");

    m_worker->Replay();
}