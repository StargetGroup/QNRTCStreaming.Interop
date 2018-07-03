#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomErrorEventArgs
		{
		public:
			property int ErrorCode;
			property System::String^ ErrorMsg;
		};
	}
}
