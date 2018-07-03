#pragma once
#include "RTCLogLevel.h"
namespace QNRTCStreaming
{
	namespace Interop 
	{
		public ref class RTCEngine
		{
		public:
			RTCEngine();
			property static bool IsInited;
			/**
			* Initialize the SDK internal resources
			* @return return 0 if success or an error code
			*/
			static int  Init();

			/**
			* Release the SDK internal resources
			* @return return 0 if success or an error code
			*/
			static int  Release();

			/**
			* Sets the parameter information for the log store
			* @param [in] level_
			*        what level of logs will be logged
			* @param [in] dir_name_
			*        the log will be stored in which directory
			* @param [in] file_name_
			*        the log file name of stored
			* @return return 0 if success or an error code
			*/
			static int SetLogParams(RTCLogLevel level,
				System::String^ dirName, System::String^ fileName);

		//protected:
		//	virtual ~QNRTCEngine() {};
		};
	}
}
