#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomLocalPublishResultEventArgs
		{
		public:
			property int ErrorCode;
			property System::String^ ErrorMsg;
		};
	}
}
