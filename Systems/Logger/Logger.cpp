#include "Logger.hpp"

Logger& Logger::Instance()
{
    static Logger instance;
    return instance;
}

Logger::Logger()
{
    m_file.open("Log.txt", std::ios_base::trunc);
}

Logger::~Logger()
{
    m_file.close();
}

void Logger::Log(std::string message)
{
    std::unique_lock<std::mutex> lock(mtx);
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    m_file << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " - " << message << std::endl;

}