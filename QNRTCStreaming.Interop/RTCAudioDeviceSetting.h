#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public enum class RTCWindowsDeviceType
		{
			wdt_DefaultCommunicationDevice = -1,
			wdt_DefaultDevice = -2
		};
		
		public ref class RTCAudioDeviceSetting
		{
		public:
			RTCAudioDeviceSetting();
			property int DeviceIndex;   //speaker or playout device index
			property RTCWindowsDeviceType DeviceType;
		};
	}
}
