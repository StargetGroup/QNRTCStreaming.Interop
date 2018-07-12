#include "stdafx.h"
#include "RTCCameraSetting.h"

using namespace QNRTCStreaming::Interop;
RTCCameraSetting::RTCCameraSetting()
{
	Width = 640;
	Height = 480;
	MaxFps = 25;
	Bitrate = 2000000;
	RenderHwnd = System::IntPtr::Zero;
}
