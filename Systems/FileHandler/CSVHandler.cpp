#include "CSVHandler.hpp"

CSVHandler& CSVHandler::Instance()
{
    static CSVHandler instance;
    return instance;
}

CSVHandler::CSVHandler()
{
    Logger& logger = Logger::Instance();
    logger.Log("CSV Handler Created");

    //Open CSV
    m_csv.open("tmp.csv", std::ios_base::trunc);

    //Write header
    if(m_csv.is_open())
    {
        m_csv << "Time,Title,Altitude,Latitude,Longitude,Pitch,Bank,Heading,VelocityZ,VelocityY,VelocityX" << std::endl;
    }
    else
    {
        logger.Log("Failed to open CSV");
    }
}

CSVHandler::~CSVHandler()
{
    Logger& logger = Logger::Instance();
    logger.Log("CSV Handler Destroyed");

    //Close CSV
    m_csv.close();

    //Remove the temp file
    std::remove("tmp.csv");
}

void CSVHandler::ClearTmp()
{
    std::lock_guard<std::mutex> lock(csv_mtx);
    Logger& logger = Logger::Instance();
    logger.Log("Clearing CSV");

    //Clear the tmp file
    m_csv.close();
    m_csv.open("tmp.csv", std::ios_base::trunc);

    //Write header
    if(m_csv.is_open())
    {
        m_csv << "Time,Title,Altitude,Latitude,Longitude,Pitch,Bank,Heading,VelocityZ,VelocityY,VelocityX" << std::endl;
    }
    else
    {
        logger.Log("Failed to open CSV");
    }
}

void CSVHandler::WriteCSV(std::string data)
{
    std::lock_guard<std::mutex> lock(csv_mtx);
    Logger& logger = Logger::Instance();

    m_csv << data << std::endl;
}

bool CSVHandler::SaveCSV(const std::string destFolder, const std::string tmpFile, const std::string fileName)
{
    std::filesystem::path destPath(destFolder);
    destPath /= fileName;

    //Open tmp file
    std::ifstream tmp(tmpFile, std::ios::binary);
    if(!tmp.is_open())
    {
        Logger& logger = Logger::Instance();
        logger.Log("Failed to open tmp file");
        return false;
    }

    //Open destination file
    std::ofstream dest(destPath, std::ios::binary);
    if(!dest.is_open())
    {
        Logger& logger = Logger::Instance();
        logger.Log("Failed to open destination file");
        return false;
    }

    //Copy tmp file to destination file
    dest << tmp.rdbuf();

    //Check for error
    if(!dest.good() || !tmp.good())
    {
        Logger& logger = Logger::Instance();
        logger.Log("Failed to copy tmp file to destination file");
        return false;
    }

    return true;
}