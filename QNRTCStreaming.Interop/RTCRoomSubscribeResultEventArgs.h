#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomSubscribeResultEventArgs
		{
		public:
			property System::String^ UserId;
			property int ErrorCode;
			property System::String^ ErrorMsg;
		};
	}
}
