namespace MapEditor
{
    partial class fmNewMap
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this._tbMapName = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this._numMapHeigh = new System.Windows.Forms.NumericUpDown();
            this._numMapWidth = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this._numTileWidth = new System.Windows.Forms.NumericUpDown();
            this._numTileHeigh = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.bttCancel = new System.Windows.Forms.Button();
            this.bttOK = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this._numMapHeigh)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this._numMapWidth)).BeginInit();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this._numTileWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this._numTileHeigh)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Map name";
            // 
            // _tbMapName
            // 
            this._tbMapName.Location = new System.Drawing.Point(106, 12);
            this._tbMapName.Name = "_tbMapName";
            this._tbMapName.Size = new System.Drawing.Size(149, 20);
            this._tbMapName.TabIndex = 1;
            this._tbMapName.Text = "Map_";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this._numMapHeigh);
            this.groupBox1.Controls.Add(this._numMapWidth);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Location = new System.Drawing.Point(15, 48);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(240, 101);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Map Size";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(210, 59);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(25, 13);
            this.label7.TabIndex = 7;
            this.label7.Text = "tiles";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(210, 33);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(25, 13);
            this.label6.TabIndex = 6;
            this.label6.Text = "tiles";
            // 
            // _numMapHeigh
            // 
            this._numMapHeigh.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this._numMapHeigh.Location = new System.Drawing.Point(91, 57);
            this._numMapHeigh.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this._numMapHeigh.Name = "_numMapHeigh";
            this._numMapHeigh.Size = new System.Drawing.Size(113, 20);
            this._numMapHeigh.TabIndex = 5;
            this._numMapHeigh.Value = new decimal(new int[] {
            12,
            0,
            0,
            0});
            // 
            // _numMapWidth
            // 
            this._numMapWidth.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this._numMapWidth.Location = new System.Drawing.Point(91, 31);
            this._numMapWidth.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this._numMapWidth.Name = "_numMapWidth";
            this._numMapWidth.Size = new System.Drawing.Size(113, 20);
            this._numMapWidth.TabIndex = 4;
            this._numMapWidth.Value = new decimal(new int[] {
            400,
            0,
            0,
            0});
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(16, 59);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "Map Heigh";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(16, 33);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Map Width";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this._numTileWidth);
            this.groupBox2.Controls.Add(this._numTileHeigh);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Location = new System.Drawing.Point(15, 155);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(240, 101);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Tile Size";
            // 
            // _numTileWidth
            // 
            this._numTileWidth.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this._numTileWidth.Location = new System.Drawing.Point(91, 31);
            this._numTileWidth.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this._numTileWidth.Name = "_numTileWidth";
            this._numTileWidth.Size = new System.Drawing.Size(143, 20);
            this._numTileWidth.TabIndex = 6;
            this._numTileWidth.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            // 
            // _numTileHeigh
            // 
            this._numTileHeigh.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this._numTileHeigh.Location = new System.Drawing.Point(91, 57);
            this._numTileHeigh.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this._numTileHeigh.Name = "_numTileHeigh";
            this._numTileHeigh.Size = new System.Drawing.Size(143, 20);
            this._numTileHeigh.TabIndex = 7;
            this._numTileHeigh.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(16, 59);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(55, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Tile Heigh";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(16, 33);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(55, 13);
            this.label5.TabIndex = 1;
            this.label5.Text = "Tile Width";
            // 
            // bttCancel
            // 
            this.bttCancel.Location = new System.Drawing.Point(23, 271);
            this.bttCancel.Name = "bttCancel";
            this.bttCancel.Size = new System.Drawing.Size(92, 34);
            this.bttCancel.TabIndex = 5;
            this.bttCancel.Text = "Cancel";
            this.bttCancel.UseVisualStyleBackColor = true;
            this.bttCancel.Click += new System.EventHandler(this.bttCancel_Click);
            // 
            // bttOK
            // 
            this.bttOK.Location = new System.Drawing.Point(154, 271);
            this.bttOK.Name = "bttOK";
            this.bttOK.Size = new System.Drawing.Size(92, 34);
            this.bttOK.TabIndex = 6;
            this.bttOK.Text = "OK";
            this.bttOK.UseVisualStyleBackColor = true;
            this.bttOK.Click += new System.EventHandler(this.bttOK_Click);
            // 
            // fmNewMap
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(267, 317);
            this.Controls.Add(this.bttOK);
            this.Controls.Add(this.bttCancel);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this._tbMapName);
            this.Controls.Add(this.label1);
            this.Name = "fmNewMap";
            this.Text = "fmNewMap";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this._numMapHeigh)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this._numMapWidth)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this._numTileWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this._numTileHeigh)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox _tbMapName;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.NumericUpDown _numMapHeigh;
        private System.Windows.Forms.NumericUpDown _numMapWidth;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.NumericUpDown _numTileWidth;
        private System.Windows.Forms.NumericUpDown _numTileHeigh;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button bttCancel;
        private System.Windows.Forms.Button bttOK;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
    }
}