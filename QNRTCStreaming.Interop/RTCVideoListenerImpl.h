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

			virtual void OnVideoFrame(const unsigned char * raw_data_, int data_len_, int width_,
				int height_, qiniu::VideoCaptureType video_type_, const std::string & user_id_) override;

			/** Video frames callback when preview local camera
			* @param [in] raw_data_
			*        pointer to video frame data
			* @param [in] data_len_
			*        video frame data size
			* @param [in] width_
			*        video frame width
			* @param [in] height_
			*        video frame height
			* @param [in] video_type_
			*        video frame raw data format
			*/
			virtual void OnVideoFramePreview(
				const unsigned char* raw_data_,
				int data_len_,
				int width_,
				int height_,
				qiniu::VideoCaptureType video_type_
			) override;

			virtual void OnVideoDeviceStateChanged(VideoDeviceState device_state_, const std::string & device_name_) override;

		private:
			gcroot<RTCVideoListener^> _callback;
		};
	}
}
