#pragma once

#include "SimConnectManager.hpp"
#include "../Logger/Logger.hpp"
#include "../FileHandler/CSVHandler.hpp"
#include "../FileHandler/CustomFileHandler.hpp"
#include <SimConnect.h>
#include <chrono>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <cstdio>
#include <filesystem>
#include <mutex>
#include <memory>
#include <utility>

#pragma pack(push, 1)
struct dataTypes
{
    //Values we need: time/lat/long/pitch/bank/heading
    char title[256];
    double  altitude;
    float  latitude;
    float  longitude;
    float pitch;
    float bank;
    float heading;
    float velocityZ;
    float velocityY;
    float velocityX;
};
#pragma pack(pop)

enum DATA_DEFINE_ID
{
    DEFINITION_1,
};

enum DATA_REQUEST_ID
{
    REQUEST_1,
    REQUEST_2,
};

class SimConnectWorker
{
public:
    SimConnectWorker();
    ~SimConnectWorker();
    void dataRequest();
    int GetQuit() { return m_quit; }
    void WriteToCSV(std::string data);
    void SetQuit(bool value) { m_quit = value; }
    void SetSelf(std::weak_ptr<SimConnectWorker> self) { m_self = self; }
    std::chrono::high_resolution_clock::time_point start;
    void StageFiles(const std::vector<std::string>& files);
    void Replay();
    std::mutex csv_mtx;

private:
    std::ofstream m_file;
    bool isConnected;
    std::ofstream m_csv;
    std::atomic<bool> m_quit{ false };
    std::weak_ptr<SimConnectWorker> m_self;
    std::vector<std::ifstream> m_readFiles;
    bool readNextLine(dataTypes& data, std::ifstream& file);
};