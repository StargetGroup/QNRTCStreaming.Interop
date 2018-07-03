#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCAudioPCMFrameEventArgs
		{
		public:
			property System::IntPtr AudioData;
			property int BitsPerSample;
			property int SampleRate;
			property int ChannelsCount;
			property int FramesCount;
			property System::String^ UserId;
		};

	}
}