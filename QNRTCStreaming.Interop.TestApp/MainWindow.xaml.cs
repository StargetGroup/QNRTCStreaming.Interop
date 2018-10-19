using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
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
using Spiderman.Interop;
using System.IO;
using System.Threading;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Diagnostics;

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
            System.Windows.Forms.UserControl control = new System.Windows.Forms.UserControl();
            control.Width = 100;
            control.Height = 100;
            control.BackColor = System.Drawing.Color.Black;
            System.Windows.Forms.Integration.WindowsFormsHost host = new System.Windows.Forms.Integration.WindowsFormsHost();
            host.HorizontalAlignment = System.Windows.HorizontalAlignment.Stretch;
            host.VerticalAlignment = VerticalAlignment.Stretch;
            host.Child = control;
            _remoteVideo.Children.Add(host);
            RemoteHwnd = control.Handle;

            control = new System.Windows.Forms.UserControl();
            control.Width = 100;
            control.Height = 100;
            control.BackColor = System.Drawing.Color.Black;
            host = new System.Windows.Forms.Integration.WindowsFormsHost();
            host.HorizontalAlignment = System.Windows.HorizontalAlignment.Stretch;
            host.VerticalAlignment = VerticalAlignment.Stretch;
            host.Child = control;
            _localVideo.Children.Add(host);
            LocalHwnd = control.Handle;

            this._roomNameInput.Text = "test";
            this._userIdInput.Text = Guid.NewGuid().ToString().Split('-')[0];
            this.WC.FrameCaptured += this.OnWaveFrameCaptured;
            this.WC.Init(2);
            this.SC.FrameCaptured += this.OnScreenFrameCaptured;
            var screen = System.Windows.Forms.Screen.PrimaryScreen;
            this.SC.Init(screen.GetHandle(), 0, 0, screen.Bounds.Width, screen.Bounds.Height, 0);
        }

        private void OnScreenFrameCaptured(object sender, ScreenFrameEventArgs e)
        {
            this.Session.Video.InputVideoFrame(e.Pixels, e.DataSize, e.Width, e.Height, e.Timestamp, RTCVideoCaptureType.kRGB24, RTCVideoRotation.kVideoRotation_0, false);
        }

        private void OnWaveFrameCaptured(object sender, WaveFrameEventArgs e)
        {
            this.Session.Audio.InputAudioFrame(e.pData, e.DataSize, e.BitsPerSample, e.SampleRate, e.NumberOfChannels, e.NumberOfFrames);

            byte[] data = new byte[e.DataSize];
            Marshal.Copy(e.pData, data, 0, e.DataSize);

            if(channels != e.NumberOfChannels)
            {
                channels = e.NumberOfChannels;
            }
            if(sampleRate != e.SampleRate)
            {
                sampleRate = e.SampleRate;
            }
            if(bitsPerSample != e.BitsPerSample)
            {
                bitsPerSample = e.BitsPerSample;
            }

            fsWave.Write(data, 0, e.DataSize);
        }

        IntPtr RemoteHwnd;
        IntPtr LocalHwnd;
        public WaveCapturer WC = new WaveCapturer();
        public ScreenCapturer SC = new ScreenCapturer();
        private FileStream fsWave;
        private int channels;
        private int sampleRate;
        private int bitsPerSample;

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
            Session.SetLogParams(System.IO.Path.Combine(System.Windows.Forms.Application.StartupPath, "rtc-log", "rtc-log.txt"));
            var roomToken = "";
            if (string.IsNullOrEmpty(_token.Text) == false)
            {
                roomToken = _token.Text;
            }
            Session.UserStateChanged += this.OnUserStateChanged;
            Session.RoomListener.JoinResult += this.OnJoinResult;
            Session.RoomListener.RemotePublish += this.OnRemotePublish;
            Session.RoomListener.LocalPublishResult += this.OnLocalPublishResult;
            Session.RoomListener.RoomStateChanged += this.OnRoomStateChanged;
            //User.RoomListener.RemoteUserJoin += this.OnRemoteUserJoin;
            //User.RoomListener.RemoteUserLeave += this.OnRemoteUserLeave;
            //RTCAudioDeviceSetting setting = new RTCAudioDeviceSetting();
            //setting.DeviceIndex = 0;
            //setting.DeviceType = RTCWindowsDeviceType.wdt_DefaultDevice;
            //var ret = User.Audio.SetRecordingDevice(setting);
            var ret = Session.JoinRoom(roomToken);
        }

        private void OnRoomStateChanged(object sender, RTCRoomStateChangedEventArgs e)
        {
            Debug.Write(e.State.ToString());
        }

        private void OnJoinTestRoomButtonClick(object sender, RoutedEventArgs e)
        {
            Session.Init();
            Session.SetLogParams(System.IO.Path.Combine(System.Windows.Forms.Application.StartupPath, "rtc-log", "rtc-log.txt"));
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
            Session.SetLogParams(System.IO.Path.Combine(System.Windows.Forms.Application.StartupPath, "rtc-log", "rtc-log.txt"));
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

        private void OnLeaveRoomButtonClick(object sender, RoutedEventArgs e)
        {
            var ret = Session.LeaveRoom();
            _roomName.Text = "";
            _userId.Text = "";
            _publishAudio.IsChecked = false;
            _publishVideo.IsChecked = false;
            _inputAudio.IsChecked = false;
            _inputVideo.IsChecked = false;
            _muteAudio.IsChecked = false;
            _muteVideo.IsChecked = false;
            _userListView.ItemsSource = null;
        }

        private void OnLocalPublishResult(object sender, RTCRoomLocalPublishResultEventArgs e)
        {
            //Session.Room.Subscribe(Session.Room.GetUserId(), LocalHwnd);
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
                    System.Windows.MessageBox.Show(e.ErrorMsg);
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
                var myUserId = Session.Room.GetUserId();
                foreach (var user in e.Users)
                {
                    //if (user.UserId == Session.Room.GetUserId())
                    //{
                    //    Session.Room.Subscribe(user.UserId, LocalHwnd);
                    //}
                    //else
                    //{
                    if(user.VideoPublished || user.AudioPublished)
                    {
                        if(user.UserId != myUserId)
                        {
                            Session.Room.Subscribe(user.UserId, RemoteHwnd);
                        }
                    }

                    //}
                }

                //Session.Room.Subscribe(Session.Room.GetUserId(), LocalHwnd);

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
            if (bPublishAudio || bPublishVideo)
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
            SetVideo();
        }

        private void OnInputAudioClick(object sender, RoutedEventArgs e)
        {
            var bInputAudio = _inputAudio.IsChecked.Value;
            if(bInputAudio)
            {
                Session.Audio.EnableAudioFakeInput(true);
                this.fsWave = new FileStream("waveFile.pcm", FileMode.Create);
                WC.Start();
            }
            else
            {
                WC.Stop();
                Session.Audio.EnableAudioFakeInput(false);
                Thread.Sleep(TimeSpan.FromSeconds(1));
                this.fsWave.Flush();
                this.fsWave.Close();

                try
                {
                    WC.ConvertPcmToWavFile("waveFile.pcm", "waveFile.wav", channels, sampleRate, bitsPerSample);
                }
                catch { }
            }
        }

        public void SetVideo()
        {
            var bPublishAudio = _publishAudio.IsChecked.Value;
            var bPublishVideo = _publishVideo.IsChecked.Value;
            var bInputVideo = _inputVideo.IsChecked.Value;
            var vd = Session.Video.GetCameraDevices().FirstOrDefault();
            if (vd != null)
            {
                var cap = vd.Capabilitys.FirstOrDefault();
                if (bInputVideo)
                {
                    Session.Video.EnableVideoFakeCamera(true);
                    var screen = System.Windows.Forms.Screen.PrimaryScreen;
                    var camera_setting = new RTCCameraSetting();
                    camera_setting.RenderHwnd = LocalHwnd;
                    camera_setting.Width = screen.Bounds.Width;
                    camera_setting.Height = screen.Bounds.Height;
                    camera_setting.MaxFps = 15;
                    camera_setting.Bitrate = 500000;
                    camera_setting.DeviceName = "";
                    camera_setting.DeviceId = "";
                    var ret = Session.Video.SetCameraParams(camera_setting);
                    SC.Start();
                }
                else
                {
                    SC.Stop();
                    var camera_setting = new RTCCameraSetting();
                    camera_setting.RenderHwnd = LocalHwnd;
                    camera_setting.DeviceName = vd.DeviceName;
                    camera_setting.DeviceId = vd.DeviceId;
                    camera_setting.Width = cap.Width;
                    camera_setting.Height = cap.Height;
                    camera_setting.MaxFps = 15;
                    camera_setting.Bitrate = 500000;
                    Session.Video.EnableVideoFakeCamera(false);
                    var ret = Session.Video.SetCameraParams(camera_setting);
                }
            }
            if (bPublishAudio || bPublishVideo)
            {
                var ret = Session.Room.Publish(bPublishAudio, bPublishVideo);
                if(ret == (int)RTCErrorCode.Already_Published)
                {
                    Session.Room.UnPublish();
                    Session.Room.Publish(bPublishAudio, bPublishVideo);
                }
            }
            else
            {
                Session.Room.UnPublish();
            }
        }

        private void OnInputVideoClick(object sender, RoutedEventArgs e)
        {
            SetVideo();
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
            if(string.IsNullOrEmpty(_recordVolume.Text))
            {
                return;
            }
            var ret = Session.Audio.SetAudioVolume(RTCAudioDeviceType.adt_record,Convert.ToInt32(_recordVolume.Text));
        }

        private void OnPlayoutVolumeChanged(object sender, TextChangedEventArgs e)
        {
            if (string.IsNullOrEmpty(_playoutVolume.Text))
            {
                return;
            }
            var ret = Session.Audio.SetAudioVolume(RTCAudioDeviceType.adt_playout, Convert.ToInt32(_playoutVolume.Text));
        }
    }
}
