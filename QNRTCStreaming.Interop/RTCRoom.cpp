#include "stdafx.h"
#include "RTCRoom.h"

using namespace QNRTCStreaming::Interop;
using namespace pili_sdk_csharp::pili_common;
using namespace System::Security::Cryptography;
using namespace System::Net::Http;
RTCRoom::RTCRoom()
{

}

RTCRoom^ QNRTCStreaming::Interop::RTCRoom::ObtainRoomInterface()
{
	auto entity = QNRTCRoom::ObtainRoomInterface();
	RTCRoom^ room = gcnew RTCRoom;
	room->Entity = entity;
	return room;
}

RTCAudio^ RTCRoom::ObtainAudioInterface()
{
	auto entity = Entity->ObtainAudioInterface();
	RTCAudio^ audio = gcnew RTCAudio;
	audio->Entity = entity;
	return audio;
}

RTCVideo^ RTCRoom::ObtainVideoInterface()
{
	auto entity = Entity->ObtainVideoInterface();
	RTCVideo^ video = gcnew RTCVideo;
	video->Entity = entity;
	return video;
}

void RTCRoom::SetRoomListener(RTCRoomListener^ listener)
{
	RTCRoomListenerImpl* impl = new RTCRoomListenerImpl(listener);
	Entity->SetRoomListener(impl);
}

RTCRoomListener^ RTCRoom::GetRoomListener()
{
	auto listener_ = Entity->GetRoomListener();
	auto impl = dynamic_cast<RTCRoomListenerImpl*>(listener_);
	return impl->GetCallback();
}

int RTCRoom::JoinRoom(System::String^ roomToken)
{
	auto room_token_ = DataConvertUtil::SystemStringToStdString(roomToken);
	auto result = Entity->JoinRoom(room_token_);
	return result;
}

int RTCRoom::LeaveRoom()
{
	return Entity->LeaveRoom();
}

bool RTCRoom::IsJoined()
{
	return Entity->IsJoined();
}

System::String^ RTCRoom::GetRoomName()
{
	auto room_name_ = Entity->GetRoomName();
	auto roomName = DataConvertUtil::StdStringToSystemString(room_name_);
	return roomName;
}

System::String^ RTCRoom::GetUserId()
{
	auto user_id_ = Entity->GetUserID();
	auto userId = DataConvertUtil::StdStringToSystemString(user_id_);
	return userId;
}

int RTCRoom::Publish(bool enableAudio, bool enableVideo)
{
	int ret = Entity->Publish(enableAudio, enableVideo);
	if (ret == 0)
	{
		AudioPublished = enableAudio;
		VideoPublished = enableVideo;
	}
	return ret;
}

int RTCRoom::UnPublish()
{
	int ret = Entity->UnPublish();
	auto  listener = this->GetRoomListener();
	if (ret == 0)
	{
		AudioPublished = false;
		VideoPublished = false;
		if (listener != nullptr)
		{
			RTCRoomLocalUnPublishEventArgs^ args = gcnew RTCRoomLocalUnPublishEventArgs;
			listener->RaiseLocalUnPublish(args);
		}
	}
	return ret;
}

int RTCRoom::Subscribe(System::String^ userId, System::IntPtr renderHwnd)
{
	auto user_id_ = DataConvertUtil::SystemStringToStdString(userId);
	void* render_hwnd_ = nullptr;
	if (renderHwnd != System::IntPtr::Zero)
	{
		render_hwnd_ = renderHwnd.ToPointer();
	}

	return Entity->Subscribe(user_id_, render_hwnd_);
}

int RTCRoom::KickoutUser(System::String ^ userId)
{
	auto user_id_ = DataConvertUtil::SystemStringToStdString(userId);
	return Entity->KickoutUser(user_id_);
}

int RTCRoom::MuteAudio(bool muteFlag)
{
	int ret = Entity->MuteAudio(muteFlag);
	auto  listener = this->GetRoomListener();
	if (ret == 0)
	{
		MuteAudioFlag = muteFlag;
		if (listener != nullptr)
		{
			RTCRoomLocalStreamMuteEventArgs^ args = gcnew RTCRoomLocalStreamMuteEventArgs;
			args->MuteAudio = MuteAudioFlag;
			args->MuteVideo = MuteVideoFlag;
			listener->RaiseLocalStreamMute(args);
		}
	}
	return ret;
}

int RTCRoom::MuteVideo(bool muteFlag)
{
	int ret = Entity->MuteVideo(muteFlag);
	auto  listener = this->GetRoomListener();
	if (ret == 0)
	{
		MuteVideoFlag = muteFlag;
		if (listener != nullptr)
		{
			RTCRoomLocalStreamMuteEventArgs^ args = gcnew RTCRoomLocalStreamMuteEventArgs;
			args->MuteAudio = MuteAudioFlag;
			args->MuteVideo = MuteVideoFlag;
			listener->RaiseLocalStreamMute(args);
		}
	}
	return ret;
}

void RTCRoom::EnableStatisticCallback(int periodSecond)
{
	Entity->EnableStatisticCallback(periodSecond);
}

int RTCRoom::SetMergeStreamLayout(System::String^ userId,
	int posX, int posY, int posZ,
	int width, int height, bool isVisible)
{
	auto user_id_ = DataConvertUtil::SystemStringToStdString(userId);
	return Entity->SetMergeStreamLayout(user_id_, posX, posY, posZ, width, height, isVisible);
}

int RTCRoom::StopMergeStream()
{
	return Entity->StopMergeStream();
}

System::String^ RTCRoom::CreateRoomToken(System::String^ roomName, System::String^ userId,bool isAdmin, System::DateTime expireAt, System::String^ appId, System::String^ accessKey, System::String^ secretKey)
{
	auto encoding = gcnew System::Text::UTF8Encoding;
	System::DateTime^ refDate = gcnew System::DateTime(1970, 1, 1);
	System::String^ strExpireAt = Convert::ToInt64(System::DateTime::Now.AddDays(2).Subtract(*refDate).TotalMilliseconds).ToString();
	System::String^ permission = isAdmin ? "admin" : "user";
	System::String^ json = "{\"appId\":\"" + appId + "\",\"roomName\":\"" + roomName + "\",\"userId\":\"" + userId + "\",\"expireAt\":" 
		+ strExpireAt +",\"permission\":\""+ permission +"\"}";

	auto b = encoding->GetBytes(json);
	auto encodedRoomAccess = UrlSafeBase64::encodeToString(b);
	b = encoding->GetBytes(encodedRoomAccess);
	// 2. 计算HMAC-SHA1签名，并对签名结果做URL安全的Base64编码
	auto keyByte = encoding->GetBytes(secretKey);
	auto sha1 = gcnew HMACSHA1(keyByte);
	auto sign = sha1->ComputeHash(b);
	auto encodedSign = UrlSafeBase64::encodeToString(sign);

	// 3. 将AccessKey与以上两者拼接得到房间鉴权
	auto roomToken = accessKey + ":" + encodedSign + ":" + encodedRoomAccess;
	return roomToken;
}

System::String^ RTCRoom::CreateTestRoomToken(System::String^ roomName, System::String^ userId, bool isAdmin)
{
	auto url = "http://api-demo.qnsdk.com/v1/rtc/token/admin/app/d8lk7l4ed/room/"+ roomName +"/user/"+ userId;
	if (isAdmin == false)
	{
		url = "http://api-demo.qnsdk.com/v1/rtc/token/app/d8lk7l4ed/room/" + roomName + "/user/"+ userId;
	}
	HttpClient^ client = gcnew HttpClient();
	auto task = client->GetStringAsync(url);
	task->Wait();
	auto token = task->Result;
	return token;
}