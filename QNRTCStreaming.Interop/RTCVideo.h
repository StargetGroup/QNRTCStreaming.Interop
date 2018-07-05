#pragma once
#include "RTCCameraDeviceInfo.h"
#include "RTCVideoListener.h"
#include "RTCCameraSetting.h"
#include "RTCVideoListenerImpl.h"
#include "RTCVideoRotation.h"
#include "RTCScreenWindowInfo.h"

namespace QNRTCStreaming
{
	namespace Interop
	{
		public ref class RTCVideo
		{
		public:
			RTCVideo();
			/** Get the number of local cameras
			* @return the number of local cameras
			*/
			int GetCameraCount();

			/** Get specified camera devices information
			* @param [in] device_index_
			*        output local camera's device informations
			* @return return an object of CameraDeviceInfo
			*/
			RTCCameraDeviceInfo^ GetCameraInfo(int deviceIndex);

			array<RTCCameraDeviceInfo^>^ GetCameraDevices();

			/** Set the video module event listener interface, you must set it to nullptr
			*   before exiting the room
			* @param [in] listener_ptr_
			*        the instance pointer of the QNRTCVideoListener interface is implemented
			*/
			void SetVideoListener(RTCVideoListener^ listener);

			/** Get the pointer of QNRTCVideoListener set by the user
			* @return The user sets an instance pointer to the QNRTCVideoListener interface
			*/
			RTCVideoListener^ GetVideoListener();

			/** Set camera params before publish video stream, or else it will use default params
			* @param [in out] camera_setting_
			*        set the camera params before publish, if the camera not support those params,
			*        it will output the most similar params and publish
			* @return return 0 if success or an error code
			*/
			int SetCameraParams(RTCCameraSetting^ cameraSetting);

			/** Preview the camera by specified params
			* @param [in out] camera_setting_
			*        set the camera params previewed, if the camera not support those params,
			*        it will output the most similar params and publish
			* @return return 0 if success or an error code
			*/
			int PreviewCamera(RTCCameraSetting^ cameraSetting);

			/** Cancel preview camera
			* @return return 0 if success or an error code
			*/
			int UnPreviewCamera();

			/** Enable or disable external data import feature
			* @param [in] enable_flag_
			*        true:enable, false:disable;
			* @return return 0 if success or an error code
			* @brief developer must call this method before InputVideoFrame
			*/
			int EnableVideoFakeCamera(bool enableFlag);

			/** Import video frame data when external data import feature enabled
			* @param [in] data_
			*        video frame data pointer
			* @param [in] data_size_
			*        video frame data size
			* @param [in] width_
			*        picture width
			* @param [in] height_
			*        picture height
			* @param [in] timestamp_us_
			*        video frame timestamp, unit:microsecond
			* @param [in] raw_type_
			*        video frame type, currently supports three formats: kI420 kYUY2 kRGB24
			* @param [in] rotation_
			*        clockwise rotation, default is kVideoRotation_0
			* @param [in] mirror_flag_
			*        whether the input video frame need mirror
			* @return return 0 if success or an error code
			* @brief developer must call EnableVideoFakeCamera(true) first
			*/
			int InputVideoFrame(
				System::IntPtr data,
				int dataSize,
				int width,
				int height,
				System::Int64 timestampUs,
				RTCVideoCaptureType rawType,
				RTCVideoRotation rotation,
				bool mirrorFlag
			);

			/** Whether enabled video fake camera future
			* @return true: enable, false: disable
			*/
			bool IsEnableVideoFakeCamera();

			/** Get the number of screen windows
			* @return the number of local screen windows
			* @brief not thread safe
			*/
			int GetScreenWindowCount();

			/** Get specified screen window's information
			* @param [in] screen window's index
			* @return return an object of ScreenWindowInfo
			* @brief not thread safe
			*/
			RTCScreenWindowInfo^ GetScreenWindowInfo(int index);

			/** Enable or disable screen share,if source_id_ >= 0 ,enable; if source_id_ < 0, disable;
			* @param [in] source_id_
			*        screen window source id, obtain by method:GetScreenWindowInfo
			* @param [in] allow_directx_capturer_
			*        allowing directx based capturer or not, this capturer works on windows 7
			*        with platform update / windows 8 or upper.
			* @return return 0 if success, or an error code
			*/
			int EnableAndSetScreenSourceId(int sourceId, bool allowDirectxCapturer);

			/** Get screen source id, if < 0, not enable
			* @return enable and set screen source's id, if not enable, it will return -1
			*/
			int GetScreenSourceId();

			/** Mirroring the specified user, mirror = left and right rotation
			* @param [in] user_id_
			*        specified user id
			* @param [in] mirror_flag_
			*        mirror flag, true or false
			* @return is set success
			*/
			int SetMirrorWhenDisplay(System::String^ userId, bool mirrorFlag);

			QNRTCVideo* Entity;
		};
	}
}
