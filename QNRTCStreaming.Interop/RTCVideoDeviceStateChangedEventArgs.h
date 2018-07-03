#pragma once
#include "RTCVideoDeviceState.h"
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCVideoDeviceStateChangedEventArgs
		{
		public:
			property RTCVideoDeviceState DeviceState;
			property System::String^ DeviceName;
		};

	}
}