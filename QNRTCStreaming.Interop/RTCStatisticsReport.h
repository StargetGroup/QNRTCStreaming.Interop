#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref struct  RTCStatisticsReport
		{
			System::String^ UserId;
			// audio parameters    
			int AudioBitrate;
			float AudioPacketLostRate;

			// video parameters
			int VideoWidth;
			int VideoHeight;
			int VideoFrameRate;
			int VideoBitrate;
			float VideoPacketLostRate;

		};
	}
}
