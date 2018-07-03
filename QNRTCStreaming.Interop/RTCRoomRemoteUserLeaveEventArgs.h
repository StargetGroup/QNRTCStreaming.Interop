#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomRemoteUserLeaveEventArgs
		{
		public:
			property System::String^ UserId;
			property int ErrorCode;
		};
	}
}
