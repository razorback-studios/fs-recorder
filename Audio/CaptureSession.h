#pragma once

#include <vector>

#include <Windows.h>
#include <mmdeviceapi.h>
#include <atlbase.h>

#include "AudioDevice.h"

namespace FSR::Sound {
    class CaptureSession {
    public:
        ~CaptureSession();

        auto Initialize() -> void;
        auto GetCaptureDevices() -> std::vector<AudioDevice>; // TODO: Create a device class to represent a capture device (render device as well?)
        auto CreateAudioSession();

        auto GetRawEnumerator() -> CComPtr<IMMDeviceEnumerator>;

    private:
        CComPtr<IMMDeviceEnumerator> enumerator;

        bool initialized = false;
    };
}