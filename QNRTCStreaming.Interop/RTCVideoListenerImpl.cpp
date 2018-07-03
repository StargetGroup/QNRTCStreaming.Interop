#include "stdafx.h"
#include "RTCVideoListenerImpl.h"

using namespace QNRTCStreaming::Interop;
RTCVideoListenerImpl::RTCVideoListenerImpl(RTCVideoListener^ callback)
{
	_callback = callback;
}

RTCVideoListener^ RTCVideoListenerImpl::GetCallback()
{
	return this->_callback;
}

void RTCVideoListenerImpl::OnVideoFrame(const unsigned char * raw_data_, int data_len_, int width_,
	int height_, qiniu::VideoCaptureType video_type_, const std::string & user_id_)
{
	RTCVideoFrameEventArgs^ args = gcnew RTCVideoFrameEventArgs;
	args->RawData = System::IntPtr((void*)raw_data_);
	args->DataLength = data_len_;
	args->Width = width_;
	args->Height = height_;
	args->VideoType = (RTCVideoCaptureType)video_type_;
	args->UserId = DataConvertUtil::StdStringToSystemString(user_id_);

	_callback->RaiseVideoFrame(args);
}

void RTCVideoListenerImpl::OnVideoDeviceStateChanged(VideoDeviceState device_state_, const std::string & device_name_)
{
	RTCVideoDeviceStateChangedEventArgs^ args = gcnew RTCVideoDeviceStateChangedEventArgs;
	args->DeviceState = (RTCVideoDeviceState)device_state_;
	args->DeviceName = DataConvertUtil::StdStringToSystemString(device_name_);

	_callback->RaiseVideoDeviceStateChanged(args);
}