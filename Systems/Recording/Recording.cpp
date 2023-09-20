#include "Recording.hpp"

Recording::Recording(QObject *parent) : QObject(parent)
{
    m_isRecording = false;
    m_status = "Not recording.";
}

bool Recording::getIsRecording()
{
    return m_isRecording;
}

QString Recording::getStatus()
{
    return m_status;
}

void Recording::handleRecord()
{
    if(!m_isRecording)
    {
        m_isRecording = true;
        m_status = "Recording...";
        emit isRecordingChanged();
    }
    else
    {
        m_isRecording = false;
        m_status = "Not Recording.";
        emit isRecordingChanged();
    }
}