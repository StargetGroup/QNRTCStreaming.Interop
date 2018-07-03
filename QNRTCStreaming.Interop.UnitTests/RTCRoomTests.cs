using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using QNRTCStreaming.Interop;

namespace QNRTCStreaming.Interop.UnitTests
{
    [TestClass]
    public class RTCRoomTests
    {
        [TestMethod]
        public RTCRoom TestObtainRoomInterface()
        {
            var room = RTCRoom.ObtainRoomInterface();
            return room;
        }

        [TestMethod]
        public static RTCAudio TestObtainAudioInterface()
        {
            var room = RTCRoom.ObtainRoomInterface();
            var audio = room.ObtainAudioInterface();
            return audio;
        }

        [TestMethod]
        public void TestSetRoomListener()
        {
            var room = RTCRoom.ObtainRoomInterface();
            RTCRoomListener listener = new RTCRoomListener();
            room.SetRoomListener(listener);
        }
    }
}
