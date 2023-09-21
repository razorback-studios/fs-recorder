#pragma once
#include <QObject>
#include <QString>

class Recording : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRecording READ getIsRecording NOTIFY isRecordingChanged)
    Q_PROPERTY(QString status READ getStatus NOTIFY isStatusChanged)

public:
    explicit Recording(QObject *parent = nullptr);

    bool getIsRecording();
    QString getStatus();

public slots:
    void handleRecordStart();
    void handleRecordStop();

signals:
    void isRecordingChanged();
    void isStatusChanged();

private:
    QString m_name;
    bool m_isRecording;
    QString m_status;
};