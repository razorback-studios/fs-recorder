#include <QObject>
#include <QTimer>
#include <QThread>

#include "../SimConnectClient/SimConnectManager.hpp"
#include "../SimConnectClient/SimConnectWorker.hpp"
#include "../Logger/Logger.hpp"

class SimConnectBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ GetIsConnected WRITE SetIsConnected NOTIFY connectionChanged)
    Q_PROPERTY(bool isRecording READ GetIsRecording WRITE SetIsRecording NOTIFY recordingChanged)

public:
    explicit SimConnectBridge(QObject *parent = nullptr);
    ~SimConnectBridge();

    //Accessors
    bool GetIsConnected() { return m_isConnected; }
    void SetIsConnected(bool value) { m_isConnected = value;  emit connectionChanged(); }
    bool GetIsRecording() { return m_isRecording; }
    void SetIsRecording(bool value) { m_isRecording = value; emit recordingChanged(); }

public slots:
    void TryConnection();
    void StartRecording();
    void StopRecording();
    void SaveCSV(const QString& destFolder, const QString& tmpFile, const QString& fileName);

signals:
    void connectionChanged();
    void recordingChanged();

private:
    bool m_isConnected;
    bool m_isRecording;
    SimConnectWorker* m_worker = nullptr;
    std::thread m_workerThread;
    QTimer* m_timer;
};