#pragma once
#include "RTCUserDataInfo.h"

namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomLeaveEventArgs
		{
		public:
			property int ErrorCode;

			property System::String^ ErrorMsg;

			property System::String^ KickerUserId;
		};
	}
}
