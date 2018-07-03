#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomRemoteUserJoinEventArgs
		{
		public:
			property System::String^ UserId;
			property System::String^ UserData;
		};
	}
}
