#pragma once

#include "../Logger/Logger.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

class CSVHandler
{
public:
    static CSVHandler& Instance();
    void WriteCSV(std::string data);

private:
    CSVHandler();
    ~CSVHandler();
    CSVHandler(const CSVHandler&) = delete;
    CSVHandler& operator=(const CSVHandler&) = delete;
    std::ofstream m_csv;
};