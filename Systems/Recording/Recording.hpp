#pragma once
#include <QObject>
#include <QString>

class Recording : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRecording READ getIsRecording NOTIFY isRecordingChanged)
    Q_PROPERTY(QString status READ getStatus)

public:
    explicit Recording(QObject *parent = nullptr);

    bool getIsRecording();
    QString getStatus();

public slots:
    void handleRecord();

signals:
    void isRecordingChanged();

private:
    QString m_name;
    bool m_isRecording;
    QString m_status;
};