#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public enum class RTCVideoDeviceState
		{
			vds_active = 0x00000001,           //new video device is activated
			vds_lost = 0x00000002,           //the video device is lost
		};

	}
}