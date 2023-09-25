#include <iostream>
#include <mmdeviceapi.h>
#include <Windows.h>
#include <atlbase.h>
#include <Functiondiscoverykeys_devpkey.h>

#include <vector>

#include "AudioDevice.h"
#include "CaptureSession.h"

auto main() -> int {
    FSR::Sound::CaptureSession session;
    session.Initialize();

    std::vector<FSR::Sound::AudioDevice> devices = session.GetCaptureDevices();
    std::cout << "Found " << devices.size() << " devices" << std::endl;

    for (auto& device : devices) {
        std::wcout << device.GetFriendlyName() << std::endl;
    }

    return S_OK;
}