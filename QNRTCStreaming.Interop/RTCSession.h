#pragma once
#include "RTCRoom.h"
#include "RTCAudio.h"
#include "RTCVideo.h"
#include "RTCSessionUserStateChangedEventArgs.h"

namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCSession
		{
		public:
			RTCSession();
			void Init();
			property RTCRoom^ Room;
			property RTCAudio^ Audio;
			property RTCVideo^ Video;
			property RTCRoomListener^ RoomListener;
			property RTCAudioListener^ AudioListener;
			property RTCVideoListener^ VideoListener;

			property System::Collections::Generic::List<RTCUserDataInfo^>^ Users;

			event EventHandler<RTCSessionUserStateChangedEventArgs^>^ UserStateChanged;
			void RaiseUserStateChanged(RTCSessionUserStateChangedEventArgs^ e);

			RTCUserDataInfo^ GetUserById(System::String^ userId);

		private:
			void RTCSession::OnRoomJoinResult(System::Object^ sender, RTCRoomJoinResultEventArgs^ e);
			void RTCSession::OnRoomLeave(System::Object^ sender, RTCRoomLeaveEventArgs^ e);
			void RTCSession::OnRoomLocalPublishResult(System::Object^ sender, RTCRoomLocalPublishResultEventArgs^ e);
			void RTCSession::OnRoomRemoteUserJoin(System::Object^ sender, RTCRoomRemoteUserJoinEventArgs^ e);
			void RTCSession::OnRoomRemoteUserLeave(System::Object^ sender, RTCRoomRemoteUserLeaveEventArgs^ e);
			void RTCSession::OnRoomRemotePublish(System::Object^ sender, RTCRoomRemotePublishEventArgs^ e);
			void RTCSession::OnRoomRemoteUnPublish(System::Object^ sender, RTCRoomRemoteUnPublishEventArgs^ e);
			void RTCSession::OnRoomRemoteStreamMute(System::Object^ sender, RTCRoomRemoteStreamMuteEventArgs^ e);
			void RTCSession::OnRoomLocalStreamMute(System::Object^ sender, RTCRoomLocalStreamMuteEventArgs^ e);
			void RTCSession::OnRoomLocalUnPublish(System::Object^ sender, RTCRoomLocalUnPublishEventArgs^ e);
		};
	}
}
