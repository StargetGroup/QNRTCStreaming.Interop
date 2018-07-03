#pragma once
#include "RTCVideoCaptureType.h"
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCCameraCapability
		{
		public:
			property int Width;
			property int Height;
			property int MaxFps;
			property RTCVideoCaptureType^  VideoType;
		};
	}
}
