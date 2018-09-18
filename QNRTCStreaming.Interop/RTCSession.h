#pragma once
#include "RTCEngine.h"
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
			int Init();
			int JoinRoom(System::String^ roomToken);
			int LeaveRoom();
			property RTCRoom^ Room;
			property RTCAudio^ Audio;
			property RTCVideo^ Video;
			property RTCRoomListener^ RoomListener;
			property RTCAudioListener^ AudioListener;
			property RTCVideoListener^ VideoListener;

			void Release();

			property System::Collections::Generic::List<RTCUserDataInfo^>^ Users;

			event EventHandler<RTCSessionUserStateChangedEventArgs^>^ UserStateChanged;
			void RaiseUserStateChanged(RTCSessionUserStateChangedEventArgs^ e);

			RTCUserDataInfo^ GetUserById(System::String^ userId);

			/** process video raw picture, crop or mirror
			* @param [in] src_data_
			*        pointer to source raw data
			* @param [in] src_width_
			*        source picture width
			* @param [in] src_height_
			*        source picture height
			* @param [in] src_data_size_
			*        source data size
			* @param [in] picture_fmt_
			*        source picture format, current only supported kI420
			* @param [in] mirror_flag_
			*        whether mirror source picture flag
			* @param [in] origin_x_
			*        crop x pos from top left
			* @param [in] origin_y_
			*        crop y pos from top left
			* @param [in] dest_width_
			*        crop width from source picture
			* @param [in] dest_height_
			*        crop height from source picture
			* @param [out] dest_data_
			*        dest data buffer pointer
			* @param [out] dest_data_size_
			*        dest_data_'s dest size
			* @return return 0 if success, or an error code
			*/
			int CropRawPicture(
				System::IntPtr srcData,
				int srcWidth,
				int srcHeight,
				int srcDataSize,
				RTCVideoCaptureType pictureFmt,
				bool mirrorFlag,
				int originX,
				int originY,
				int destWidth,
				int destHeight,
				__out System::IntPtr destData,
				__out int destDataSize
			);

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

			unsigned char* pCorpPictureBuffer;
			~RTCSession();
		};
	}
}
