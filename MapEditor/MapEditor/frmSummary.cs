using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class frmSummary : Form
    {
        byte[] _objects;
        public frmSummary(byte[] _objects)
        {
            InitializeComponent();
            this._objects = _objects;
            LoadMatrix2Table();
        }

        protected void LoadMatrix2Table()
        {
            for (int i = 0; i < _objects.Length; ++i )
            {
                if(_objects[i] != 0)
                {
                    _dataGrid.Rows.Add("" + i,
                        "" + _objects[i],
                        "" + "Object_" + i);
                }
            }
        }
    }
}
