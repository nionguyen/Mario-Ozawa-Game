using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class fmNewMap : Form
    {
        protected bool _isOK = false;
        public fmNewMap(Size _ms, Size _ts)
        {
            InitializeComponent();
            _numMapWidth.Value = _ms.Width;
            _numMapHeigh.Value = _ms.Height;
            _numTileWidth.Value = _ts.Width;
            _numTileHeigh.Value = _ts.Height;
        }
#region Properties.................
        public bool OK
        {
            get
            {
                return _isOK;
            }
        }

        public int MapWidth
        {
            get { return (int)_numMapWidth.Value; }
        }

        public int MapHeigh
        {
            get { return (int)_numMapHeigh.Value; }
        }

        public int TileWidth
        {
            get { return (int)_numTileWidth.Value; }
        }

        public int TileHeigh
        {
            get { return (int)_numTileHeigh.Value; }
        }

        public string MapName
        {
            get { return _tbMapName.Text; }
        }
#endregion

        private void bttOK_Click(object sender, EventArgs e)
        {
            _isOK = true;
            this.Close();
        }

        private void bttCancel_Click(object sender, EventArgs e)
        {
            _isOK = false;
            this.Close();
        }

        

    }
}
