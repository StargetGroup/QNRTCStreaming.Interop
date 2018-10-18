#include "stdafx.h"
#include "RTCSession.h"

using namespace System::IO;
using namespace System::Windows::Forms;
using namespace QNRTCStreaming::Interop;
using namespace System::Threading;
using namespace System::Linq;
using namespace System::Collections;

RTCSession::RTCSession()
{
}

RTCSession::~RTCSession()
{
	if (pCorpPictureBuffer != nullptr)
	{
		delete[] pCorpPictureBuffer;
		pCorpPictureBuffer = nullptr;
	}
}

int RTCSession::Init()
{
	auto b = RTCEngine::Init();
	if (b != 0)
	{
		return b;
	}
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
	RoomListener->SubscribeResult += gcnew EventHandler<RTCRoomSubscribeResultEventArgs^> (this, &RTCSession::OnRoomSubscribeResult);

	return 0;
}

int RTCSession::SetLogParams(System::String^ fileName)
{
	if (RTCEngine::GetLogFileName() != nullptr)
	{
		return -1;
	}
	if (fileName == nullptr)
	{
		auto path = Path::Combine(Application::StartupPath, "rtc-log");
		return RTCEngine::SetLogParams(RTCLogLevel::LOG_INFO, path, "rtc.log");
	}
	else
	{
		FileInfo^ fi = gcnew FileInfo(fileName);
		auto path = fi->DirectoryName;
		auto fileName = fi->Name;
		return RTCEngine::SetLogParams(RTCLogLevel::LOG_INFO, path, fileName);
	}
}

int RTCSession::JoinRoom(System::String^ roomToken)
{
	if (Room != nullptr)
	{
		return Room->JoinRoom(roomToken);
	}
	return -1;
}

int RTCSession::LeaveRoom()
{
	if (Room != nullptr)
	{
		this->Users->Clear();
		RTCSessionUserStateChangedEventArgs^ args = gcnew RTCSessionUserStateChangedEventArgs;
		args->Users = this->Users->ToArray();
		this->RaiseUserStateChanged(args);
		return Room->LeaveRoom();
	}
	return -1;
}

void RTCSession::Release()
{
	if (Room != nullptr)
	{
		return Room->Release();
	}
}

RTCUserDataInfo^ RTCSession::GetUserById(System::String^ userId)
{
	for (int i = 0; i < Users->Count; i++)
	{
		if (Users[i]->UserId == userId)
		{
			return Users[i];
		}
	}
	return nullptr;
}

void RTCSession::RaiseUserStateChanged(RTCSessionUserStateChangedEventArgs^ e)
{
	this->UserStateChanged(this,e);
}

void RTCSession::OnRoomJoinResult(System::Object^ sender, RTCRoomJoinResultEventArgs^ e)
{
	auto list = this->Users->ToArray();
	for (int i = 0; i < list->Length;i++) {
		auto user = list[i];
		if (user->Subscribed) {
			Room->UnSubscribe(user->UserId);
		}
	}
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
		user->Subscribed = false;
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
		user->Subscribed = false;
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

void RTCSession::OnRoomSubscribeResult(System::Object^ sender, RTCRoomSubscribeResultEventArgs^ e)
{
	if (e->ErrorCode == 0) 
	{
		auto user = GetUserById(e->UserId);
		if (user != nullptr)
		{
			user->Subscribed = true;
		}
	}
}

int RTCSession::CropRawPicture(
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
)
{
	if (pCorpPictureBuffer == nullptr) {
		pCorpPictureBuffer = new uint8_t[destWidth * destHeight * 3];
	}
	uint32_t dest_size(0);
	auto dest_data_ptr = System::IntPtr(pCorpPictureBuffer);
	auto ret = Video->CropRawPicture(srcData, srcWidth, srcHeight, srcDataSize, pictureFmt
		, mirrorFlag, originX, originY, destWidth, destHeight, dest_data_ptr, destWidth * destHeight * 3 / 2, __out dest_size);
	destData = dest_data_ptr;
	return ret;
}