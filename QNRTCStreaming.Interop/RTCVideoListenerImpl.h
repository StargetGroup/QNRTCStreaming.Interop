#pragma once
#include "RTCVideoFrameEventArgs.h"
#include "RTCVideoCaptureType.h"
#include "RTCVideoListener.h"

namespace QNRTCStreaming
{
	namespace Interop
	{
		public class RTCVideoListenerImpl : public QNRTCVideo::QNRTCVideoListener
		{
		public:
			RTCVideoListenerImpl(RTCVideoListener^ callback);

			RTCVideoListener^ GetCallback();

			void OnVideoFrame(const unsigned char * raw_data_, int data_len_, int width_,
				int height_, qiniu::VideoCaptureType video_type_, const std::string & user_id_);

			void OnVideoDeviceStateChanged(VideoDeviceState device_state_, const std::string & device_name_);

		private:
			gcroot<RTCVideoListener^> _callback;
		};
	}
}
