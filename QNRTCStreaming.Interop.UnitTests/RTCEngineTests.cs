using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using QNRTCStreaming.Interop;

namespace QNRTCStreaming.Interop.UnitTests
{
    [TestClass]
    public class RTCEngineTests
    {
        [TestMethod]
        public void TestInit()
        {
            var ret = RTCEngine.Init();
        }
    }
}
