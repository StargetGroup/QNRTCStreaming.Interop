#pragma once
#include "RTCAudioListener.h"
#include "RTCAudioListenerImpl.h"
#include "RTCAudioDeviceInfo.h"
#include "RTCAudioDeviceSetting.h"
using namespace System::Runtime::InteropServices;
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCAudio
		{
		public:
			RTCAudio();
			QNRTCAudio * Entity;
			int GetAudioDeviceCount(RTCAudioDeviceType deviceType);
			int GetAudioDeviceInfo(RTCAudioDeviceType deviceType, int deviceIndex, [Out] RTCAudioDeviceInfo^% audioInfo);
			array<RTCAudioDeviceInfo^>^ GetRecordingDevices();
			array<RTCAudioDeviceInfo^>^ GetPlayoutDevices();
			void SetAudioListener(RTCAudioListener^ listener);
			RTCAudioListener^ GetAudioListener();
			int SetRecordingDevice(RTCAudioDeviceSetting^ recordingDeviceSetting);
			int SetPlayoutDevice(RTCAudioDeviceSetting^ playoutDeviceSetting);
			int GetAudioVolume(RTCAudioDeviceType deviceType);
			int SetAudioVolume(RTCAudioDeviceType deviceType, int volume);
			int SetAudioMuteFlag(RTCAudioDeviceType deviceType, bool muteFlag);
			bool GetAudioMuteFlag(RTCAudioDeviceType deviceType);
			/** Enable or disable external data import feature
			* @param [in] enable_flag_
			*        true:enable, false:disable;
			* @return return 0 if success or an error code
			* @brief developer must call this method before InputAudioFrame
			*/
			int EnableAudioFakeInput(bool enableFlag);

			/** Import audio frame data when external data import feature enabled
			* @param [in] audio_data_
			*        audio frame data pointer
			* @param [in] data_size_
			*        audio frame data size
			* @param [in] bits_per_sample_
			*        how many bits contained per sample, current only supported 16 bits per sample
			* @param [in] sample_rate_
			*        audio sample rate, unit: HZ
			* @param [in] number_of_channels_
			*        audio channels number, current only supported mono and stereo channels
			* @param [in] number_of_frames_
			*        how many audio samples are included in the data.
			* @return return 0 if success or an error code
			* @brief developer must call EnableAudioFakeInput(true) first
			*/
			int InputAudioFrame(
				System::IntPtr audioData,
				int dataSize,
				int bitsPerSample,
				int sampleRate,
				int numberOfChannels,
				int numberOfFrames
			);

			bool IsEnableAudioFakeInput();
		};
	}
}
