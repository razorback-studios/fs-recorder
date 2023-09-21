#include "Recording.hpp"

Recording::Recording(QObject *parent) : QObject(parent)
{
    m_isRecording = false;
    m_status = "Idle";
}

bool Recording::getIsRecording()
{
    return m_isRecording;
}

QString Recording::getStatus()
{
    return m_status;
}

void Recording::handleRecordStart()
{
    if(!m_isRecording)
    {
        m_isRecording = true;
        m_status = "Recording...";
        emit isRecordingChanged();
        emit isStatusChanged();
    }
    else
    {
        m_status = "Already Recording";
        emit isStatusChanged();
    }
}

void Recording::handleRecordStop()
{
    if(m_isRecording)
    {
        m_isRecording = false;
        m_status = "Recording Complete.";
        emit isRecordingChanged();
        emit isStatusChanged();
    }
    else
    {
        m_status = "No Recording in Progress.";
        emit isStatusChanged();
    }
}