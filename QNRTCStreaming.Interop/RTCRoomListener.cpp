#include "stdafx.h"
#include "RTCRoomListener.h"

using namespace QNRTCStreaming::Interop;
RTCRoomListener::RTCRoomListener()
{

}

void RTCRoomListener::RaiseRoomStateChanged(RTCRoomStateChangedEventArgs^ e)
{
	this->RoomStateChanged(this, e);
}

void RTCRoomListener::RaiseJoinResult(RTCRoomJoinResultEventArgs^ e)
{
	this->JoinResult(this, e);
}

void RTCRoomListener::RaiseLeave(RTCRoomLeaveEventArgs^ e)
{
	this->Leave(this, e);
}

void RTCRoomListener::RaiseRemoteUserJoin(RTCRoomRemoteUserJoinEventArgs^ e)
{
	this->RemoteUserJoin(this, e);
}

void RTCRoomListener::RaiseRemoteUserLeave(RTCRoomRemoteUserLeaveEventArgs^ e)
{
	this->RemoteUserLeave(this, e);
}

void RTCRoomListener::RaiseRemotePublish(RTCRoomRemotePublishEventArgs^ e)
{
	this->RemotePublish(this, e);
}

void RTCRoomListener::RaiseRemoteUnPublish(RTCRoomRemoteUnPublishEventArgs^ e)
{
	this->RemoteUnPublish(this, e);
}

void RTCRoomListener::RaiseLocalPublishResult(RTCRoomLocalPublishResultEventArgs^ e)
{
	this->LocalPublishResult(this, e);
}

void RTCRoomListener::RaiseSubscribeResult(RTCRoomSubscribeResultEventArgs^ e)
{
	this->SubscribeResult(this, e);
}

void RTCRoomListener::RaiseKickoutResult(RTCRoomKickoutResultEventArgs^ e)
{
	this->KickoutResult(this, e);
}

void RTCRoomListener::RaiseRemoteStreamMute(RTCRoomRemoteStreamMuteEventArgs^ e)
{
	this->RemoteStreamMute(this, e);
}

void RTCRoomListener::RaiseError(RTCRoomErrorEventArgs^ e)
{
	this->Error(this, e);
}

void RTCRoomListener::RaiseStatisticsUpdated(RTCRoomStatisticsUpdatedEventArgs^ e)
{
	this->StatisticsUpdated(this, e);
}

void RTCRoomListener::RaiseLocalStreamMute(RTCRoomLocalStreamMuteEventArgs^ e)
{
	this->LocalStreamMute(this, e);
}

void RTCRoomListener::RaiseLocalUnPublish(RTCRoomLocalUnPublishEventArgs^ e)
{
	this->LocalUnPublish(this, e);
}