#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public enum class RTCAudioDeviceType
		{
			adt_invalid = -1,
			adt_record,
			adt_playout,
		};

		public ref class RTCAudioDeviceInfo
		{
		public:

			property RTCAudioDeviceType DeviceType;

			property System::String^ DeviceId;

			property System::String^ DeviceName;

			property int DeviceIndex;
		};
	}
}
