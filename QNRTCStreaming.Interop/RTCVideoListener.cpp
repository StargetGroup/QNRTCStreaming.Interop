#include "stdafx.h"
#include "RTCVideoListener.h"

using namespace QNRTCStreaming::Interop;
void RTCVideoListener::RaiseVideoFrame(RTCVideoFrameEventArgs^ e)
{
	this->VideoFrame(this, e);
}

void RTCVideoListener::RaiseVideoDeviceStateChanged(RTCVideoDeviceStateChangedEventArgs^ e)
{
	this->VideoDeviceStateChanged(this, e);
}
