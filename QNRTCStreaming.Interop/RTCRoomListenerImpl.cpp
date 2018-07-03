#include "stdafx.h"
#include "RTCRoomListenerImpl.h"

using namespace QNRTCStreaming::Interop;

RTCRoomListenerImpl::RTCRoomListenerImpl(RTCRoomListener^ callback)
{
	_callback = callback;
}

RTCRoomListener^ RTCRoomListenerImpl::GetCallback()
{
	return this->_callback;
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnStateChanged(RoomState status_)
{
	RTCRoomStateChangedEventArgs^ args = gcnew RTCRoomStateChangedEventArgs;
	args->State = (RTCRoomState)status_;
	_callback->RaiseRoomStateChanged(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnJoinResult(int32_t error_code_, const std::string & error_str_, const UserDataInfoVec & user_data_vec_)
{
	RTCRoomJoinResultEventArgs^ args = gcnew RTCRoomJoinResultEventArgs();
	args->ErrorCode = error_code_;
	args->ErrorMsg = DataConvertUtil::StdStringToSystemString(error_str_);

	int size = user_data_vec_.size();
	args->Users = gcnew array<RTCUserDataInfo^>(size);

	for (int i = 0; i < size; i++)
	{
		UserDataInfo userData = user_data_vec_[i];
		RTCUserDataInfo^ info = gcnew RTCUserDataInfo();

		info->UserId = DataConvertUtil::StdStringToSystemString(userData.user_id);
		info->AudioPublished = userData.audio_published;
		info->VideoPublished = userData.video_published;
		info->AudioMute = userData.audio_mute;
		info->VideoMute = userData.video_mute;
		args->Users[i] = info;
	}

	_callback->RaiseJoinResult(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnLeave(int32_t error_code_, const std::string & error_str_, const std::string & kicker_user_id_)
{
	RTCRoomLeaveEventArgs^ args = gcnew RTCRoomLeaveEventArgs();
	args->ErrorCode = error_code_;
	args->ErrorMsg = DataConvertUtil::StdStringToSystemString(error_str_);
	args->KickerUserId = DataConvertUtil::StdStringToSystemString(kicker_user_id_);
	_callback->RaiseLeave(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnRemoteUserJoin(const std::string & user_id_, const std::string & user_data_)
{
	RTCRoomRemoteUserJoinEventArgs^ args = gcnew RTCRoomRemoteUserJoinEventArgs();
	args->UserId = DataConvertUtil::StdStringToSystemString(user_id_);
	args->UserData = DataConvertUtil::StdStringToSystemString(user_data_);
	_callback->RaiseRemoteUserJoin(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnRemoteUserLeave(const std::string & user_id_, int32_t error_code_)
{
	RTCRoomRemoteUserLeaveEventArgs^ args = gcnew RTCRoomRemoteUserLeaveEventArgs();
	args->UserId = DataConvertUtil::StdStringToSystemString(user_id_);
	args->ErrorCode = error_code_;
	_callback->RaiseRemoteUserLeave(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnRemotePublish(const std::string & user_id_, bool enable_audio_, bool enable_video_)
{
	RTCRoomRemotePublishEventArgs^ args = gcnew RTCRoomRemotePublishEventArgs();
	args->UserId = DataConvertUtil::StdStringToSystemString(user_id_);
	args->EnableAudio = enable_audio_;
	args->EnableVideo = enable_video_;
	_callback->RaiseRemotePublish(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnRemoteUnPublish(const std::string & user_id_)
{
	RTCRoomRemoteUnPublishEventArgs^ args = gcnew RTCRoomRemoteUnPublishEventArgs();
	args->UserId = DataConvertUtil::StdStringToSystemString(user_id_);
	_callback->RaiseRemoteUnPublish(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnLocalPublishResult(int32_t error_code_, const std::string & error_str_)
{
	RTCRoomLocalPublishResultEventArgs^ args = gcnew RTCRoomLocalPublishResultEventArgs();
	args->ErrorCode = error_code_;
	args->ErrorMsg = DataConvertUtil::StdStringToSystemString(error_str_);
	_callback->RaiseLocalPublishResult(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnSubscribeResult(const std::string & user_id_, int32_t error_code_, const std::string & error_str_)
{
	RTCRoomSubscribeResultEventArgs^ args = gcnew RTCRoomSubscribeResultEventArgs();
	args->UserId = DataConvertUtil::StdStringToSystemString(user_id_);
	args->ErrorCode = error_code_;
	args->ErrorMsg = DataConvertUtil::StdStringToSystemString(error_str_);
	_callback->RaiseSubscribeResult(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnKickoutResult(const std::string & user_id_, int32_t error_code_, const std::string & error_str_)
{
	RTCRoomKickoutResultEventArgs^ args = gcnew RTCRoomKickoutResultEventArgs();
	args->UserId = DataConvertUtil::StdStringToSystemString(user_id_);
	args->ErrorCode = error_code_;
	args->ErrorMsg = DataConvertUtil::StdStringToSystemString(error_str_);
	_callback->RaiseKickoutResult(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnRemoteStreamMute(const std::string & user_id_, bool mute_audio_, bool mute_video_)
{
	RTCRoomRemoteStreamMuteEventArgs^ args = gcnew RTCRoomRemoteStreamMuteEventArgs();
	args->UserId = DataConvertUtil::StdStringToSystemString(user_id_);
	args->MuteAudio = mute_audio_;
	args->MuteVideo = mute_video_;
	_callback->RaiseRemoteStreamMute(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnError(int32_t error_code_, const std::string & error_str_)
{
	RTCRoomErrorEventArgs^ args = gcnew RTCRoomErrorEventArgs();
	args->ErrorCode = error_code_;
	args->ErrorMsg = DataConvertUtil::StdStringToSystemString(error_str_);
	_callback->RaiseError(args);
}

void QNRTCStreaming::Interop::RTCRoomListenerImpl::OnStatisticsUpdated(const StatisticsReport & statistics_)
{
	RTCRoomStatisticsUpdatedEventArgs^ args = gcnew RTCRoomStatisticsUpdatedEventArgs();
	args->Statistics = gcnew RTCStatisticsReport();
	args->Statistics->UserId = DataConvertUtil::StdStringToSystemString(statistics_.user_id);
	args->Statistics->AudioBitrate = statistics_.audio_bitrate;
	args->Statistics->AudioPacketLostRate = statistics_.audio_packet_lost_rate;
	args->Statistics->VideoBitrate = statistics_.video_bitrate;
	args->Statistics->VideoWidth = statistics_.video_width;
	args->Statistics->VideoHeight = statistics_.video_height;
	args->Statistics->VideoFrameRate = statistics_.video_frame_rate;
	args->Statistics->VideoPacketLostRate = statistics_.video_packet_lost_rate;
	_callback->RaiseStatisticsUpdated(args);
}
