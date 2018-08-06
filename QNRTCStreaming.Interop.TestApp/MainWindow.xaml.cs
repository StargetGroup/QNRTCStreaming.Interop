using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using pili_sdk_csharp.pili_common;

namespace QNRTCStreaming.Interop.TestApp
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            RTCEngine.Init();
            System.Windows.Forms.UserControl control = new System.Windows.Forms.UserControl();
            control.Width = 100;
            control.Height = 100;
            control.BackColor = System.Drawing.Color.Black;
            System.Windows.Forms.Integration.WindowsFormsHost host = new System.Windows.Forms.Integration.WindowsFormsHost();
            host.HorizontalAlignment = HorizontalAlignment.Stretch;
            host.VerticalAlignment = VerticalAlignment.Stretch;
            host.Child = control;
            _remoteVideo.Children.Add(host);
            RemoteHwnd = control.Handle;

            control = new System.Windows.Forms.UserControl();
            control.Width = 100;
            control.Height = 100;
            control.BackColor = System.Drawing.Color.Black;
            host = new System.Windows.Forms.Integration.WindowsFormsHost();
            host.HorizontalAlignment = HorizontalAlignment.Stretch;
            host.VerticalAlignment = VerticalAlignment.Stretch;
            host.Child = control;
            _localVideo.Children.Add(host);
            LocalHwnd = control.Handle;

            this._roomNameInput.Text = "test";
            this._userIdInput.Text = Guid.NewGuid().ToString().Split('-')[0];
        }

        IntPtr RemoteHwnd;
        IntPtr LocalHwnd;

        RTCSession Session = new Interop.RTCSession();
        //RTCRoom Room { get; set; }
        //RTCAudio Audio { get; set; }
        //RTCRoomListener RoomListener { get; set; } = new RTCRoomListener();
        //RTCAudioListener AudioListener { get; set; } = new RTCAudioListener();

        //private void OnInitButtonClick(object sender, RoutedEventArgs e)
        //{
        //    var ret = RTCEngine.Init();
        //    if(ret == 0)
        //    {
        //        MessageBox.Show("初始化成功");
        //    }
        //    else
        //    {
        //        MessageBox.Show("初始化失败");
        //    }
        //}
        //private void OnCrateRoomButtonClick(object sender, RoutedEventArgs e)
        //{
        //    Room = RTCRoom.ObtainRoomInterface();
        //    Audio = Room.ObtainAudioInterface();
        //    Room.SetRoomListener(RoomListener);
        //    Audio.SetAudioListener(AudioListener);
        //    RoomListener.JoinResult += this.RoomListener_JoinResult;
        //    RoomListener.LocalPublishResult += this.RoomListener_LocalPublishResult;
        //}

        //private void RoomListener_LocalPublishResult(object sender, RTCRoomLocalPublishResultEventArgs e)
        //{
        //    //throw new NotImplementedException();
        //}

        //private void RoomListener_JoinResult(object sender, RTCRoomJoinResultEventArgs e)
        //{
        //    //throw new NotImplementedException();
        //}

        private void OnJoinRoomButtonClick(object sender, RoutedEventArgs e)
        {
            Session.Init();
            var roomToken = "";
            if(string.IsNullOrEmpty(_token.Text) == false)
            {
                roomToken = _token.Text;
            }
            Session.UserStateChanged += this.OnUserStateChanged;
            Session.RoomListener.JoinResult += this.OnJoinResult;
            Session.RoomListener.RemotePublish += this.OnRemotePublish;
            Session.RoomListener.LocalPublishResult += this.OnLocalPublishResult;
            //User.RoomListener.RemoteUserJoin += this.OnRemoteUserJoin;
            //User.RoomListener.RemoteUserLeave += this.OnRemoteUserLeave;
            //RTCAudioDeviceSetting setting = new RTCAudioDeviceSetting();
            //setting.DeviceIndex = 0;
            //setting.DeviceType = RTCWindowsDeviceType.wdt_DefaultDevice;
            //var ret = User.Audio.SetRecordingDevice(setting);
            var ret = Session.JoinRoom(roomToken);
        }

        private void OnJoinTestRoomButtonClick(object sender, RoutedEventArgs e)
        {
            Session.Init();
            var roomToken = Session.Room.CreateTestRoomToken(_roomNameInput.Text, _userIdInput.Text, true);
            Session.UserStateChanged += this.OnUserStateChanged;
            Session.RoomListener.JoinResult += this.OnJoinResult;
            Session.RoomListener.RemotePublish += this.OnRemotePublish;
            Session.RoomListener.LocalPublishResult += this.OnLocalPublishResult;
            //User.RoomListener.RemoteUserJoin += this.OnRemoteUserJoin;
            //User.RoomListener.RemoteUserLeave += this.OnRemoteUserLeave;
            //RTCAudioDeviceSetting setting = new RTCAudioDeviceSetting();
            //setting.DeviceIndex = 0;
            //setting.DeviceType = RTCWindowsDeviceType.wdt_DefaultDevice;
            //var ret = User.Audio.SetRecordingDevice(setting);
            var ret = Session.JoinRoom(roomToken);
        }

        private void OnJoinProductionRoomButtonClick(object sender, RoutedEventArgs e)
        {
            Session.Init();
            var roomToken = Session.Room.CreateRoomToken(_roomNameInput.Text, _userIdInput.Text, true, DateTime.Now.AddDays(2), _appIdInput.Text, _accessKeyInput.Text, _secretKeyInput.Text);
            Session.UserStateChanged += this.OnUserStateChanged;
            Session.RoomListener.JoinResult += this.OnJoinResult;
            Session.RoomListener.RemotePublish += this.OnRemotePublish;
            Session.RoomListener.LocalPublishResult += this.OnLocalPublishResult;
            //User.RoomListener.RemoteUserJoin += this.OnRemoteUserJoin;
            //User.RoomListener.RemoteUserLeave += this.OnRemoteUserLeave;
            //RTCAudioDeviceSetting setting = new RTCAudioDeviceSetting();
            //setting.DeviceIndex = 0;
            //setting.DeviceType = RTCWindowsDeviceType.wdt_DefaultDevice;
            //var ret = User.Audio.SetRecordingDevice(setting);
            var ret = Session.JoinRoom(roomToken);
        }

        private void OnLocalPublishResult(object sender, RTCRoomLocalPublishResultEventArgs e)
        {
            Session.Room.Subscribe(Session.Room.GetUserId(), LocalHwnd);
        }

        private void OnUserStateChanged(object sender, RTCSessionUserStateChangedEventArgs e)
        {
            this.Dispatcher.Invoke(() =>
            {
                _userListView.ItemsSource = null;
                _userListView.ItemsSource = e.Users;//.Select(el => el.UserId);
            });
        }

        //private void OnRemoteUserLeave(object sender, RTCRoomRemoteUserLeaveEventArgs e)
        //{
        //    this.Dispatcher.Invoke(() =>
        //    {
        //        var users = _userListView.ItemsSource as List<string>;
        //        users.Remove(e.UserId);
        //        _userListView.ItemsSource = null;
        //        _userListView.ItemsSource = users;
        //    });
        //}

        //private void OnRemoteUserJoin(object sender, RTCRoomRemoteUserJoinEventArgs e)
        //{
        //    this.Dispatcher.Invoke(() =>
        //    {
        //        var users = _userListView.ItemsSource as List<string>;
        //        users.Add(e.UserId);
        //        _userListView.ItemsSource = null;
        //        _userListView.ItemsSource = users;
        //    });
        //}

        private void OnRemotePublish(object sender, RTCRoomRemotePublishEventArgs e)
        {
            Session.Room.Subscribe(e.UserId, RemoteHwnd);
        }

        private void OnJoinResult(object sender, RTCRoomJoinResultEventArgs e)
        {
            this.Dispatcher.Invoke(() =>
            {
                if (string.IsNullOrEmpty(e.ErrorMsg) == false)
                {
                    MessageBox.Show(e.ErrorMsg);
                }
                _roomName.Text = Session.Room.GetRoomName();
                _userId.Text = Session.Room.GetUserId();

                var record = Session.Audio.GetRecordingDevices().FirstOrDefault();
                _record.Text = record?.DeviceName;

                var playout = Session.Audio.GetPlayoutDevices().FirstOrDefault();
                _playout.Text = playout?.DeviceName;

                var camera = Session.Video.GetCameraDevices().FirstOrDefault();
                _camera.Text = camera?.DeviceName;

                _recordVolume.Text = Session.Audio.GetAudioVolume(RTCAudioDeviceType.adt_record).ToString();
                _playoutVolume.Text = Session.Audio.GetAudioVolume(RTCAudioDeviceType.adt_playout).ToString();

                foreach(var user in e.Users)
                {
                    //if (user.UserId == Session.Room.GetUserId())
                    //{
                    //    Session.Room.Subscribe(user.UserId, LocalHwnd);
                    //}
                    //else
                    //{
                        Session.Room.Subscribe(user.UserId, RemoteHwnd);
                    //}
                }

                Session.Room.Subscribe(Session.Room.GetUserId(), LocalHwnd);

                //var users = e.Users.Select(el => el.UserId).ToList();
                //_userListView.ItemsSource = users;
            });
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            this.Session.LeaveRoom();
        }

        private void OnPublishAudioClick(object sender, RoutedEventArgs e)
        {
            var bPublishAudio = _publishAudio.IsChecked.Value;
            var bPublishVideo = _publishVideo.IsChecked.Value;
            Session.Room.UnPublish();
            if(bPublishAudio || bPublishVideo)
            {
                var vd = Session.Video.GetCameraDevices().FirstOrDefault();
                if (vd != null)
                {
                    var cap = vd.Capabilitys.FirstOrDefault();
                    RTCCameraSetting camera_setting = new RTCCameraSetting();
                    camera_setting.RenderHwnd = LocalHwnd;
                    camera_setting.DeviceName = vd.DeviceName;
                    camera_setting.DeviceId = vd.DeviceId;
                    camera_setting.Width = cap.Width;
                    camera_setting.Height = cap.Height;
                    camera_setting.MaxFps = 15;
                    camera_setting.Bitrate = 500000;
                    Session.Video.SetCameraParams(camera_setting);
                }
                //var recordDevice = Session.Audio.GetRecordingDevices().FirstOrDefault();
                //RTCAudioDeviceSetting audio_setting = new RTCAudioDeviceSetting();
                //audio_setting.DeviceIndex = (short)recordDevice.DeviceIndex;
                //audio_setting.DeviceType = RTCWindowsDeviceType.wdt_DefaultDevice;
                //var ret = Session.Audio.SetRecordingDevice(audio_setting);

                //var playoutDevice = Session.Audio.GetPlayoutDevices().FirstOrDefault();
                //audio_setting = new RTCAudioDeviceSetting();
                //audio_setting.DeviceIndex = (short)playoutDevice.DeviceIndex;
                //audio_setting.DeviceType = RTCWindowsDeviceType.wdt_DefaultDevice;
                //ret = Session.Audio.SetPlayoutDevice(audio_setting);
                Session.Room.Publish(bPublishAudio, bPublishVideo);
            }
        }

        private void OnPublishVideoClick(object sender, RoutedEventArgs e)
        {
            var bPublishAudio = _publishAudio.IsChecked.Value;
            var bPublishVideo = _publishVideo.IsChecked.Value;
            Session.Room.UnPublish();
            if (bPublishAudio || bPublishVideo)
            {
                var vd = Session.Video.GetCameraDevices().FirstOrDefault();
                if(vd != null)
                {
                    var cap = vd.Capabilitys.FirstOrDefault();
                    RTCCameraSetting camera_setting = new RTCCameraSetting();
                    camera_setting.RenderHwnd = LocalHwnd;
                    camera_setting.DeviceName = vd.DeviceName;
                    camera_setting.DeviceId = vd.DeviceId;
                    camera_setting.Width = cap.Width;
                    camera_setting.Height = cap.Height;
                    camera_setting.MaxFps = 15;
                    camera_setting.Bitrate = 500000;
                    Session.Video.SetCameraParams(camera_setting);
                }
                //var recordDevice = Session.Audio.GetRecordingDevices().FirstOrDefault();
                //RTCAudioDeviceSetting audio_setting = new RTCAudioDeviceSetting();
                //audio_setting.DeviceIndex = (short)recordDevice.DeviceIndex;
                //audio_setting.DeviceType = RTCWindowsDeviceType.wdt_DefaultDevice;
                //var ret = Session.Audio.SetRecordingDevice(audio_setting);

                //var playoutDevice = Session.Audio.GetPlayoutDevices().FirstOrDefault();
                //audio_setting = new RTCAudioDeviceSetting();
                //audio_setting.DeviceIndex = (short)playoutDevice.DeviceIndex;
                //audio_setting.DeviceType = RTCWindowsDeviceType.wdt_DefaultDevice;
                //ret = Session.Audio.SetPlayoutDevice(audio_setting);
                Session.Room.Publish(bPublishAudio, bPublishVideo);
            }
        }

        private void OnMuteAudioClick(object sender, RoutedEventArgs e)
        {
            var bMuteAudio = _muteAudio.IsChecked.Value;
            var ret = Session.Room.MuteAudio(bMuteAudio);
        }

        private void OnMuteVideoClick(object sender, RoutedEventArgs e)
        {
            var bMuteVideo = _muteVideo.IsChecked.Value;
            var ret = Session.Room.MuteVideo(bMuteVideo);
        }

        private void OnRecordVolumeChanged(object sender, TextChangedEventArgs e)
        {
            var ret = Session.Audio.SetAudioVolume(RTCAudioDeviceType.adt_record,Convert.ToInt32(_recordVolume.Text));
        }

        private void OnPlayoutVolumeChanged(object sender, TextChangedEventArgs e)
        {
            var ret = Session.Audio.SetAudioVolume(RTCAudioDeviceType.adt_playout, Convert.ToInt32(_playoutVolume.Text));
        }
    }
}
