namespace meeseeks_bus_pirate_spi_flash_mem_programmer
{
    partial class mainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.listBoxMemSlots = new System.Windows.Forms.ListBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.labelConnectionStatus = new System.Windows.Forms.Label();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.comboBoxCommPorts = new System.Windows.Forms.ComboBox();
            this.labelSlot = new System.Windows.Forms.Label();
            this.labelLoad = new System.Windows.Forms.Label();
            this.textBoxFilePath = new System.Windows.Forms.TextBox();
            this.buttonOpenPath = new System.Windows.Forms.Button();
            this.checkBoxEraseOnly = new System.Windows.Forms.CheckBox();
            this.richTextBoxFileHex = new System.Windows.Forms.RichTextBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.labelWriteStatus = new System.Windows.Forms.Label();
            this.progressBarWrite = new System.Windows.Forms.ProgressBar();
            this.buttonWrite = new System.Windows.Forms.Button();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.labelBytes = new System.Windows.Forms.Label();
            this.buttonReadSlot = new System.Windows.Forms.Button();
            this.buttonWriteSlot = new System.Windows.Forms.Button();
            this.labelSlotWriteStatus = new System.Windows.Forms.Label();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Controls.Add(this.groupBox1);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Left;
            this.groupBox2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.groupBox2.Location = new System.Drawing.Point(0, 0);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(0);
            this.groupBox2.Size = new System.Drawing.Size(252, 422);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.listBoxMemSlots);
            this.groupBox3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox3.Location = new System.Drawing.Point(0, 140);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox3.Size = new System.Drawing.Size(252, 282);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "groupBox3";
            // 
            // listBoxMemSlots
            // 
            this.listBoxMemSlots.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listBoxMemSlots.FormattingEnabled = true;
            this.listBoxMemSlots.ItemHeight = 15;
            this.listBoxMemSlots.Items.AddRange(new object[] {
            "Mem Slot 1",
            "Mem Slot 2",
            "Mem Slot 3",
            "Mem Slot 4",
            "Mem Slot 5",
            "Mem Slot 6",
            "Mem Slot 7",
            "Mem Slot 8",
            "Mem Slot 9",
            "Mem Slot 10",
            "Mem Slot 11",
            "Mem Slot 12",
            "Mem Slot 13",
            "Mem Slot 14",
            "Mem Slot 15"});
            this.listBoxMemSlots.Location = new System.Drawing.Point(3, 18);
            this.listBoxMemSlots.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.listBoxMemSlots.Name = "listBoxMemSlots";
            this.listBoxMemSlots.Size = new System.Drawing.Size(246, 262);
            this.listBoxMemSlots.TabIndex = 4;
            this.listBoxMemSlots.SelectedIndexChanged += new System.EventHandler(this.listBoxMemSlots_SelectedIndexChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.labelConnectionStatus);
            this.groupBox1.Controls.Add(this.buttonConnect);
            this.groupBox1.Controls.Add(this.buttonRefresh);
            this.groupBox1.Controls.Add(this.comboBoxCommPorts);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox1.Location = new System.Drawing.Point(0, 16);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox1.Size = new System.Drawing.Size(252, 124);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "connect";
            // 
            // labelConnectionStatus
            // 
            this.labelConnectionStatus.AutoSize = true;
            this.labelConnectionStatus.Location = new System.Drawing.Point(10, 93);
            this.labelConnectionStatus.Name = "labelConnectionStatus";
            this.labelConnectionStatus.Size = new System.Drawing.Size(84, 15);
            this.labelConnectionStatus.TabIndex = 7;
            this.labelConnectionStatus.Text = "not connected";
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(10, 62);
            this.buttonConnect.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(132, 22);
            this.buttonConnect.TabIndex = 6;
            this.buttonConnect.Text = "connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Location = new System.Drawing.Point(148, 36);
            this.buttonRefresh.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(82, 22);
            this.buttonRefresh.TabIndex = 5;
            this.buttonRefresh.Text = "refresh";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            // 
            // comboBoxCommPorts
            // 
            this.comboBoxCommPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxCommPorts.FormattingEnabled = true;
            this.comboBoxCommPorts.Location = new System.Drawing.Point(10, 36);
            this.comboBoxCommPorts.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.comboBoxCommPorts.Name = "comboBoxCommPorts";
            this.comboBoxCommPorts.Size = new System.Drawing.Size(133, 23);
            this.comboBoxCommPorts.TabIndex = 4;
            // 
            // labelSlot
            // 
            this.labelSlot.AutoSize = true;
            this.labelSlot.Location = new System.Drawing.Point(282, 7);
            this.labelSlot.Name = "labelSlot";
            this.labelSlot.Size = new System.Drawing.Size(67, 15);
            this.labelSlot.TabIndex = 3;
            this.labelSlot.Text = "Mem Slot 1";
            // 
            // labelLoad
            // 
            this.labelLoad.AutoSize = true;
            this.labelLoad.Location = new System.Drawing.Point(282, 31);
            this.labelLoad.Name = "labelLoad";
            this.labelLoad.Size = new System.Drawing.Size(145, 15);
            this.labelLoad.TabIndex = 4;
            this.labelLoad.Text = "load file (max size is 64KB)";
            // 
            // textBoxFilePath
            // 
            this.textBoxFilePath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxFilePath.Location = new System.Drawing.Point(282, 52);
            this.textBoxFilePath.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBoxFilePath.Name = "textBoxFilePath";
            this.textBoxFilePath.Size = new System.Drawing.Size(466, 23);
            this.textBoxFilePath.TabIndex = 5;
            this.textBoxFilePath.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxFilePath_KeyPress);
            this.textBoxFilePath.Leave += new System.EventHandler(this.textBoxFilePath_Leave);
            // 
            // buttonOpenPath
            // 
            this.buttonOpenPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonOpenPath.Location = new System.Drawing.Point(753, 52);
            this.buttonOpenPath.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonOpenPath.Name = "buttonOpenPath";
            this.buttonOpenPath.Size = new System.Drawing.Size(25, 22);
            this.buttonOpenPath.TabIndex = 6;
            this.buttonOpenPath.Text = "...";
            this.buttonOpenPath.UseVisualStyleBackColor = true;
            this.buttonOpenPath.Click += new System.EventHandler(this.buttonOpenPath_Click);
            // 
            // checkBoxEraseOnly
            // 
            this.checkBoxEraseOnly.AutoSize = true;
            this.checkBoxEraseOnly.Location = new System.Drawing.Point(451, 28);
            this.checkBoxEraseOnly.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxEraseOnly.Name = "checkBoxEraseOnly";
            this.checkBoxEraseOnly.Size = new System.Drawing.Size(226, 19);
            this.checkBoxEraseOnly.TabIndex = 7;
            this.checkBoxEraseOnly.Text = "only erase the block, do not load a file";
            this.checkBoxEraseOnly.UseVisualStyleBackColor = true;
            this.checkBoxEraseOnly.CheckedChanged += new System.EventHandler(this.checkBoxEraseOnly_CheckedChanged);
            // 
            // richTextBoxFileHex
            // 
            this.richTextBoxFileHex.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBoxFileHex.Font = new System.Drawing.Font("Courier New", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.richTextBoxFileHex.Location = new System.Drawing.Point(282, 85);
            this.richTextBoxFileHex.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.richTextBoxFileHex.Name = "richTextBoxFileHex";
            this.richTextBoxFileHex.Size = new System.Drawing.Size(497, 238);
            this.richTextBoxFileHex.TabIndex = 8;
            this.richTextBoxFileHex.Text = "";
            // 
            // groupBox4
            // 
            this.groupBox4.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox4.Controls.Add(this.labelWriteStatus);
            this.groupBox4.Controls.Add(this.progressBarWrite);
            this.groupBox4.Controls.Add(this.buttonWrite);
            this.groupBox4.Location = new System.Drawing.Point(282, 347);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox4.Size = new System.Drawing.Size(496, 67);
            this.groupBox4.TabIndex = 9;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "write memory";
            // 
            // labelWriteStatus
            // 
            this.labelWriteStatus.AutoSize = true;
            this.labelWriteStatus.Location = new System.Drawing.Point(5, 44);
            this.labelWriteStatus.Name = "labelWriteStatus";
            this.labelWriteStatus.Size = new System.Drawing.Size(0, 15);
            this.labelWriteStatus.TabIndex = 2;
            // 
            // progressBarWrite
            // 
            this.progressBarWrite.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.progressBarWrite.Location = new System.Drawing.Point(93, 20);
            this.progressBarWrite.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.progressBarWrite.Name = "progressBarWrite";
            this.progressBarWrite.Size = new System.Drawing.Size(398, 22);
            this.progressBarWrite.TabIndex = 1;
            // 
            // buttonWrite
            // 
            this.buttonWrite.Location = new System.Drawing.Point(5, 20);
            this.buttonWrite.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonWrite.Name = "buttonWrite";
            this.buttonWrite.Size = new System.Drawing.Size(82, 22);
            this.buttonWrite.TabIndex = 0;
            this.buttonWrite.Text = "write";
            this.buttonWrite.UseVisualStyleBackColor = true;
            this.buttonWrite.Click += new System.EventHandler(this.buttonWrite_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "data";
            this.openFileDialog.ReadOnlyChecked = true;
            // 
            // labelBytes
            // 
            this.labelBytes.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelBytes.AutoSize = true;
            this.labelBytes.Location = new System.Drawing.Point(282, 325);
            this.labelBytes.Name = "labelBytes";
            this.labelBytes.Size = new System.Drawing.Size(47, 15);
            this.labelBytes.TabIndex = 10;
            this.labelBytes.Text = "bytes: 0";
            // 
            // buttonReadSlot
            // 
            this.buttonReadSlot.Location = new System.Drawing.Point(690, 327);
            this.buttonReadSlot.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonReadSlot.Name = "buttonReadSlot";
            this.buttonReadSlot.Size = new System.Drawing.Size(82, 22);
            this.buttonReadSlot.TabIndex = 11;
            this.buttonReadSlot.Text = "read slot";
            this.buttonReadSlot.UseVisualStyleBackColor = true;
            this.buttonReadSlot.Click += new System.EventHandler(this.buttonReadSlot_Click);
            // 
            // buttonWriteSlot
            // 
            this.buttonWriteSlot.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonWriteSlot.Location = new System.Drawing.Point(595, 327);
            this.buttonWriteSlot.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonWriteSlot.Name = "buttonWriteSlot";
            this.buttonWriteSlot.Size = new System.Drawing.Size(82, 22);
            this.buttonWriteSlot.TabIndex = 12;
            this.buttonWriteSlot.Text = "write slot";
            this.buttonWriteSlot.UseVisualStyleBackColor = true;
            this.buttonWriteSlot.Click += new System.EventHandler(this.buttonWriteSlot_Click);
            // 
            // labelSlotWriteStatus
            // 
            this.labelSlotWriteStatus.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelSlotWriteStatus.AutoSize = true;
            this.labelSlotWriteStatus.Location = new System.Drawing.Point(432, 325);
            this.labelSlotWriteStatus.Name = "labelSlotWriteStatus";
            this.labelSlotWriteStatus.Size = new System.Drawing.Size(0, 15);
            this.labelSlotWriteStatus.TabIndex = 13;
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(801, 422);
            this.Controls.Add(this.labelSlotWriteStatus);
            this.Controls.Add(this.buttonWriteSlot);
            this.Controls.Add(this.buttonReadSlot);
            this.Controls.Add(this.labelBytes);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.richTextBoxFileHex);
            this.Controls.Add(this.checkBoxEraseOnly);
            this.Controls.Add(this.buttonOpenPath);
            this.Controls.Add(this.textBoxFilePath);
            this.Controls.Add(this.labelLoad);
            this.Controls.Add(this.labelSlot);
            this.Controls.Add(this.groupBox2);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "mainForm";
            this.Text = "MeeSeeks Flash Mem Programmer";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.mainForm_FormClosing);
            this.Load += new System.EventHandler(this.mainForm_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private GroupBox groupBox2;
        private GroupBox groupBox3;
        private GroupBox groupBox1;
        private Button buttonRefresh;
        private ComboBox comboBoxCommPorts;
        private Button buttonConnect;
        private Label labelConnectionStatus;
        private ListBox listBoxMemSlots;
        private Label labelSlot;
        private Label labelLoad;
        private TextBox textBoxFilePath;
        private Button buttonOpenPath;
        private CheckBox checkBoxEraseOnly;
        private RichTextBox richTextBoxFileHex;
        private GroupBox groupBox4;
        private Label labelWriteStatus;
        private ProgressBar progressBarWrite;
        private Button buttonWrite;
        private OpenFileDialog openFileDialog;
        private Label labelBytes;
        private Button buttonReadSlot;
        private Button buttonWriteSlot;
        private Label labelSlotWriteStatus;
    }
}