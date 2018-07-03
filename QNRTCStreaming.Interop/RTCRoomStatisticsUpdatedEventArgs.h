#pragma once
#include "RtcStatisticsReport.h"

namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCRoomStatisticsUpdatedEventArgs
		{
		public:
			property RTCStatisticsReport^ Statistics;
		};

	}
}