#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomRemotePublishEventArgs
		{
		public:
			property System::String^ UserId;
			property bool EnableAudio;
			property bool EnableVideo;
		};
	}
}
