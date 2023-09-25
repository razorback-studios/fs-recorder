#include <QObject>
#include <QTimer>

#include "../SimConnectClient/SimConnectManager.hpp"
#include "../SimConnectClient/SimConnectWorker.hpp"
#include "../Logger/Logger.hpp"

class SimConnectBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ GetIsConnected WRITE SetIsConnected NOTIFY connectionChanged)

public:
    explicit SimConnectBridge(QObject *parent = nullptr);
    ~SimConnectBridge();
    bool GetIsConnected() { return m_isConnected; }
    void SetIsConnected(bool value) { m_isConnected = value; }

public slots:
    void TryConnection();
    void StartRecording();

signals:
    void connectionChanged();

private:
    bool m_isConnected;
    SimConnectWorker* m_worker = nullptr;
    QTimer* m_timer;
};