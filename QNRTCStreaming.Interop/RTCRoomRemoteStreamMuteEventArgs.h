#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomRemoteStreamMuteEventArgs
		{
		public:
			property System::String^ UserId;
			property bool MuteAudio;
			property bool MuteVideo;
		};
	}
}
