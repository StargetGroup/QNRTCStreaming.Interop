#include "stdafx.h"
#include "RTCAudioListenerImpl.h"

using namespace QNRTCStreaming::Interop;
QNRTCStreaming::Interop::RTCAudioListenerImpl::RTCAudioListenerImpl(RTCAudioListener ^ callback)
{
	_callback = callback;
}

RTCAudioListener^ RTCAudioListenerImpl::GetCallback()
{
	return this->_callback;
}

void QNRTCStreaming::Interop::RTCAudioListenerImpl::OnAudioPCMFrame(const void * audio_data_, int bits_per_sample_, int sample_rate_, size_t number_of_channels_, size_t number_of_frames_, const std::string & user_id_)
{
	RTCAudioPCMFrameEventArgs^ args = gcnew RTCAudioPCMFrameEventArgs;
	args->AudioData = System::IntPtr((void*)audio_data_);
	args->BitsPerSample = bits_per_sample_;
	args->SampleRate = sample_rate_;
	args->ChannelsCount = number_of_channels_;
	args->FramesCount = number_of_frames_;
	_callback->RaiseAudioPCMFrame(args);
}

void QNRTCStreaming::Interop::RTCAudioListenerImpl::OnAudioDeviceStateChanged(AudioDeviceState device_state_, const std::string & device_guid_)
{
	RTCAudioDeviceStateChangedEventArgs^ args = gcnew RTCAudioDeviceStateChangedEventArgs();
	args->DeviceState = (RTCAudioDeviceState)device_state_;
	args->DeviceId = DataConvertUtil::StdStringToSystemString(device_guid_);

	_callback->RaiseAudioDeviceStateChanged(args);
}
