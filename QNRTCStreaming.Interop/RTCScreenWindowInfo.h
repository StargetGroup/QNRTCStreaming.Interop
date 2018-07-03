#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCScreenWindowInfo
		{
		public:
			int          Id;        // windows id
			System::String^  Title;     // windows title
			bool         IsScreen; // is screen, true:sreen; false:window
		};

	}
}