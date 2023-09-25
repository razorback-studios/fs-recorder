#pragma once

#include "SimConnectManager.hpp"
#include <SimConnect.h>
#include <chrono>
#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <fstream>

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

static enum DATA_DEFINE_ID
{
    DEFINITION_1,
};

static enum DATA_REQUEST_ID
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
    void LogData(std::string data);
    int GetQuit() { return quit; }
    void WriteToCSV(std::string data);
    void SetQuit(int value) { quit = value; }
    std::chrono::high_resolution_clock::time_point start;

private:
    std::ofstream m_file;
    bool isConnected;
    int quit = 0;
    std::ofstream m_csv;

};