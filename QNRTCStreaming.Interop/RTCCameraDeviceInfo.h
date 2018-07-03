#pragma once
#include "RTCCameraCapability.h"
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCCameraDeviceInfo
		{
		public:
			property System::String^ DeviceId;
			property System::String^ DeviceName;
			property array<RTCCameraCapability^>^ Capabilitys;
		};
	}
}
