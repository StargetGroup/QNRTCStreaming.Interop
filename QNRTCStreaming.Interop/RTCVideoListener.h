#pragma once
#include "RTCVideoFrameEventArgs.h"
#include "RTCVideoDeviceStateChangedEventArgs.h"
#include "RTCVideoFramePreviewEventArgs.h"

namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCVideoListener
		{
		public:

			event EventHandler<RTCVideoFrameEventArgs^>^ VideoFrame;
			void RaiseVideoFrame(RTCVideoFrameEventArgs^ e);

			event EventHandler<RTCVideoFramePreviewEventArgs^>^ VideoFramePreview;
			void RaiseVideoFramePreview(RTCVideoFramePreviewEventArgs^ e);

			event EventHandler<RTCVideoDeviceStateChangedEventArgs^>^ VideoDeviceStateChanged;
			void RaiseVideoDeviceStateChanged(RTCVideoDeviceStateChangedEventArgs^ e);
		};
	}
}
