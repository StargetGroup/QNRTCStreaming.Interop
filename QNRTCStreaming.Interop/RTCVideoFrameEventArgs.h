#pragma once
#include "RTCVideoCaptureType.h"
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCVideoFrameEventArgs
		{
		public:
			property System::IntPtr RawData;
			property int DataLength;
			property int Width;
			property int Height;
			property RTCVideoCaptureType VideoType;
			property System::String^ UserId;
		};
	}
}
