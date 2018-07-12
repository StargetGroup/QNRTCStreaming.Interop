#pragma once
#include "RTCAudioListener.h"
#include "RTCAudioPCMFrameEventArgs.h"
namespace QNRTCStreaming
{
	namespace Interop
	{
		class RTCAudioListenerImpl : public QNRTCAudio::QNRTCAudioListener
		{
		public:
			RTCAudioListenerImpl(RTCAudioListener^ callback);

			RTCAudioListener^ GetCallback();
		private:
			gcroot<RTCAudioListener^> _callback;

			// Í¨¹ý QNRTCAudioListener ¼Ì³Ð
			virtual void OnAudioPCMFrame(const unsigned char* audio_data_, int bits_per_sample_, int sample_rate_, size_t number_of_channels_, size_t number_of_frames_, const std::string & user_id_) override;
			virtual void OnAudioDeviceStateChanged(AudioDeviceState device_state_, const std::string & device_guid_) override;
		};

	}
}