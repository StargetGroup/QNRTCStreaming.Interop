#include "stdafx.h"
#include "RTCSession.h"

using namespace QNRTCStreaming::Interop;
using namespace System::Threading;
using namespace System::Linq;
using namespace System::Collections;

RTCSession::RTCSession()
{
}

void RTCSession::Init()
{
	Room = RTCRoom::ObtainRoomInterface();
	RoomListener = gcnew RTCRoomListener;
	Room->SetRoomListener(RoomListener);
	Video = Room->ObtainVideoInterface();
	VideoListener = gcnew RTCVideoListener;
	Video->SetVideoListener(VideoListener);
	Audio = Room->ObtainAudioInterface();
	AudioListener = gcnew RTCAudioListener;
	Audio->SetAudioListener(AudioListener);
	Room->EnableStatisticCallback(5);
	this->Users = gcnew System::Collections::Generic::List<RTCUserDataInfo^>;
	RoomListener->JoinResult += gcnew EventHandler<RTCRoomJoinResultEventArgs^>(this, &RTCSession::OnRoomJoinResult);
	RoomListener->Leave += gcnew EventHandler<RTCRoomLeaveEventArgs^>(this, &RTCSession::OnRoomLeave);
	RoomListener->LocalPublishResult += gcnew EventHandler<RTCRoomLocalPublishResultEventArgs^>(this, &RTCSession::OnRoomLocalPublishResult);
	RoomListener->RemoteUserJoin += gcnew EventHandler<RTCRoomRemoteUserJoinEventArgs^>(this, &RTCSession::OnRoomRemoteUserJoin);
	RoomListener->RemoteUserLeave += gcnew EventHandler<RTCRoomRemoteUserLeaveEventArgs^>(this, &RTCSession::OnRoomRemoteUserLeave);
	RoomListener->RemotePublish += gcnew EventHandler<RTCRoomRemotePublishEventArgs^>(this, &RTCSession::OnRoomRemotePublish);
	RoomListener->RemoteUnPublish += gcnew EventHandler<RTCRoomRemoteUnPublishEventArgs^>(this, &RTCSession::OnRoomRemoteUnPublish);
	RoomListener->RemoteStreamMute += gcnew EventHandler<RTCRoomRemoteStreamMuteEventArgs^>(this, &RTCSession::OnRoomRemoteStreamMute);
	RoomListener->LocalUnPublish += gcnew EventHandler<RTCRoomLocalUnPublishEventArgs^>(this, &RTCSession::OnRoomLocalUnPublish);
	RoomListener->LocalStreamMute += gcnew EventHandler<RTCRoomLocalStreamMuteEventArgs^>(this, &RTCSession::OnRoomLocalStreamMute);
}

RTCUserDataInfo^ RTCSession::GetUserById(System::String^ userId)
{
	for (int i = 0; i < Users->Count; i++)
	{
		Users[i]->UserId == userId;
		return Users[i];
	}
}

void RTCSession::RaiseUserStateChanged(RTCSessionUserStateChangedEventArgs^ e)
{
	this->UserStateChanged(this,e);
}

void RTCSession::OnRoomJoinResult(System::Object^ sender, RTCRoomJoinResultEventArgs^ e)
{
	this->Users->AddRange(e->Users);
	RTCSessionUserStateChangedEventArgs^ args = gcnew RTCSessionUserStateChangedEventArgs;
	args->Users = this->Users->ToArray();
	this->RaiseUserStateChanged(args);
}

void RTCSession::OnRoomLeave(System::Object^ sender, RTCRoomLeaveEventArgs^ e)
{
	this->Users->Remove(GetUserById(e->KickerUserId));
	RTCSessionUserStateChangedEventArgs^ args = gcnew RTCSessionUserStateChangedEventArgs;
	args->Users = this->Users->ToArray();
	this->RaiseUserStateChanged(args);
}

void RTCSession::OnRoomLocalPublishResult(System::Object^ sender, RTCRoomLocalPublishResultEventArgs^ e)
{
	auto user = GetUserById(Room->GetUserId());
	if (user != nullptr)
	{
		user->AudioPublished = Room->AudioPublished;
		user->VideoPublished = Room->VideoPublished;
	}
	RTCSessionUserStateChangedEventArgs^ args = gcnew RTCSessionUserStateChangedEventArgs;
	args->Users = this->Users->ToArray();
	this->RaiseUserStateChanged(args);
}
void RTCSession::OnRoomRemoteUserJoin(System::Object^ sender, RTCRoomRemoteUserJoinEventArgs^ e)
{
	RTCUserDataInfo^ user = gcnew RTCUserDataInfo;
	user->UserId = e->UserId;
	this->Users->Add(user);
	RTCSessionUserStateChangedEventArgs^ args = gcnew RTCSessionUserStateChangedEventArgs;
	args->Users = this->Users->ToArray();
	this->RaiseUserStateChanged(args);
}
void RTCSession::OnRoomRemoteUserLeave(System::Object^ sender, RTCRoomRemoteUserLeaveEventArgs^ e)
{
	auto user = GetUserById(e->UserId);
	this->Users->Remove(user);
	RTCSessionUserStateChangedEventArgs^ args = gcnew RTCSessionUserStateChangedEventArgs;
	args->Users = this->Users->ToArray();
	this->RaiseUserStateChanged(args);
}
void RTCSession::OnRoomRemotePublish(System::Object^ sender, RTCRoomRemotePublishEventArgs^ e)
{
	auto user = GetUserById(e->UserId);
	if (user != nullptr)
	{
		user->AudioPublished = e->EnableAudio;
		user->VideoPublished = e->EnableVideo;
	}
	RTCSessionUserStateChangedEventArgs^ args = gcnew RTCSessionUserStateChangedEventArgs;
	args->Users = this->Users->ToArray();
	this->RaiseUserStateChanged(args);
}
void RTCSession::OnRoomRemoteUnPublish(System::Object^ sender, RTCRoomRemoteUnPublishEventArgs^ e)
{
	auto user = GetUserById(e->UserId);
	if (user != nullptr)
	{
		user->AudioPublished = false;
		user->VideoPublished = false;
	}
	RTCSessionUserStateChangedEventArgs^ args = gcnew RTCSessionUserStateChangedEventArgs;
	args->Users = this->Users->ToArray();
	this->RaiseUserStateChanged(args);
}

void RTCSession::OnRoomRemoteStreamMute(System::Object^ sender, RTCRoomRemoteStreamMuteEventArgs^ e)
{
	auto user = GetUserById(e->UserId);
	if (user != nullptr)
	{
		user->AudioMute = e->MuteAudio;
		user->VideoMute = e->MuteVideo;
	}
	RTCSessionUserStateChangedEventArgs^ args = gcnew RTCSessionUserStateChangedEventArgs;
	args->Users = this->Users->ToArray();
	this->RaiseUserStateChanged(args);
}

void RTCSession::OnRoomLocalStreamMute(System::Object^ sender, RTCRoomLocalStreamMuteEventArgs^ e)
{
	auto user = GetUserById(Room->GetUserId());
	if (user != nullptr)
	{
		user->AudioMute = e->MuteAudio;
		user->VideoMute = e->MuteVideo;
	}
	RTCSessionUserStateChangedEventArgs^ args = gcnew RTCSessionUserStateChangedEventArgs;
	args->Users = this->Users->ToArray();
	this->RaiseUserStateChanged(args);
}
void RTCSession::OnRoomLocalUnPublish(System::Object^ sender, RTCRoomLocalUnPublishEventArgs^ e)
{
	auto user = GetUserById(Room->GetUserId());
	if (user != nullptr)
	{
		user->AudioPublished = false;
		user->VideoPublished = false;
	}
	RTCSessionUserStateChangedEventArgs^ args = gcnew RTCSessionUserStateChangedEventArgs;
	args->Users = this->Users->ToArray();
	this->RaiseUserStateChanged(args);
}