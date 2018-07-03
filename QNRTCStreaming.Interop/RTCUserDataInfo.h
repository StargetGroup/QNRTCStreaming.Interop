#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref struct RTCUserDataInfo
		{
		public:
			RTCUserDataInfo();

			System::String^ UserId;
			bool AudioPublished;
			bool VideoPublished;
			bool AudioMute;
			bool VideoMute;
			System::String^ ToString() override;
		};
	}
}