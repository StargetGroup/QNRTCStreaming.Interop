#include "stdafx.h"
#include "RTCAudio.h"

using namespace QNRTCStreaming::Interop;

RTCAudio::RTCAudio()
{
}

int RTCAudio::GetAudioDeviceCount(RTCAudioDeviceType deviceType)
{
	auto device_type_ = (AudioDeviceInfo::AudioDeviceType)deviceType;
	return Entity->GetAudioDeviceCount(device_type_);
}

int RTCAudio::GetAudioDeviceInfo(RTCAudioDeviceType deviceType, int deviceIndex, [Out] RTCAudioDeviceInfo^% audioInfo)
{
	auto device_type_ = (AudioDeviceInfo::AudioDeviceType)deviceType;
	AudioDeviceInfo audio_info_;
	auto result_ = Entity->GetAudioDeviceInfo(device_type_, deviceIndex, __out audio_info_);
	if (result_ == 0)
	{
		RTCAudioDeviceInfo^ a = gcnew RTCAudioDeviceInfo;
		a->DeviceType = (RTCAudioDeviceType)audio_info_.device_type;
		a->DeviceId = DataConvertUtil::CharPtrToSystemString(audio_info_.device_id);
		a->DeviceName = DataConvertUtil::CharPtrToSystemString(audio_info_.device_name);
		a->DeviceIndex = audio_info_.device_index;
		audioInfo = a;
	}

	return result_;
}

array<RTCAudioDeviceInfo^>^ RTCAudio::GetRecordingDevices()
{
	auto count = GetAudioDeviceCount(RTCAudioDeviceType::adt_record);
	auto list = gcnew array<RTCAudioDeviceInfo^>(count);
	for (int i = 0; i < count; i++)
	{
		RTCAudioDeviceInfo^ audioInfo;
		auto result_ = GetAudioDeviceInfo(RTCAudioDeviceType::adt_record, i, __out audioInfo);
		if (result_ == 0)
		{
			list[i] = audioInfo;
		}
	}
	return list;
}

array<RTCAudioDeviceInfo^>^ RTCAudio::GetPlayoutDevices()
{
	auto count = GetAudioDeviceCount(RTCAudioDeviceType::adt_playout);
	auto list = gcnew array<RTCAudioDeviceInfo^>(count);
	for (int i = 0; i < count; i++)
	{
		RTCAudioDeviceInfo^ audioInfo;
		auto result_ = GetAudioDeviceInfo(RTCAudioDeviceType::adt_playout, i, __out audioInfo);
		if (result_ == 0)
		{
			list[i] = audioInfo;
		}
	}
	return list;
}

void RTCAudio::SetAudioListener(RTCAudioListener ^ listener)
{
	RTCAudioListenerImpl* impl = new RTCAudioListenerImpl(listener);
	Entity->SetAudioListener(impl);
}

RTCAudioListener^ RTCAudio::GetAudioListener()
{
	auto audio_listener_ = Entity->GetAudioListener();
	auto impl = dynamic_cast<RTCAudioListenerImpl*>(audio_listener_);
	return impl->GetCallback();
}

int RTCAudio::SetRecordingDevice(RTCAudioDeviceSetting^ recordingDeviceSetting)
{
	AudioDeviceSetting recording_device_setting;
	recording_device_setting.device_index = recordingDeviceSetting->DeviceIndex;
	recording_device_setting.device_type = (AudioDeviceSetting::WindowsDeviceType)recordingDeviceSetting->DeviceType;
	return Entity->SetRecordingDevice(recording_device_setting);
}

int RTCAudio::SetPlayoutDevice(RTCAudioDeviceSetting^ recordingDeviceSetting)
{
	AudioDeviceSetting recording_device_setting;
	recording_device_setting.device_index = recordingDeviceSetting->DeviceIndex;
	recording_device_setting.device_type = (AudioDeviceSetting::WindowsDeviceType)recordingDeviceSetting->DeviceType;
	return Entity->SetPlayoutDevice(recording_device_setting);
}

int RTCAudio::GetAudioVolume(RTCAudioDeviceType deviceType)
{
	auto device_type_ = (AudioDeviceInfo::AudioDeviceType)deviceType;
	return Entity->GetAudioVolume(device_type_);
}

int RTCAudio::SetAudioVolume(RTCAudioDeviceType deviceType, int volume)
{
	auto device_type_ = (AudioDeviceInfo::AudioDeviceType)deviceType;
	return Entity->SetAudioVolume(device_type_, volume);
}

int RTCAudio::SetLocalAudioVolume(System::String^ userId, double volume)
{
	auto user_id_ = DataConvertUtil::SystemStringToStdString(userId);
	return Entity->SetAudioVolume(user_id_, volume);
}

int RTCAudio::SetAudioMuteFlag(RTCAudioDeviceType deviceType, bool muteFlag)
{
	auto device_type_ = (AudioDeviceInfo::AudioDeviceType)deviceType;
	return Entity->SetAudioMuteFlag(device_type_, muteFlag);
}

bool RTCAudio::GetAudioMuteFlag(RTCAudioDeviceType deviceType)
{
	auto device_type_ = (AudioDeviceInfo::AudioDeviceType)deviceType;
	return Entity->GetAudioMuteFlag(device_type_);
}

int RTCAudio::EnableAudioFakeInput(bool enableFlag)
{
	return Entity->EnableAudioFakeInput(enableFlag);
}

int RTCAudio::InputAudioFrame(System::IntPtr audioData, int dataSize, int bitsPerSample, int sampleRate, int numberOfChannels, int numberOfFrames)
{
	auto audio_data_ = (const unsigned char*)audioData.ToPointer();
	return Entity->InputAudioFrame(audio_data_, dataSize, bitsPerSample, sampleRate, numberOfChannels, numberOfFrames);
}

bool RTCAudio::IsEnableAudioFakeInput()
{
	return Entity->IsEnableAudioFakeInput();
}

int RTCAudio::GetAudioLevel(System::String^ userId)
{
	auto user_id_ = DataConvertUtil::SystemStringToStdString(userId);
	return Entity->GetAudioLevel(user_id_);
}

//int RTCAudio::SetAECOption(RTCAECOption aecOption)
//{
//	auto aec_option_ = (AECOption)aecOption;
//	return Entity->SetAECOption(aec_option_);
//}

int RTCAudio::MixDesktopAudio(bool enable, float volumeScaleRatio)
{
	return Entity->MixDesktopAudio(enable, volumeScaleRatio);
}