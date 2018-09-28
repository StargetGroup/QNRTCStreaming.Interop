#include "stdafx.h"
#include "RTCEngine.h"

using namespace QNRTCStreaming::Interop;

RTCEngine::RTCEngine()
{
}

int RTCEngine::Init()
{
	if (IsInited)
	{
		return 0;
	}
	auto b = QNRTCEngine::Init();
	if (b == 0)
	{
		IsInited = true;
	}
	return b;
}

int  RTCEngine::Release()
{
	if (IsInited == false)
	{
		return 0;
	}
	auto b = QNRTCEngine::Release();
	if (b == 0)
	{
		IsInited = false;
	}
	return b;
}

int RTCEngine::SetLogParams(RTCLogLevel level, System::String^ dirName, System::String^ fileName)
{
	QNLogLevel level_ = (QNLogLevel)level;
	auto dir_name_ = DataConvertUtil::SystemStringToStdString(dirName);
	auto file_name_ = DataConvertUtil::SystemStringToStdString(fileName);
	return QNRTCEngine::SetLogParams(level_, dir_name_, file_name_);
}