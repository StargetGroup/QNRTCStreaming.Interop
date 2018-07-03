#include "stdafx.h"
#include "RTCVideo.h"

using namespace QNRTCStreaming::Interop;
RTCVideo::RTCVideo()
{

}

/** Get the number of local cameras
* @return the number of local cameras
*/
int RTCVideo::GetCameraCount()
{
	return Entity->GetCameraCount();
}

/** Get specified camera devices information
* @param [in] device_index_
*        output local camera's device informations
* @return return an object of CameraDeviceInfo
*/
RTCCameraDeviceInfo^ RTCVideo::GetCameraInfo(int deviceIndex)
{
	CameraDeviceInfo camera_info_ = Entity->GetCameraInfo(deviceIndex);

	if (&camera_info_ == nullptr)
	{
		return nullptr;
	}

	RTCCameraDeviceInfo^ cameraInfo = gcnew RTCCameraDeviceInfo;
	cameraInfo->DeviceId = DataConvertUtil::StdStringToSystemString(camera_info_.device_id);
	cameraInfo->DeviceName = DataConvertUtil::StdStringToSystemString(camera_info_.device_name);
	auto count = camera_info_.capability_vec.size();
	auto list = gcnew array<RTCCameraCapability^>(count);
	cameraInfo->Capabilitys = list;
	for (int i = 0; i < count; i++)
	{
		auto cp_ = camera_info_.capability_vec[i];
		RTCCameraCapability^ cp = gcnew RTCCameraCapability;
		cp->VideoType = (RTCVideoCaptureType)cp_.video_type;
		cp->Width = cp_.width;
		cp->Height = cp_.height;
		cp->MaxFps = cp_.max_fps;
		list[i] = cp;
	}
	return cameraInfo;
}

array<RTCCameraDeviceInfo^>^ RTCVideo::GetCameraDevices()
{
	auto count = GetCameraCount();
	auto list = gcnew array<RTCCameraDeviceInfo^>(count);
	for (int i = 0; i < count; i++)
	{
		RTCCameraDeviceInfo^ cameraInfo = GetCameraInfo(i);
		if (cameraInfo != nullptr)
		{
			list[i] = cameraInfo;
		}
	}
	return list;
}

/** Set the video module event listener interface, you must set it to nullptr
*   before exiting the room
* @param [in] listener_ptr_
*        the instance pointer of the QNRTCVideoListener interface is implemented
*/
void RTCVideo::SetVideoListener(RTCVideoListener^ listener)
{
	RTCVideoListenerImpl* impl = new RTCVideoListenerImpl(listener);
	Entity->SetVideoListener(impl);
}

/** Get the pointer of QNRTCVideoListener set by the user
* @return The user sets an instance pointer to the QNRTCVideoListener interface
*/
RTCVideoListener^ RTCVideo::GetVideoListener()
{
	auto listener_ = Entity->GetVideoListener();
	auto impl = dynamic_cast<RTCVideoListenerImpl*>(listener_);
	return impl->GetCallback();
}

/** Set camera params before publish video stream, or else it will use default params
* @param [in out] camera_setting_
*        set the camera params before publish, if the camera not support those params,
*        it will output the most similar params and publish
* @return return 0 if success or an error code
*/
int RTCVideo::SetCameraParams(RTCCameraSetting^ cameraSetting)
{
	CameraSetting setting_;
	setting_.device_id = DataConvertUtil::SystemStringToStdString(cameraSetting->DeviceId);
	setting_.device_name = DataConvertUtil::SystemStringToStdString(cameraSetting->DeviceName);
	setting_.width = cameraSetting->Width;
	setting_.height = cameraSetting->Height;
	setting_.bitrate = cameraSetting->Bitrate;
	setting_.max_fps = cameraSetting->MaxFps;
	if (cameraSetting->RenderHwnd)
	{
		setting_.render_hwnd = cameraSetting->RenderHwnd->ToPointer();
	}
	return this->Entity->SetCameraParams(setting_);
}

/** Preview the camera by specified params
* @param [in out] camera_setting_
*        set the camera params previewed, if the camera not support those params,
*        it will output the most similar params and publish
* @return return 0 if success or an error code
*/
int RTCVideo::PreviewCamera(RTCCameraSetting^ cameraSetting)
{
	CameraSetting setting_;
	setting_.device_id = DataConvertUtil::SystemStringToStdString(cameraSetting->DeviceId);
	setting_.device_name = DataConvertUtil::SystemStringToStdString(cameraSetting->DeviceName);
	setting_.width = cameraSetting->Width;
	setting_.height = cameraSetting->Height;
	setting_.bitrate = cameraSetting->Bitrate;
	setting_.max_fps = cameraSetting->MaxFps;
	if (cameraSetting->RenderHwnd)
	{
		setting_.render_hwnd = cameraSetting->RenderHwnd->ToPointer();
	}
	return this->Entity->PreviewCamera(setting_);
}

/** Cancel preview camera
* @return return 0 if success or an error code
*/
int RTCVideo::UnPreviewCamera()
{
	return this->Entity->UnPreviewCamera();
}

int RTCVideo::EnableVideoFakeCamera(bool enableFlag)
{
	return this->Entity->EnableVideoFakeCamera(enableFlag);
}

int RTCVideo::InputVideoFrame(
	System::IntPtr^ data,
	int dataSize,
	int width,
	int height,
	System::Int64 timestampUs,
	RTCVideoCaptureType rawType,
	RTCVideoRotation rotation,
	bool mirrorFlag
)
{
	auto data_ = (const unsigned char*)data->ToPointer();
	auto raw_type_ = (VideoCaptureType)rawType;
	auto rotation_ = (VideoRotation)rotation;
	return this->Entity->InputVideoFrame(data_, dataSize, width, height, timestampUs, raw_type_, rotation_);
}

/** Whether enabled video fake camera future
* @return true: enable, false: disable
*/
bool RTCVideo::IsEnableVideoFakeCamera()
{
	return this->Entity->IsEnableVideoFakeCamera();
}

/** Get the number of screen windows
* @return the number of local screen windows
* @brief not thread safe
*/
int RTCVideo::GetScreenWindowCount()
{
	return this->Entity->GetScreenWindowCount();
}

/** Get specified screen window's information
* @param [in] screen window's index
* @return return an object of ScreenWindowInfo
* @brief not thread safe
*/
RTCScreenWindowInfo^ RTCVideo::GetScreenWindowInfo(int index)
{
	auto window_info_ = this->Entity->GetScreenWindowInfo(index);
	RTCScreenWindowInfo^ windowInfo = gcnew RTCScreenWindowInfo;
	windowInfo->Id = window_info_.id;
	windowInfo->Title = DataConvertUtil::StdStringToSystemString(window_info_.title);
	windowInfo->IsScreen = window_info_.is_screen;
	return windowInfo;
}

int RTCVideo::EnableAndSetScreenSourceId(int sourceId, bool allowDirectxCapturer)
{
	return Entity->EnableAndSetScreenSourceId(sourceId, allowDirectxCapturer);
}

int RTCVideo::GetScreenSourceId()
{
	return Entity->GetScreenSourceId();
}

int RTCVideo::SetMirrorWhenDisplay(System::String^ userId, bool mirrorFlag)
{
	auto user_id_ = DataConvertUtil::SystemStringToStdString(userId);
	return Entity->SetMirrorWhenDisplay(user_id_, mirrorFlag);
}
