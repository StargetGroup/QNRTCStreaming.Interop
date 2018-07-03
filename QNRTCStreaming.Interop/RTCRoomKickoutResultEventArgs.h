#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomKickoutResultEventArgs
		{
		public:
			property System::String^ UserId;
			property int ErrorCode;
			property System::String^ ErrorMsg;
		};
	}
}
