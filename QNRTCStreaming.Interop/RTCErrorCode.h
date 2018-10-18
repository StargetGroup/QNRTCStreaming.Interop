#pragma once
namespace QNRTCStreaming
{
	namespace Interop
	{
		public enum class RTCErrorCode
		{
			OK = 0,
			FAILED = -1,

			//server error code
			/* token error */
			Token_Error = 10001,

			/* token is expired */
			Token_Expired = 10002,

			/* room instance closed */
			Room_INSTANCE_Closed = 10003,

			/*reconnect token error*/
			ReconnToken_Error = 10004,

			/* room closed*/
			Room_Closed = 10005,

			/* kicked out of the room */
			Kickout_Of_Room = 10006,

			/* room is full*/
			Room_Full = 10011,

			/* room not exist */
			ROOM_Not_Exist = 10012,

			/* user not exist */
			User_Not_Exist = 10021,

			/* user already exist */
			User_Already_Exist = 10022,

			/* publish stream not exist */
			Publish_Stream_Not_Exist = 10031,

			/* publish stream info not match */
			Publish_Stream_Info_Not_Match = 10032,

			/* publish stream already exist */
			Publish_Stream_Already_exist = 10033,

			/* publish stream not ready */
			Publish_Stream_Not_Ready = 10034,

			/* subscribe stream not exist */
			Subscribe_Stream_Not_Exist = 10041,

			/* subscribe stream info not match */
			Subscribe_Stream_Info_Not_Match = 10042,

			/* subscribe stream already exist */
			Subscribe_Stream_Already_Exist = 10043,

			/* can't subscribe yourself */
			Cannot_Subscribe_Self = 10044,

			/* no permission */
			No_Permission = 10051,

			/* server unavailable */
			Server_Unavailable = 10052,


			//client error code
			/* Invalid params */
			Invalid_Parameters = 11000,

			/* SDK internal Null pointer */
			Internal_Null_Pointer = 11001,

			/* Can not destroy in own thread */
			Cannot_Destroy_In_Self_Thread = 11005,

			/* Can not change device when recording */
			Cannot_Change_When_Using = 11006,

			/* Failed to set recorder device */
			Failed_Set_Recorder_Device = 11007,

			/* Failed to set communication recorder device */
			Failed_Set_Communication_Recorder_Device = 11008,

			/* Failed to set playout device */
			Failed_Set_Playout_Device = 11009,

			/* Failed to set communication playout device */
			Failed_Set_Communication_Playout_Device = 11010,

			/* Failed to get recorder or playout volume */
			Failed_Get_Volume = 11011,

			/* Failed to set recorder or playout volume*/
			Failed_Set_volume = 11012,

			/* Playout mute failed */
			Playout_Mute_Failed = 11013,

			/* Recorder mute failed */
			Recorder_Mute_Failed = 11014,

			/* Operator failed */
			Operator_Failed = 11015,

			/* Room already joined */
			Room_Already_Joined = 11016,

			/* Network disconnected */
			Network_Disconnect = 11017,

			/* No this user */
			No_This_User = 11018,

			/* No this user's stream info */
			No_This_User_Stream_Info = 11019,

			/* Device busy */
			Device_Busy = 11020,

			/* Device open failed */
			Device_Open_Failed = 11021,

			/* No this Device */
			No_This_Device = 11022,

			/* Already published*/
			Already_Published = 11023,

			/* Already unpublished*/
			Already_UnPublished = 11024,

			/* no publish record */
			No_Publish_Record = 11025,

			/* Already subscribed or subscribing */
			Already_Subscribed = 11026,

			/* Stream's connid exception */
			Stream_ConnId_Empty = 11027,

			/* Already unsubscribed or unsubscribing */
			Already_UnSubscribed = 11028,

			/* Decode room token failed */
			Decode_RoomToken_Failed = 11029,

			/* Parse json string failed */
			Parse_Json_Failed = 11030,

			/* Parse json get room name failed */
			Parse_Json_RoomName_Failed = 11031,

			/* Parse json get user id failed */
			Parse_Json_UserId_Failed = 11032,

			/* Parse json get appId failed */
			Parse_Json_AppId_Failed = 11033,

			/* Request access token failed */
			Request_Access_Token_Failed = 11034,

			/* Parse access token failed */
			Parse_Access_Token_Failed = 11035,

			/* Parse room server address failed */
			Parse_Room_Server_Address_Failed = 11036,

			/* Connect server to get accesstoken timeout */
			Get_AccessToken_Timeout = 11040,

			/* Video capture module not running*/
			VideoCapture_Not_Running = 11050,

			/* Create offer sdp failed*/
			CreateOffer_Failed = 11060,

			/* recording not started*/
			Record_Not_Start = 11061,

			/* Resample failed*/
			Internal_Resamle_Failed = 11062,

			/* System no memory*/
			No_Memory = 11063,

			/* Memory not enough*/
			Memory_Not_Enough = 11064,
		};
	}
}