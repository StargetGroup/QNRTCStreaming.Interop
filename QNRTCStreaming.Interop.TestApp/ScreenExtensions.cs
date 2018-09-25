using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace System.Windows.Forms
{
    public static class ScreenExtensions
    {

        [DllImport("User32.dll")]
        public static extern IntPtr MonitorFromPoint([In]POINTSTRUCT pt, [In]uint dwFlags);
        const int MONITOR_DEFAULTTONEAREST = 2;

        public static IntPtr GetHandle(this Screen screen)
        {
            var point = new Point(screen.Bounds.Left + 1, screen.Bounds.Top + 1);
            var pt = new POINTSTRUCT((int)point.X, (int)point.Y);
            var hmonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
            return hmonitor;
        }

    }

    [StructLayout(LayoutKind.Sequential)]
    public struct POINTSTRUCT
    {
        public int x;
        public int y;
        public POINTSTRUCT(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }
}
