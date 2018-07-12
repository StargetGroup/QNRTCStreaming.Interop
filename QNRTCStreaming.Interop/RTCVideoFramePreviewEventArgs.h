#pragma once
#include "RTCVideoCaptureType.h"
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCVideoFramePreviewEventArgs
		{
		public:
			property System::IntPtr rawData;
			property int dataLen;
			property int width;
			property int height;
			property RTCVideoCaptureType videoType;
		};

	}
}