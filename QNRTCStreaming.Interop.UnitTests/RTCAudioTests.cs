using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace QNRTCStreaming.Interop.UnitTests
{
    [TestClass]
    public class RTCAudioTests
    {
        [TestMethod]
        public void TestSetAudioListener()
        {
            var audio = RTCRoomTests.TestObtainAudioInterface();
            RTCAudioListener listener = new RTCAudioListener();
            audio.SetAudioListener(listener);
        }
    }
}
