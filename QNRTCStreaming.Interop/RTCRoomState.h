#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public enum class RTCRoomState
		{
			rs_idle,            // Idle, not connected
			rs_connecting,      // Connecting
			rs_connected,       // Connected
			rs_reconnecting,    // disconnected and reconnecting
		};
	}
}
