using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.IO;

namespace MapEditor
{
    public partial class MainForm : Form
    {
        #region Const..............
        const int START_BUTTON = 6;
        const byte MY_MAP = 111;
        #endregion

        public MainForm()
        {
            InitializeComponent();
            progressBar.Visible = false;
            lbReadingMap.Visible = false;
            _curIDObject = 0;
            _curButton = _bttNone;
            _bttNone.Focus();
            _mapSizeObjects = new Size(400, 12);
            _tileSizePixel = new Size(50, 50);
            _arrMap = new byte[_mapSizeObjects.Height, _mapSizeObjects.Width];
            _PictureBox1.Size = new Size(_mapSizeObjects.Width * _tileSizePixel.Width, _mapSizeObjects.Height * _tileSizePixel.Height);
            InitBoard();
            InitPicMain();

            Graphics _gPic = _PictureBox1.CreateGraphics();
            _PictureBox1.Image = _buff;
            _controlZQueue = new Queue<MapStatus>(MAX_QUEUE);
        }

        #region Xử lý trong Map.........
        protected Bitmap _buff;
        protected Bitmap _buffGrid;
        protected Bitmap _buffObj;
        protected Size _mapSizeObjects;
        protected Size _tileSizePixel;
        protected byte[,] _arrMap;
        protected byte _curIDObject;
        protected Button _curButton;
        protected Queue<MapStatus> _controlZQueue;
        const int MAX_QUEUE = 100;
        protected bool _isSaved = true;

        protected void InitBoard()
        {
            for (int i = 0; i < _mapSizeObjects.Height; ++i )
            {
                for (int j = 0; j < _mapSizeObjects.Width; ++j )
                {
                    _arrMap[i, j] = 0;
                }
            }
        }

        private void NewMap_Click(object sender, EventArgs e)
        {
            fmNewMap _newForm = new fmNewMap(_mapSizeObjects, _tileSizePixel);
            _newForm.ShowDialog(this);
            if (_newForm.OK)
            {
                _clickX = 0;
                _clickY = 0;
                _mapSizeObjects = new Size(_newForm.MapWidth, _newForm.MapHeigh);
                _tileSizePixel = new Size(_newForm.TileWidth, _newForm.TileHeigh);
                _arrMap = new byte[_mapSizeObjects.Height, _mapSizeObjects.Width];
                InitBoard();
                _PictureBox1.Size = new Size(_mapSizeObjects.Width * _tileSizePixel.Width, _mapSizeObjects.Height * _tileSizePixel.Height);
                InitPicMain();

                Graphics _gPic = _PictureBox1.CreateGraphics();
                _PictureBox1.Image = _buff;
                _controlZQueue.Clear();
            }
        }

        protected void InitPicMain()
        {
            try
            {
                Pen _pen = new Pen(Brushes.Black, 1);
                _buffObj = new Bitmap(_mapSizeObjects.Width * _tileSizePixel.Width, _mapSizeObjects.Height * _tileSizePixel.Height);
                _buffGrid = new Bitmap(_mapSizeObjects.Width * _tileSizePixel.Width, _mapSizeObjects.Height * _tileSizePixel.Height);
                _buff = new Bitmap(_mapSizeObjects.Width * _tileSizePixel.Width, _mapSizeObjects.Height * _tileSizePixel.Height);

                Graphics _g = Graphics.FromImage(_buffGrid);
                _g.Clear(Color.Maroon);
                for (int i = 0; i <= _mapSizeObjects.Height; ++i)
                {
                    int y = i * _tileSizePixel.Height;
                    _g.DrawLine(_pen, new Point(0, y), new Point(_mapSizeObjects.Width * _tileSizePixel.Width, y));
                }

                for (int j = 0; j <= _mapSizeObjects.Width; ++j)
                {
                    int x = j * _tileSizePixel.Width;
                    _g.DrawLine(_pen, new Point(x, 0), new Point(x, _mapSizeObjects.Height * _tileSizePixel.Height));
                }

                _g = Graphics.FromImage(_buff);
                _g.DrawImage(_buffGrid, new Point(0, 0));
            }
            catch
            {
                MessageBox.Show("The map is too large...\nPlease make another!");
                NewMap_Click(null, null);
            }
        }

        private void _PictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            _isMouseDown = false;
        }

        int _oldX = 0;
        int _oldY = 0;
        Rectangle _nowRect = new Rectangle(0, 0, 0, 0);
        private void _PictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            _isMouseDown = true;
            _oldX = e.X;
            _oldY = e.Y;
        }

        private void _PictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if(_isMouseDown)
            {
                _PictureBox1_MouseClick(sender, e);
            }
        }

        int _clickX = 0;
        int _clickY = 0;
        bool _isMouseDown = false;
        DateTime _startTime = DateTime.Now;
        private void _PictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (_isSaved)
            {
                _startTime = DateTime.Now;
                _isSaved = false;
            }
            Graphics _gBufferFinal = Graphics.FromImage(_buff);
            Graphics _gPictureBox = _PictureBox1.CreateGraphics();
            Graphics _gg = Graphics.FromImage(_buffObj);

            byte _tempObject = _curIDObject;
            Button _tempButton = _curButton;
            if(e.Button == MouseButtons.Right)
            {
                _curIDObject = 0;
                _curButton = _bttNone;
            }

            try
            {
                _gBufferFinal.DrawRectangle(new Pen(Brushes.Black, 1), new Rectangle(_clickX, _clickY, _tileSizePixel.Width, _tileSizePixel.Height));
                _gPictureBox.DrawRectangle(new Pen(Brushes.Black, 1), new Rectangle(_clickX, _clickY, _tileSizePixel.Width, _tileSizePixel.Height));

                //////////////////////////////////////////////////////////////////////////
                _clickX = _tileSizePixel.Width * (e.X / _tileSizePixel.Width);
                _clickY = _tileSizePixel.Height * (e.Y / _tileSizePixel.Height);
                
                Size _destSize = new Size();
                Image _img = null;

                if (_curButton != _bttNone)
                {
                    _img = _curButton.BackgroundImage;
                    _destSize = new Size(_img.Width, _img.Height);
                }
                else
                {
                    _img = null;
                    _destSize = new Size(_tileSizePixel.Width, _tileSizePixel.Height);
                }

                /*********************************** ControlZ *************************************/
                _zIndex = 0;
                if(_arrMap[e.Y / _tileSizePixel.Height, e.X / _tileSizePixel.Width] != _curIDObject)
                {
                    Bitmap _bitmap = new Bitmap(_destSize.Width, _destSize.Height);
                    Graphics _gTemp = Graphics.FromImage(_bitmap);
                    _gTemp.DrawImage(_buff,
                        new Rectangle(0, 0, _bitmap.Width, _bitmap.Height),
                        new Rectangle(_clickX, _clickY, _destSize.Width, _destSize.Height),
                        GraphicsUnit.Pixel);
                    MapStatus _ms = new MapStatus(e.Y / _tileSizePixel.Height,
                        e.X / _tileSizePixel.Width,
                        _arrMap[e.Y / _tileSizePixel.Height, e.X / _tileSizePixel.Width],
                        _bitmap);

                    if (_controlZQueue.Count >= MAX_QUEUE)
                        _controlZQueue.Dequeue();
                    _controlZQueue.Enqueue(_ms);
                }
                /************************************************************************/
                _arrMap[e.Y / _tileSizePixel.Height, e.X / _tileSizePixel.Width] = _curIDObject;
                /************************************************************************/
            
                if (_img != null)
                {// Vẽ hình mới
                    //_gg.FillRectangle(Brushes.Maroon, new Rectangle(_clickX, _clickY, _tileSize.Width, _tileSize.Height));
                    _gg.DrawImage(_img,
                        new Rectangle(_clickX, _clickY, _destSize.Width, _destSize.Height),
                        new Rectangle(0, 0, _img.Width, _img.Height),
                        GraphicsUnit.Pixel);
                    _gg.DrawRectangle(new Pen(Brushes.Black, 1), new Rectangle(_clickX, _clickY, _tileSizePixel.Width, _tileSizePixel.Height));
                }
                else
                {// Xóa hình trước đó
                    _gg.FillRectangle(Brushes.Maroon, 
                        new Rectangle(_clickX, _clickY, _tileSizePixel.Width, _tileSizePixel.Height));
                    _gg.DrawRectangle(new Pen(Brushes.Black, 1), 
                        new Rectangle(_clickX, _clickY, _tileSizePixel.Width, _tileSizePixel.Height));
                }

                _gBufferFinal.DrawImage(_buffGrid,
                    new Rectangle(_clickX, _clickY, _tileSizePixel.Width, _tileSizePixel.Height),
                    new Rectangle(_clickX, _clickY, _tileSizePixel.Width, _tileSizePixel.Height),
                    GraphicsUnit.Pixel);
                _gBufferFinal.DrawImage(_buffObj,
                    new Rectangle(_clickX - 1, _clickY - 1, _destSize.Width + 2, _destSize.Height + 2),
                    new Rectangle(_clickX - 1, _clickY - 1, _destSize.Width + 2, _destSize.Height + 2),
                    GraphicsUnit.Pixel);
                _gBufferFinal.DrawRectangle(new Pen(Brushes.White, 1), 
                    new Rectangle(_clickX, _clickY, _tileSizePixel.Width, _tileSizePixel.Height));

                _gPictureBox.DrawImage(_buff,
                    new Rectangle(_clickX - 1, _clickY - 1, _destSize.Width + 2, _destSize.Height + 2),
                    new Rectangle(_clickX - 1, _clickY - 1, _destSize.Width + 2, _destSize.Height + 2),
                    GraphicsUnit.Pixel);
            }
            catch
            {
                _isMouseDown = false;
            }
            _curIDObject = _tempObject;
            _curButton = _tempButton;
        }

        #endregion

        private void OpenMap_Click(object sender, EventArgs e)
        {
            OpenFileDialog _dialog = new OpenFileDialog();
            _dialog.Filter = "PNG| *.png";
            if (_dialog.ShowDialog(this) == DialogResult.Cancel)
                return;
            string _fileName = _dialog.FileName;
            Bitmap _openBitmap = new Bitmap(_fileName);
            ////////////////////Check if it is you map! and can be opened///////////////////////
            /************************************************************************/
            /*if(_openBitmap.GetPixel(0, 0).A != MY_MAP)
            {
                MessageBox.Show("It is not my map! Can not open it!\nPlease choose another!");
                return;
            }
             */
            /************************************************************************/
            //////////////////////////////Create new map////////////////////////////
            _mapSizeObjects = new Size(_openBitmap.Width, _openBitmap.Height);
            _tileSizePixel = new Size(_openBitmap.GetPixel(0, 0).G, _openBitmap.GetPixel(0, 0).R);

            lbReadingMap.Visible = true;
            progressBar.Visible = true;
            progressBar.Minimum = 0;
            progressBar.Increment(0);
            progressBar.Maximum = _mapSizeObjects.Width * _mapSizeObjects.Height;

            if (_tileSizePixel.Width == 0 || _tileSizePixel.Height == 0)
                _tileSizePixel.Width = _tileSizePixel.Height = 50;

            _arrMap = new byte[_mapSizeObjects.Height, _mapSizeObjects.Width];
            InitBoard();
            _PictureBox1.Size = new Size(_mapSizeObjects.Width * _tileSizePixel.Width, _mapSizeObjects.Height * _tileSizePixel.Height);
            InitPicMain();

            Graphics _gPic = _PictureBox1.CreateGraphics();
            _PictureBox1.Image = _buff;
            _controlZQueue.Clear();
            ////////////////////////////Load Object to ArrayMap////////////////////////////
            Bitmap _newBitmap = new Bitmap(_openBitmap);

            Rectangle bitmapRect = new Rectangle(0, 0, _newBitmap.Width, _newBitmap.Height);
            BitmapData bitmapData = _newBitmap.LockBits(bitmapRect, ImageLockMode.ReadWrite, _newBitmap.PixelFormat);
            IntPtr ptrBitmapDataOnMemory = bitmapData.Scan0;    //con trỏ đến dòng pixel đầu tiên trong Bitmap
            Int32 numberBytesOfBitMap = bitmapData.Stride * _newBitmap.Height;    //tổng số pixel trong Bitmap
            Byte[] rgbValuesArrayOfBitmap = new Byte[numberBytesOfBitMap];
            Marshal.Copy(ptrBitmapDataOnMemory, rgbValuesArrayOfBitmap, 0, numberBytesOfBitMap); //Copy ô nhớ từ ptrBitmapData và rgbValuesArrayOfBitmap bắt đầu từ 0 và lengh = numberBytesOfBitMap

            int k = 0;
            for (int i = 0; i < _mapSizeObjects.Height; ++i)
            {
                for (int j = 0; j < _mapSizeObjects.Width; ++j)
                {
                    if (rgbValuesArrayOfBitmap[k] != 0)
                    {
                        _arrMap[i, j] = rgbValuesArrayOfBitmap[k];
                    }
                    k += 4;
                }
            }

            Marshal.Copy(rgbValuesArrayOfBitmap, 0, ptrBitmapDataOnMemory, numberBytesOfBitMap);
            _newBitmap.UnlockBits(bitmapData);
            
            //////////////////////////////Draw Object to bitmap///////////////////////
            Graphics _gBufferFinal = Graphics.FromImage(_buff);
            Graphics _gDestination = _PictureBox1.CreateGraphics();
            Graphics _gBuffObject = Graphics.FromImage(_buffObj);
            ////////////////////////////// Find out CurrentButton ///////////////////////////
            int iii = 0;
            int jjj = 0;
            byte idObject = 0;

            for (int i = 0; i < _mapSizeObjects.Height; ++i )
            {
                for (int j = 0; j < _mapSizeObjects.Width; ++j )
                {
                    progressBar.Value = i * j;
                    progressBar.PerformStep();
                    iii = i;
                    jjj = j;
                    idObject = _arrMap[i, j];
                    if (idObject == 0)
                        continue;
                    //////////////////////////////////////////////////////////////////////////
                    _curIDObject = idObject;
                    _clickX = jjj * _tileSizePixel.Width;
                    _clickY = iii * _tileSizePixel.Height;
                    if(idObject == 255)
                    {
                        _curButton = _bttPlayer;
                    }
                    else if (idObject <= 50) // BackGround
                    {
                        for (int ii = 0; ii < _flowLayoutBackground.Controls.Count; ++ii)
                        {
                            Button _bt = (Button)_flowLayoutBackground.Controls[ii];
                            if (_bt == _bttNone || _bt == _bttAddObject)
                                continue;
                            if (byte.Parse(_bt.Text) == idObject)
                            {
                                _curButton = _bt;
                            }
                        }
                    }
                    else if (idObject <= 100) // Boss-Master
                    {
                        for (int ii = 0; ii < _flowLayoutBossMaster.Controls.Count; ++ii)
                        {
                            Button _bt = (Button)_flowLayoutBossMaster.Controls[ii];
                            if (byte.Parse(_bt.Text) == idObject)
                            {
                                _curButton = _bt;
                            }
                        }
                    }
                    else if (idObject <= 150)
                    {
                        for (int ii = 0; ii < _flowLayoutMonster.Controls.Count; ++ii)
                        {
                            Button _bt = (Button)_flowLayoutMonster.Controls[ii];
                            if (byte.Parse(_bt.Text) == idObject)
                            {
                                _curButton = _bt;
                            }
                        }
                    }
                    else if (idObject <= 200)
                    {
                        for (int ii = 0; ii < _flowLayoutBGUnCollision.Controls.Count; ++ii)
                        {
                            Button _bt = (Button)_flowLayoutBGUnCollision.Controls[ii];
                            if (byte.Parse(_bt.Text) == idObject)
                            {
                                _curButton = _bt;
                            }
                        }
                    }
                    ////////////////////////////// Draw each object /////////////////////////////////
                    _gBuffObject.DrawImage(_curButton.BackgroundImage, new Rectangle(_clickX, _clickY, _curButton.BackgroundImage.Width, _curButton.BackgroundImage.Height));
                    _gBufferFinal.DrawImage(_curButton.BackgroundImage, new Rectangle(_clickX, _clickY, _curButton.BackgroundImage.Width, _curButton.BackgroundImage.Height));
                    //////////////////////////////////////////////////////////////////////////
                }
            }
            ////////////////////////// Draw all to PictureBox //////////////////////////////////
            _gDestination.DrawImage(_buff, new Point(0, 0));
            progressBar.Visible = false;
            lbReadingMap.Visible = false;
            MessageBox.Show("Read map OK!");
        }

        int _countButton = START_BUTTON;
        int _tabIndex = START_BUTTON;
        private void AddButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog _dialog = new OpenFileDialog();
            _dialog.Title = "Choose a PNG image";
            _dialog.Filter = "PNG | *.png";
            _dialog.Multiselect = true;
            if (_dialog.ShowDialog(this) == DialogResult.Cancel)
                return;
            string[] _filename = _dialog.FileNames;

            for (int i = 0; i < _filename.Length; ++i )
            {
                Bitmap _bm0 = new Bitmap(_filename[i]);
                Bitmap _bm = new Bitmap(_bm0);
                
                Button _newButton = new Button();

                _newButton.BackgroundImage = _bm;
                _newButton.BackgroundImageLayout = ImageLayout.Zoom;
                _newButton.BackColor = System.Drawing.Color.Blue;
                _newButton.Font = new System.Drawing.Font("Motorwerk", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                _newButton.ForeColor = System.Drawing.Color.Yellow;
                _newButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
                _newButton.Name = "_bttObject_" + _countButton++;
                _newButton.Size = new System.Drawing.Size(48, 48);
                _newButton.TabIndex = _tabIndex++;
                _newButton.UseVisualStyleBackColor = false;
                _newButton.Text = "" + _countButton;
                _newButton.Click += new System.EventHandler(this.ButtonObjects_Click);
                _flowLayoutBackground.Controls.Add(_newButton);
            }
        }

        private void ButtonObjects_Click(object _obj, EventArgs e)
        {
            _curButton = (Button)_obj;
            _curIDObject = byte.Parse(_curButton.Text);
        }

        int _zIndex = 0;
        private void Undo_Click(object sender, EventArgs e)
        {
            try
            {
                _zIndex++;
                MapStatus _ms = _controlZQueue.ToArray()[(_controlZQueue.Count - _zIndex)];
                _arrMap[_ms.i, _ms.j] = _ms.value;
                Graphics _g = Graphics.FromImage(_buffObj);
                _g.DrawImage(_ms.bitmap, new Point(_ms.j * _tileSizePixel.Width, _ms.i * _tileSizePixel.Height));
                _g = Graphics.FromImage(_buff);
                _g.DrawImage(_ms.bitmap, new Point(_ms.j * _tileSizePixel.Width, _ms.i * _tileSizePixel.Height));
                _g = _PictureBox1.CreateGraphics();
                _g.DrawImage(_ms.bitmap, new Point(_ms.j * _tileSizePixel.Width, _ms.i * _tileSizePixel.Height));
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("Can not Undo...");
            }
        }

        private void Exit_Click(object sender, EventArgs e)
        {
            if (_isSaved == false)
            {
                DialogResult _res = MessageBox.Show("Eh! Chưa lưu cái map kia ba!\nCông kỷ làm từ hồi " + _startTime.Hour + ":" + _startTime.Minute + " đó!", "Huhm...", MessageBoxButtons.YesNoCancel);
                if (_res == DialogResult.Yes)
                {
                    SaveAsBitMap_Click(null, null);
                }
                else if (_res == DialogResult.No)
                {
                    MessageBox.Show("Cái thằng hâm!");
                    Application.Exit();
                }
                else
                {
                    return;
                }
            }
            else
            {
                if (DateTime.Now.Hour >= 23 || DateTime.Now.Hour <= 4)
                    MessageBox.Show("Chào nhá ku!\n Chúc ngủ ngon!\n Chú mày \"trâu quá\" !");
                else
                    MessageBox.Show("Chào nhá ku! Hê hê!");
                Application.Exit();
            }
        }

        private void About_Click(object sender, EventArgs e)
        {
            frmAboutUs _f = new frmAboutUs();
            _f.ShowDialog(this);
        }

        private void Help_Click(object sender, EventArgs e)
        {
            frmHelp _f = new frmHelp();
            _f.ShowDialog(this);
        }

        private void SaveAsImage_Click(object sender, EventArgs e)
        {
            _isSaved = true;
            SaveFileDialog _dialog = new SaveFileDialog();
            _dialog.Filter = "PNG | *.png";
            _dialog.FileName = "FindingPrincess_Map.png";
            if (_dialog.ShowDialog(this) == DialogResult.Cancel)
                return;
            string _filename = _dialog.FileName;
            _buffObj.Save(_filename, ImageFormat.Png);
        }

        private void SaveAsText_Click(object sender, EventArgs e)
        {
            _isSaved = true;
            SaveFileDialog _dialog = new SaveFileDialog();
            _dialog.Filter = "PhamTanLong | *.ptl";
            if (_dialog.ShowDialog(this) == DialogResult.Cancel)
                return;
            string _filename = _dialog.FileName;

            StreamWriter _sw = new StreamWriter(_filename);

            for (int i = 0; i < _mapSizeObjects.Height; ++i)
            {
                for (int j = 0; j < _mapSizeObjects.Width; ++j)
                {
                    _sw.Write((_arrMap[i, j] + " ").PadRight(3));
                }
                _sw.WriteLine();
            }
            _sw.Flush();
            _sw.Close();
        }

        protected int _count2Save = 0;
        private void SaveAsBitMap_Click(object sender, EventArgs e)
        {
            Bitmap _saveBitmap = new Bitmap(_mapSizeObjects.Width, _mapSizeObjects.Height);
            Rectangle bitmapRect = new Rectangle(0, 0, _saveBitmap.Width, _saveBitmap.Height);
            BitmapData bitmapData = _saveBitmap.LockBits(bitmapRect, ImageLockMode.ReadWrite, _saveBitmap.PixelFormat);
            IntPtr ptrBitmapDataOnMemory = bitmapData.Scan0;    //con trỏ đến dòng pixel đầu tiên trong Bitmap
            Int32 numberBytesOfBitMap = bitmapData.Stride * _saveBitmap.Height;    //tổng số pixel trong Bitmap
            Byte[] rgbValuesArrayOfBitmap = new Byte[numberBytesOfBitMap];
            Marshal.Copy(ptrBitmapDataOnMemory, rgbValuesArrayOfBitmap, 0, numberBytesOfBitMap); //Copy ô nhớ từ ptrBitmapData và rgbValuesArrayOfBitmap bắt đầu từ 0 và lengh = numberBytesOfBitMap

            //////////////////////////////////////////////////////////////////////////
            int k = 0;
            for (int i = 0; i < _mapSizeObjects.Height; ++i)
            {
                for (int j = 0; j < _mapSizeObjects.Width; ++j)
                {
                    if (_arrMap[i, j] != 0)
                    {
                        rgbValuesArrayOfBitmap[k] = (byte)(_arrMap[i, j]);
                        rgbValuesArrayOfBitmap[k + 1] = 0;
                        rgbValuesArrayOfBitmap[k + 2] = 0;
                        rgbValuesArrayOfBitmap[k + 3] = 255;
                    }
                    k += 4;
                }
            }
            ////////////////////////Đưa số kích thước từng Object vào 2 biến green-red của pixel đầu tiên//////////////////////////
            rgbValuesArrayOfBitmap[1] = (byte)_tileSizePixel.Width;
            rgbValuesArrayOfBitmap[2] = (byte)_tileSizePixel.Height;
            ////////////////////////Đánh dấu rằng đây là 1 file Map hợp lệ có thể mở được//////////////////////////////////////////////////
            rgbValuesArrayOfBitmap[3] = (byte)MY_MAP;

            //////////////////////////////////////////////////////////////////////////

            Marshal.Copy(rgbValuesArrayOfBitmap, 0, ptrBitmapDataOnMemory, numberBytesOfBitMap);
            _saveBitmap.UnlockBits(bitmapData);
            //--------------------------------------------------------------------
            Begin:
            try
            {
                SaveFileDialog _dialog = new SaveFileDialog();
                _dialog.Filter = "PNG | *.png";
                _dialog.FileName = "MAP" + _count2Save++;
                if (_dialog.ShowDialog(this) == DialogResult.Cancel)
                    return;
                string _filename = _dialog.FileName;
                _saveBitmap.Save(_filename, ImageFormat.Png);
                _isSaved = true;
            }
            catch
            {
                MessageBox.Show("That file is being used!");
                goto Begin;
            }
        }

        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Exit_Click(null, null);
        }

        private void Summary_Click(object sender, EventArgs e)
        {
            byte[] _objects = new byte[256];
            for (int i = 0; i < _mapSizeObjects.Height; ++i )
            {
                for (int j = 0; j < _mapSizeObjects.Width; ++j )
                {
                    if(_arrMap[i, j] != 0)
                        _objects[_arrMap[i, j]]++;
                }
            }
            frmSummary _form = new frmSummary(_objects);
            _form.Show();
        }

    }
}
