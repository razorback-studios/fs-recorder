#pragma once

#include "SimConnectManager.hpp"
#include <SimConnect.h>

#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <fstream>

struct dataTypes
{
    char title[256];
    double  altitude;
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
    void SetQuit(int value) { quit = value; }
    void isConnectedToSim();

private:
    std::ofstream m_file;
    bool isConnected;
    int quit = 0;

};