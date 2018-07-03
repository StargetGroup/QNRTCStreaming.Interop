#pragma once
#include "RTCRoomStateChangedEventArgs.h"
#include "RTCRoomJoinResultEventArgs.h"
#include "RTCRoomLeaveEventArgs.h"
#include "RTCRoomRemoteUserJoinEventArgs.h"
#include "RTCRoomRemoteUserLeaveEventArgs.h"
#include "RTCRoomRemotePublishEventArgs.h"
#include "RTCRoomRemoteUnPublishEventArgs.h"
#include "RTCRoomLocalPublishResultEventArgs.h"
#include "RTCRoomSubscribeResultEventArgs.h"
#include "RTCRoomKickoutResultEventArgs.h"
#include "RTCRoomRemoteStreamMuteEventArgs.h"
#include "RTCRoomErrorEventArgs.h"
#include "RTCRoomStatisticsUpdatedEventArgs.h"
#include "RTCRoomLocalStreamMuteEventArgs.h"
#include "RTCRoomLocalUnPublishEventArgs.h"

using namespace System;
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomListener
		{
		public:
			RTCRoomListener();
			event EventHandler<RTCRoomStateChangedEventArgs^>^ RoomStateChanged;
			void RaiseRoomStateChanged(RTCRoomStateChangedEventArgs^ e);

			event EventHandler<RTCRoomJoinResultEventArgs^>^ JoinResult;
			void RaiseJoinResult(RTCRoomJoinResultEventArgs^ e);

			event EventHandler<RTCRoomLeaveEventArgs^>^ Leave;
			void RaiseLeave(RTCRoomLeaveEventArgs^ e);

			event EventHandler<RTCRoomRemoteUserJoinEventArgs^>^ RemoteUserJoin;
			void RaiseRemoteUserJoin(RTCRoomRemoteUserJoinEventArgs^ e);

			event EventHandler<RTCRoomRemoteUserLeaveEventArgs^>^ RemoteUserLeave;
			void RaiseRemoteUserLeave(RTCRoomRemoteUserLeaveEventArgs^ e);

			event EventHandler<RTCRoomRemotePublishEventArgs^>^ RemotePublish;
			void RaiseRemotePublish(RTCRoomRemotePublishEventArgs^ e);

			event EventHandler<RTCRoomRemoteUnPublishEventArgs^>^ RemoteUnPublish;
			void RaiseRemoteUnPublish(RTCRoomRemoteUnPublishEventArgs^ e);

			event EventHandler<RTCRoomLocalPublishResultEventArgs^>^ LocalPublishResult;
			void RaiseLocalPublishResult(RTCRoomLocalPublishResultEventArgs^ e);

			event EventHandler<RTCRoomSubscribeResultEventArgs^>^ SubscribeResult;
			void RaiseSubscribeResult(RTCRoomSubscribeResultEventArgs^ e);

			event EventHandler<RTCRoomKickoutResultEventArgs^>^ KickoutResult;
			void RaiseKickoutResult(RTCRoomKickoutResultEventArgs^ e);

			event EventHandler<RTCRoomRemoteStreamMuteEventArgs^>^ RemoteStreamMute;
			void RaiseRemoteStreamMute(RTCRoomRemoteStreamMuteEventArgs^ e);

			event EventHandler<RTCRoomErrorEventArgs^>^ Error;
			void RaiseError(RTCRoomErrorEventArgs^ e);

			event EventHandler<RTCRoomStatisticsUpdatedEventArgs^>^ StatisticsUpdated;
			void RaiseStatisticsUpdated(RTCRoomStatisticsUpdatedEventArgs^ e);

			event EventHandler<RTCRoomLocalStreamMuteEventArgs^>^ LocalStreamMute;
			void RaiseLocalStreamMute(RTCRoomLocalStreamMuteEventArgs^ e);

			event EventHandler<RTCRoomLocalUnPublishEventArgs^>^ LocalUnPublish;
			void RaiseLocalUnPublish(RTCRoomLocalUnPublishEventArgs^ e);
			
		};
	}
}