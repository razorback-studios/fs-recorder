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

void CSVHandler::WriteCSV(std::string data)
{
    m_csv << data << std::endl;
}