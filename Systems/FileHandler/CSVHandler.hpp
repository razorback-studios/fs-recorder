#pragma once

#include "../Logger/Logger.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <mutex>

class CSVHandler
{
public:
    static CSVHandler& Instance();
    void WriteCSV(std::string data);
    void ClearTmp();
    bool SaveCSV(const std::string destFolder, const std::string tmpFile, const std::string fileName);


private:
    CSVHandler();
    ~CSVHandler();
    CSVHandler(const CSVHandler&) = delete;
    CSVHandler& operator=(const CSVHandler&) = delete;
    std::ofstream m_csv;
    std::mutex csv_mtx;
};