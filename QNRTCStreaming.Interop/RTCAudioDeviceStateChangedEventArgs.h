#pragma once
#include "RTCAudioDeviceState.h"

namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCAudioDeviceStateChangedEventArgs
		{
		public:
			property RTCAudioDeviceState DeviceState;
			property System::String^ DeviceId;
		};
	}
}
