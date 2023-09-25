#pragma once

#include <string>

#include <Windows.h>
#include <atlbase.h>
#include <mmdeviceapi.h>

namespace FSR::Sound {
    class AudioDevice {
    public:
        AudioDevice(CComPtr<IMMDevice> device) : device(device) {}

        auto GetFriendlyName() -> std::wstring;

        auto GetRawDevice() -> CComPtr<IMMDevice>;
    private:
        CComPtr<IMMDevice> device;
    };
}