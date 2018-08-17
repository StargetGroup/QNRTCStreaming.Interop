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
		public enum class RTCAECOption
		{
			aec_dmo = 0,    // dx dmo aec
			aec_google,     // google aec
		};

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

			/** Set the volume of a specified user
			* @param [in] user_id_
			*        user id
			* @param [in] volume_
			*        audio volume, 0 ~ 10
			* @return return 0 if success or an error code
			*/
			int SetAudioVolume(System::String^ userId, double volume);
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

			/** Get audio level
			* @param [in] user_id_
			*        who's audio level
			* @return 0 ~ 100£¬audio level >= 0 if success, else return -1
			*/
			int GetAudioLevel(System::String^ userId);

			/** Set Audio AEC algorithm
			* @param [in] aec_option_
			*        aec algorithm
			* @return 0 ~ 100£¬audio level >= 0 if success, else return -1
			*/
			int SetAECOption(RTCAECOption aecOption);
		};
	}
}
