#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public enum class RTCAudioDeviceState
		{
			//new audio device is activated
			Active = 0x00000001,
			//the audio device is disabled
			Disabled = 0x00000002,
			//the audio device is not present
			Notpresent = 0x00000004,
			//the audio device is unplugged
			Unplugged = 0x00000008,
			//includes all states: active, disabled, not present, and unplugged
			MASK_ALL = 0x0000000F
		};
	}
}
