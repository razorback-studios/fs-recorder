#pragma once

#include "../Logger/Logger.hpp"
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

struct dataTypes;

class CustomFileHandler
{
public:
        static CustomFileHandler& Instance();
        void WriteFile(const dataTypes& data);
        void ClearTmp();
        // bool SaveFile(const std::string destFolder, const std::string tmpFile, const std::string fileName);

private:
        CustomFileHandler();
        ~CustomFileHandler();
        CustomFileHandler(const CustomFileHandler&) = delete;
        CustomFileHandler& operator=(const CustomFileHandler&) = delete;
        std::ofstream m_file;
        std::mutex file_mtx;
};