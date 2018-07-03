#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCCameraSetting
		{
		public:
			RTCCameraSetting();
			property System::String^ DeviceId;              //camera device id, can't be empty
			property System::String^ DeviceName;            //camera device name, can't be empty
			property int Width;      //camera capture and encode width
			property int Height;      //camera capture and encode height
			property int MaxFps;       //video frames per second
			property int Bitrate;   //video encode bitrate, unit:bps
			property System::IntPtr^  RenderHwnd;  //video render window hwnd,MFC:HWND; QT:winId
		};
	}
}
