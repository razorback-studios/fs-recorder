#include "AudioDevice.h"

#include <Functiondiscoverykeys_devpkey.h>

auto FSR::Sound::AudioDevice::GetRawDevice() -> CComPtr<IMMDevice> { return device; }

auto FSR::Sound::AudioDevice::GetFriendlyName() -> std::wstring {
    IPropertyStore* propertyStore;
    device->OpenPropertyStore(STGM_READ, &propertyStore);

    PROPVARIANT property;
    propertyStore->GetValue(PKEY_Device_FriendlyName, &property);

    std::wstring name(property.pwszVal);

    return name;
}