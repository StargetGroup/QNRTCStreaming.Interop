#pragma once
#include <string>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace msclr::interop;
namespace QNRTCStreaming
{
	namespace Interop
	{
		static class DataConvertUtil
		{
		public:
			static const char* SystemStringToConstCharPtr(String^ str)
			{
				marshal_context mc;
				return mc.marshal_as<const char*>(str);
			}

			static String^ ConstCharPtrToSystemString(const char* str)
			{
				return marshal_as<String^>(str);
			}

			static String^ CharPtrToSystemString(char* str)
			{
				return marshal_as<String^>(str);
			}

			static const wchar_t* SystemStringToConstWcharPtr(String^ str)
			{
				marshal_context mc;
				return mc.marshal_as<const wchar_t*>(str);
			}

			static String^ ConstWcharPtrToSystemString(const wchar_t* str)
			{
				return marshal_as<String^>(str);
			}

			static String^ WcharPtrToSystemString(wchar_t* str)
			{
				return marshal_as<String^>(str);
			}

			static std::string SystemStringToStdString(String^ str)
			{
				return marshal_as<std::string>(str);
			}

			static String^ StdStringToSystemString(std::string str)
			{
				return marshal_as<String^>(str);
			}
		};

	}
}