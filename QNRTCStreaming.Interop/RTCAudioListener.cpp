#include "stdafx.h"
#include "RTCAudioListener.h"

using namespace QNRTCStreaming::Interop;
RTCAudioListener::RTCAudioListener()
{
}

void RTCAudioListener::RaiseAudioPCMFrame(RTCAudioPCMFrameEventArgs^ e)
{
	this->AudioPCMFrame(this, e);
}

void RTCAudioListener::RaiseAudioDeviceStateChanged(RTCAudioDeviceStateChangedEventArgs^ e)
{
	this->AudioDeviceStateChanged(this, e);
}