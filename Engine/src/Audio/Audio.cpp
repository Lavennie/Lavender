#include "Audio.h"
#include <MMdeviceapi.h>
#include <Mfidl.h>

namespace Lavender
{
	void Audio::Init()
	{
		IMMDeviceEnumerator* deviceEnumerator = NULL;
		const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
		const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
		HRESULT hr = CoCreateInstance(
			CLSID_MMDeviceEnumerator, NULL,
			CLSCTX_ALL, IID_IMMDeviceEnumerator,
			(LPVOID*)&deviceEnumerator);

		IMMDevice* defaultDevice = NULL;
		hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);

		//deviceEnumerator->EnumAudioEndpoints();

		//defaultDevice->
	}
}