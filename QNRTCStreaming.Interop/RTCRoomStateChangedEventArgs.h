#pragma once
#include "RTCRoomState.h"

namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomStateChangedEventArgs
		{
		public:
			RTCRoomStateChangedEventArgs();
			property RTCRoomState State;
		};

	}
}