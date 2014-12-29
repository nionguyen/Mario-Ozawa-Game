using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace MapEditor
{
    public class MapStatus
    {
        public int i;
        public int j;
        public byte value;
        public Bitmap bitmap;

        public MapStatus(int _i, int _j, byte _value, Bitmap _bitmap)
        {
            i = _i;
            j = _j;
            value = _value;
            bitmap = _bitmap;
        }
    }
}
