#pragma once

#include <iostream>
#include <fstream>
#include <ctime>

class Logger
{
public:
    static Logger& Instance();
    void Log(std::string message);

    ~Logger();

private:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    std::ofstream m_file;

};