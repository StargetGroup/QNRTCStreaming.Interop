#pragma once
#include "RTCUserDataInfo.h"

namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomJoinResultEventArgs
		{
		public:
			property int ErrorCode;

			property System::String^ ErrorMsg;

			property array<RTCUserDataInfo^>^ Users;
		};
	}
}
