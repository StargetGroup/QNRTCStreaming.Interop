#include "stdafx.h"
#include "RTCUserDataInfo.h"

using namespace QNRTCStreaming::Interop;
RTCUserDataInfo::RTCUserDataInfo()
{
}


System::String^ RTCUserDataInfo::ToString()
{
	return System::String::Format("UserId:{0} AudioPublished:{1} VideoPublished:{2} AudioMute:{3} VideoMute:{4}",
		UserId, AudioPublished, VideoPublished, AudioMute, VideoMute);
}