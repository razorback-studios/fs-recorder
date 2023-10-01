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
    m_file.open("data.frc", std::ios::binary | std::ios::out | std::ios::trunc);

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
    std::remove("data.frc");
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

bool CustomFileHandler::SaveFile(std::string destFolder, std::string tmpFile, std::string fileName)
{
    //if file is open, close it
    if(m_file.is_open())
    {
        m_file.close();
    }

    Logger& logger = Logger::Instance();

    std::filesystem::path destPath(destFolder);
    destPath /= fileName;

    logger.Log("tmp file path: " + tmpFile);

    if(!std::filesystem::exists(tmpFile))
    {
        logger.Log("Tmp file does not exist");
        return false;
    }

    //Open files
    std::ifstream tmp(tmpFile, std::ios::binary);
    std::ofstream dest(destPath, std::ios::binary);

    if(tmp && dest)
    {
        dest << tmp.rdbuf();
    }
    else
    {
        logger.Log("Failed to open tmp or destination file");
        return false;
    }

    //Close files
    tmp.close();
    dest.close();

    if(!std::filesystem::exists(destPath))
    {
        logger.Log("Destination file does not exist");
        return false;
    }

    return true;
}