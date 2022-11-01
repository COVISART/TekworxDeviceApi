using System;
using System.Collections.Generic;

namespace WrapperClasses
{
    public struct BOARDCAPSlib
    {
        public int nLEDCount; // Total number of LED outputs
        public int nLEDFirst; // First LED output number
        public int nLEDLast; // Last LED output number
        public int nSwitchCount; // Total number of switches
        public int nSwitchFirst; // First switch input number
        public int nSwitchLast; // Last switch input number
        public int n7SegmentCount; // Total number of 7 Segment output (future)
        public int n7SegmentFirst; // First 7 Segment output number (future)
        public int n7SegmentLast; // Last 7 Segment output number (future)
        public int nDatalineCount; // Total datalines
        public int nDatalineFirst; // First dataline number
        public int nDatalineLast; // Last dataline number
        public int nReserved1;
        public int nReserved2;
        public int nReserved3;
        public int nReserved4;
        public int nReserved5;
        public int nReserved6;
        public int nReserved7;
        public int nReserved8;
        public int nReserved9;
        public string szBoardType; // Null-terminated string containing the board type identifier
        public string szManufactureDate; // Null-terminated string containing the manufacture date of the board
        public int dwFeatures; // Features that are currently enabled on the board
        public int nUpdateLevel; // Update level that is currently applied to this board
    }
    public static class CallBack
    {
        public static List<BoardData> SwitchVariable = new List<BoardData>();

        public static void switch_callback_invoker(uint sessionId, int nSwitch, int nDir)
        {
            SwitchCallback?.Invoke(sessionId, nSwitch, nDir);
        }

        public static event Action<uint, int, int> SwitchCallback;
    }

    public class BoardData
    {
        public uint SessionId;
        public int SwitchNo;
        public int Value;
    }
}
