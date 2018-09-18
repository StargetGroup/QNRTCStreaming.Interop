#pragma once

namespace qiniu
{
#define QNRTC_OK 0
#define QNRTC_FAILED -1
#define QNRTC_SUCCEEDED(rv) (rv == AVD_OK)
    
//server error code
/* token error */
#define Err_Token_Error 10001

/* token is expired */
#define Err_Token_Expired 10002

/* room instance closed */
#define Err_Room_INSTANCE_Closed 10003

/*reconnect token error*/
#define Err_ReconnToken_Error 10004

/* room closed*/
#define Err_Room_Closed 10005

/* kicked out of the room */
#define Err_Kickout_Of_Room 10006
        
/* room is full*/
#define Err_Room_Full 10011

/* room not exist */
#define Err_ROOM_Not_Exist 10012

/* user not exist */
#define Err_User_Not_Exist 10021

/* user already exist */
#define Err_User_Already_Exist 10022

/* publish stream not exist */
#define Err_Publish_Stream_Not_Exist 10031

/* publish stream info not match */
#define  Err_Publish_Stream_Info_Not_Match 10032

/* publish stream already exist */
#define Err_Publish_Stream_Already_exist 10033

/* publish stream not ready */
#define Err_Publish_Stream_Not_Ready 10034

/* subscribe stream not exist */
#define Err_Subscribe_Stream_Not_Exist 10041

/* subscribe stream info not match */
#define Err_Subscribe_Stream_Info_Not_Match 10042

/* subscribe stream already exist */
#define Err_Subscribe_Stream_Already_Exist 10043

/* can't subscribe yourself */
#define Err_Cannot_Subscribe_Self 10044

/* no permission */
#define Err_No_Permission 10051

/* server unavailable */
#define Err_Server_Unavailable 10052


//client error code
/* Invalid params */
#define Err_Invalid_Parameters 11000

/* SDK internal Null pointer */
#define Err_Internal_Null_Pointer 11001

/* Can not destroy in own thread */
#define Err_Cannot_Destroy_In_Self_Thread 11005

/* Can not change device when recording */
#define Err_Cannot_Change_When_Using 11006

/* Failed to set recorder device */
#define Err_Failed_Set_Recorder_Device 11007

/* Failed to set communication recorder device */
#define Err_Failed_Set_Communication_Recorder_Device 11008

/* Failed to set playout device */
#define Err_Failed_Set_Playout_Device 11009

/* Failed to set communication playout device */
#define Err_Failed_Set_Communication_Playout_Device 11010

/* Failed to get recorder or playout volume */
#define Err_Failed_Get_Volume 11011

/* Failed to set recorder or playout volume*/
#define Err_Failed_Set_volume 11012

/* Playout mute failed */
#define Err_Playout_Mute_Failed 11013

/* Recorder mute failed */
#define Err_Recorder_Mute_Failed 11014

/* Operator failed */
#define Err_Operator_Failed 11015

/* Room already joined */
#define Err_Room_Already_Joined 11016

/* Network disconnected */
#define Err_Network_Disconnect 11017

/* No this user */
#define Err_No_This_User 11018

/* No this user's stream info */
#define Err_No_This_User_Stream_Info 11019

/* Device busy */
#define Err_Device_Busy 11020

/* Device open failed */
#define Err_Device_Open_Failed 11021

/* No this Device */
#define Err_No_This_Device 11022

/* Already published*/
#define Err_Already_Published 11023

/* Already unpublished*/
#define Err_Already_UnPublished 11024

/* no publish record */
#define Err_No_Publish_Record 11025

/* Already subscribed or subscribing */
#define Err_Already_Subscribed 11026

/* Stream's connid exception */
#define Err_Stream_ConnId_Empty 11027

/* Already unsubscribed or unsubscribing */
#define Err_Already_UnSubscribed 11028

/* Decode room token failed */
#define Err_Decode_RoomToken_Failed 11029

/* Parse json string failed */
#define Err_Parse_Json_Failed 11030

/* Parse json get room name failed */
#define Err_Parse_Json_RoomName_Failed 11031

/* Parse json get user id failed */
#define Err_Parse_Json_UserId_Failed 11032

/* Parse json get appId failed */
#define Err_Parse_Json_AppId_Failed 11033

/* Request access token failed */
#define Err_Request_Access_Token_Failed 11034

/* Parse access token failed */
#define Err_Parse_Access_Token_Failed 11035

/* Parse room server address failed */
#define Err_Parse_Room_Server_Address_Failed 11036

/* Connect server to get accesstoken timeout */
#define Err_Get_AccessToken_Timeout 11040

/* Video capture module not running*/
#define Err_VideoCapture_Not_Running 11050

/* Create offer sdp failed*/
#define Err_CreateOffer_Failed 11060

/* recording not started*/
#define Err_Record_Not_Start 11061

/* Resample failed*/
#define Err_Internal_Resamle_Failed 11062

/* No memory*/
#define Err_No_Memory 11063
}
