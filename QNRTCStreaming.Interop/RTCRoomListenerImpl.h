#pragma once
#include "RTCRoomListener.h";

namespace QNRTCStreaming
{
	namespace Interop
	{
		class RTCRoomListenerImpl : public QNRTCRoom::QNRTCRoomListener
		{
		public:
			RTCRoomListenerImpl(RTCRoomListener^ callback);

			// Í¨¹ý QNRTCRoomListener ¼Ì³Ð
			virtual void OnStateChanged(RoomState status_) override;
			virtual void OnJoinResult(int32_t error_code_, const std::string & error_str_, const UserDataInfoVec & user_data_vec_) override;
			virtual void OnLeave(int32_t error_code_, const std::string & error_str_, const std::string & kicker_user_id_) override;
			virtual void OnRemoteUserJoin(const std::string & user_id_, const std::string & user_data_) override;
			virtual void OnRemoteUserLeave(const std::string & user_id_, int32_t error_code_) override;
			virtual void OnRemotePublish(const std::string & user_id_, bool enable_audio_, bool enable_video_) override;
			virtual void OnRemoteUnPublish(const std::string & user_id_) override;
			virtual void OnLocalPublishResult(int32_t error_code_, const std::string & error_str_) override;
			virtual void OnSubscribeResult(const std::string & user_id_, int32_t error_code_, const std::string & error_str_) override;
			virtual void OnKickoutResult(const std::string & user_id_, int32_t error_code_, const std::string & error_str_) override;
			virtual void OnRemoteStreamMute(const std::string & user_id_, bool mute_audio_, bool mute_video_) override;
			virtual void OnError(int32_t error_code_, const std::string & error_str_) override;
			virtual void OnStatisticsUpdated(const StatisticsReport & statistics_) override;
			RTCRoomListener^ GetCallback();
		private:
			gcroot<RTCRoomListener^> _callback;
		};
	}
}