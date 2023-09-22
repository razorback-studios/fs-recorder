#pragma once

#include <QObject>

#include <Windows.h>
#include <SimConnect.h>

class SimConnectWorker : public QObject
{
    Q_OBJECT 

public:
    explicit SimConnectWorker(QObject *parent = nullptr);
};