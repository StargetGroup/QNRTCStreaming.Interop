#pragma once
#include "RTCUserDataInfo.h"
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCSessionUserStateChangedEventArgs
		{
		public:
			property array<RTCUserDataInfo^>^ Users;
		};
	}
}