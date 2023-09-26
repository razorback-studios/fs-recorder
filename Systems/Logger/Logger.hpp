#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <mutex>

class Logger
{
public:
    static Logger& Instance();
    void Log(std::string message);
    std::mutex mtx;

    ~Logger();

private:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    std::ofstream m_file;

};