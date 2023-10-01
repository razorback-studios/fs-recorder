#include "CustomFileHandler.hpp"
#include "SimConnectWorker.hpp"

CustomFileHandler& CustomFileHandler::Instance()
{
    static CustomFileHandler instance;
    return instance;
}

CustomFileHandler::CustomFileHandler()
{
    Logger& logger = Logger::Instance();
    logger.Log("Custom File Handler Created");

    //Open CSV
    m_file.open("tmp.frc", std::ios::binary | std::ios::out | std::ios::trunc);

    if(!m_file.is_open())
    {
        logger.Log("Failed to open binary file");
    }
    else 
    {
        logger.Log("Opened binary file");
    }
}

CustomFileHandler::~CustomFileHandler()
{
    Logger& logger = Logger::Instance();
    logger.Log("Custom File Handler Destroyed");

    //Close CSV
    m_file.close();

    //Remove the temp file
    std::remove("tmp.frc");
}

void CustomFileHandler::ClearTmp()
{
    std::lock_guard<std::mutex> lock(file_mtx);
    Logger& logger = Logger::Instance();
    logger.Log("Clearing binary file");

    //Clear the tmp file
    m_file.close();
    m_file.open("data.frc", std::ios::binary, std::ios::trunc);

    if(!m_file.is_open())
    {
        logger.Log("Failed to open binary file");
    }
    else 
    {
        logger.Log("Opened binary file");
    }
}

void CustomFileHandler::WriteFile(const dataTypes& data)
{
    std::lock_guard<std::mutex> lock(file_mtx);
    Logger& logger = Logger::Instance();

    if (!m_file.is_open()) {
        logger.Log("Failed to open binary file");
        return;
    }

    //Write to file
    m_file.write(reinterpret_cast<const char*>(&data), sizeof(dataTypes));
    m_file << "\n";
}