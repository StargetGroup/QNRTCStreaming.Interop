#pragma once
#include "RTCAudioPCMFrameEventArgs.h"
#include "RTCAudioDeviceStateChangedEventArgs.h"

using namespace System;
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCAudioListener
		{
		public:
			RTCAudioListener();
			/** Audio frames callback
			* @param [in] audio_data_
			*        pointer to audio pcm data
			* @param [in] bits_per_sample_
			*        how many bits contained per sample
			* @param [in] sample_rate_
			*        audio sample rate, unit: HZ
			* @param [in] number_of_channels_
			*        audio channels number
			* @param [in] number_of_frames_
			*        how many audio samples are included in the data
			* @param [in] user_id_
			*        user id of this audio source, if empty, data after mixing remote
			*/
			event EventHandler<RTCAudioPCMFrameEventArgs^>^ AudioPCMFrame;
			void RaiseAudioPCMFrame(RTCAudioPCMFrameEventArgs^ e);

			event EventHandler<RTCAudioDeviceStateChangedEventArgs^>^ AudioDeviceStateChanged;
			void RaiseAudioDeviceStateChanged(RTCAudioDeviceStateChangedEventArgs^ e);
		};
	}
}