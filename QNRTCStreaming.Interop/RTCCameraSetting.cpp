#include "stdafx.h"
#include "RTCCameraSetting.h"

using namespace QNRTCStreaming::Interop;
RTCCameraSetting::RTCCameraSetting()
{
	Width = 640;
	Height = 480;
	MaxFps = 15;
	Bitrate = 300000;
	RenderHwnd = System::IntPtr::Zero;
}
