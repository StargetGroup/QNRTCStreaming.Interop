#pragma once

#include "RTCAudio.h"
#include "RTCVideo.h"
#include "RTCRoomListenerImpl.h"
#include "RTCRoomListener.h"

namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoom
		{
		public:
			RTCRoom();

			/** Get the global unique instance pointer of the QNRTCRoom interface
			* @return returns a pointer to the QNRTCRoom, or null
			*/
			static RTCRoom^ ObtainRoomInterface();

			RTCAudio^ ObtainAudioInterface();

			RTCVideo^ ObtainVideoInterface();

			/** Set the callback interface pointer for listening room message,
			*   and set it to nullptr before exiting the room
			* @param [in] listener_ptr_
			*        pointer of QNRTCRoomListener
			*/
			void SetRoomListener(RTCRoomListener^ listener);
			RTCRoomListener^ GetRoomListener();
			int JoinRoom(System::String^ roomToken);
			int LeaveRoom();
			bool IsJoined();
			System::String^ GetRoomName();
			System::String^ GetUserId();
			int Publish(bool enableAudio, bool enableVideo);
			int UnPublish();
			int Subscribe(System::String^ userId, System::IntPtr renderHwnd);
			/** Cancel subscribe to the specified user's media stream
			* @param [in] user_id_
			*        the user id that will be cancel subscribed
			* @return return 0 if success or an error code
			*/
			int UnSubscribe(System::String^ userId);
			int KickoutUser(System::String^ userId);
			/** Mute video stream
			* @param [in] muteFlag
			*         the video track black frames, can be disabled and re-enabled
			* @return return 0 if success or an error code
			*/
			int MuteAudio(bool muteFlag);

			int MuteVideo(bool muteFlag);

			property bool MuteAudioFlag;
			property bool MuteVideoFlag;
			property bool AudioPublished;
			property bool VideoPublished;

			/** Enable or disable statistics info, will got on QNRTCRoomListener::OnStatisticsUpdated
			* @param [in]periodSecond
			*        statistics period, unit: second, if 0 will no statistics info
			*/
			void EnableStatisticCallback(int periodSecond);
			/** Configuring server-side stream merge parameters
			* @param [in] userId
			*         user id
			* @param [in] posX
			*         Starting axis coordinate, origin coordinate is upper-left corner
			* @param [in] posY
			*         Start the longitudinal axis coordinates, the origin coordinates are in the upper left corner
			* @param [in] posZ
			*         Window level, 0 denotes the lowest level
			* @param [in] width
			*         The width in the canvas after this user's stream merged
			* @param [in] height
			*         The height in the canvas after this user's stream merged
			* @param [in] isVisible
			*         Visibility
			* @return return 0 if success or an error code
			*/
			int SetMergeStreamLayout(System::String^ userId,
				int posX, int posY, int posZ,
				int width, int height, bool isVisible);

			int StopMergeStream();
			System::String^ CreateRoomToken(System::String^ roomName, System::String^ userId, bool isAdmin, System::DateTime expireAt, System::String^ appId, System::String^ accessKey, System::String^ secretKey);
			System::String^ CreateTestRoomToken(System::String^ roomName, System::String^ userId, bool isAdmin);
			QNRTCRoom* Entity;

		};

	}
}