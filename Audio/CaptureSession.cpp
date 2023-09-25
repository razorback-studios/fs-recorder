#include "CaptureSession.h"

#include <exception>

FSR::Sound::CaptureSession::~CaptureSession() { if (initialized) CoUninitialize(); }

auto FSR::Sound::CaptureSession::Initialize() -> void {
    if (initialized) return;

    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) throw std::exception("Failed to initialize the COM library");

    const CLSID MMDeviceEnumeratorCLSID = __uuidof(MMDeviceEnumerator);
    if (FAILED(enumerator.CoCreateInstance(MMDeviceEnumeratorCLSID, nullptr, CLSCTX_ALL))) throw std::exception("Failed to create the device enumerator");

    initialized = true;
}

auto FSR::Sound::CaptureSession::GetCaptureDevices() -> std::vector<AudioDevice> {
    std::vector<AudioDevice> devices;

    CComPtr<IMMDeviceCollection> collection;
    if (FAILED(enumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &collection))) throw std::exception("Failed to enumerate audio devices");

    unsigned int count;
    if (FAILED(collection->GetCount(&count))) throw std::exception("Failed to get the number of audio devices available");
    for (std::size_t index = 0; index < count; index++) {
        CComPtr<IMMDevice> internalDevice;
        if (FAILED(collection->Item(index, &internalDevice))) throw std::exception("Failed to get the audio device at the specified index");

        AudioDevice device(internalDevice);
        devices.push_back(device);
    }

    return devices;
}

auto FSR::Sound::CaptureSession::CreateAudioSession() {

}

auto FSR::Sound::CaptureSession::GetRawEnumerator() -> CComPtr<IMMDeviceEnumerator> { return enumerator; }