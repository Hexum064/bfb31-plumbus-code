using System.Windows.Forms.VisualStyles;
using System.IO.Ports;
using System.Diagnostics;
using System.Text;
using System;
using System.Linq;
using System.ComponentModel;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace meeseeks_bus_pirate_spi_flash_mem_programmer
{
    public partial class mainForm : Form
    {
        /*
         * Notes: 
         * The memory is programmed 1 page at a time, with up to 256 bytes at a time
         * The Block erase takes about 200ms
         * We can read as many byte in a row as we want
         * 
         * The max size of a file is 65530 because the first 2 bytes in a block will be the size 
         * of the file it holds, and a value of 0xFF, 0xFF for the first two bytes will indicate
         * that nothing has been written. There is another 4 bytes free at the end of the block
         * for something else.
         * 
         * 
         * 
         */

        private const int MAX_FILE_SIZE = 65530;

        private const byte ERASE_CMD = 0xD8;
        private const byte WEL_CMD = 0x06;
        private const byte READ_CMD = 0x0B;
        private const byte STATUS_CMD = 0x05;
        private const byte PROG_CMD = 0x02;

        private const byte BUSY_bm = 0x01;
        private const byte WEL_bm = 0x02;

        private const UInt16 PAGE_SIZE = 256;
        private const UInt16 CHUNK_SIZE = 32;

        private SerialPort? serialPort = null;
        private List<SlotData> slots = new List<SlotData>{
            new SlotData(0), 
            new SlotData(1), 
            new SlotData(2), 
            new SlotData(3), 
            new SlotData(4), 
            new SlotData(5), 
            new SlotData(6), 
            new SlotData(7), 
            new SlotData(8), 
            new SlotData(9), 
            new SlotData(10), 
            new SlotData(11), 
            new SlotData(12), 
            new SlotData(13), 
            new SlotData(14) };
        private int currentSlot = 0;

        public mainForm()
        {
            InitializeComponent();
        }

 
        

        private void initApp()
        {
            refreshCommPorts();
            listBoxMemSlots.SelectedIndex = 0;
            
        }
        
        private async void refreshCommPorts()
        {
            labelConnectionStatus.Text = "loading comm ports";
            string[] ports = await getCommPorts();
            comboBoxCommPorts.Items.AddRange(ports);
            labelConnectionStatus.Text = "select comm port";
        }

        private Task<string[]> getCommPorts()
        {
            return Task.Run(() =>
            {
                string[] ports = SerialPort.GetPortNames();
                return ports;
            });
        }

        private Task<SerialPort?> openPort(string port)
        {
            return Task.Run(() =>
            {
                SerialPort? serialPort = null;
                try
                {
                    serialPort = new SerialPort(port, 115200, Parity.None, 8, StopBits.One);
                    serialPort.Open();
                    serialPort.WriteBufferSize = 1024;
                    serialPort.ReadBufferSize = 1024;

                }
                catch (Exception exc)
                {
                    Debug.WriteLine(exc.Message);                    
                }

                return serialPort;
            });
        }

        private async void connectToPort()
        {
            labelConnectionStatus.Text = "connecting to port";

            serialPort = await openPort(comboBoxCommPorts.Text);
            bool isConnected = await confirmConnection();
            bool isInSPIMode = await setToSPIMode();
            if (serialPort?.IsOpen ?? false && isConnected && isInSPIMode)
            {
               
                labelConnectionStatus.Text = $"connected to {comboBoxCommPorts.Text} in SPI mode";
            } 
            else
            {
                labelConnectionStatus.Text = $"could not connect to {comboBoxCommPorts.Text}";
            }
        }

        private void closeSerialPort()
        {
            if (serialPort?.IsOpen ?? false)
            {
                try
                {
                    serialPort.Close();
                }
                catch (Exception exc)
                {
                    Debug.WriteLine(exc.Message);
                }
            }
        }

        private Task<bool> confirmConnection()
        {
            return Task.Run(() =>
            {
                try
                {
                    serialPort?.WriteLine("#");
                    string result = serialPort?.ReadExisting();
                    return result?.StartsWith("Bus Pirate") ?? false;
                }
                catch (Exception exc)
                {
                    Debug.WriteLine(exc.Message);
                    return false;
                }
            });
        }

        private string getDataSync(long timeOutMs = 300)
        {
            string read = "";
            StringBuilder sb = new StringBuilder();
            Stopwatch sw = new Stopwatch();
            try
            {
                sw.Start();

                while(true)
                {
                    read = serialPort.ReadExisting();
                    if (!string.IsNullOrEmpty(read))
                    {
                        sb.Append(read);
                    }
                    if (read.EndsWith(">") || (sw.ElapsedMilliseconds > timeOutMs && timeOutMs > 0))
                    {
                        sw.Stop();                        
                        break;
                    }
                }

                
            }
            catch (Exception exc)
            {
                Debug.WriteLine(exc.Message);
            }

            return sb.ToString();

        }

        private Task<bool> setToSPIMode()
        {

            return Task.Run(() =>
            {
                try
                {
                    if (!(serialPort?.IsOpen ?? false))
                    {
                        return false;
                    }

                    serialPort.DiscardInBuffer();
                    serialPort.WriteLine("#");
                    //Thread.Sleep(100);
                    Debug.WriteLine(getDataSync());
                    //Change mode
                    serialPort.WriteLine("m");
                    //Thread.Sleep(100);
                    Debug.WriteLine(getDataSync());
                    //Select SPI
                    serialPort.WriteLine("5");
                    //Thread.Sleep(100);
                    Debug.WriteLine(getDataSync());
                    //Set 1Mhz
                    serialPort.WriteLine("4");
                    //Thread.Sleep(100);
                    Debug.WriteLine(getDataSync());
                    //Set Clock type
                    serialPort.WriteLine("1");
                    //Thread.Sleep(100);
                    Debug.WriteLine(getDataSync());
                    //Set Clock Edge
                    serialPort.WriteLine("2");
                    //Thread.Sleep(100);
                    Debug.WriteLine(getDataSync());
                    //Set Phase
                    serialPort.WriteLine("1");
                    //Thread.Sleep(100);
                    Debug.WriteLine(getDataSync());
                    //Set CS active low
                    serialPort.WriteLine("2");
                    //Thread.Sleep(100);
                    Debug.WriteLine(getDataSync());
                    //Set output normal (H=3.3, L=Gnd)
                    serialPort.WriteLine("2");
                    //Thread.Sleep(100);
                    string result = getDataSync();
                    Debug.WriteLine(result);
                    return result.EndsWith("SPI>");
                }
                catch (Exception exc)
                {
                    Debug.WriteLine(exc.Message);
                    return false;
                }
            });

        }

        private void displayData(byte[] data)
        {
            richTextBoxFileHex.Clear();
            
            int index = 0;
            
            StringBuilder sbLine = new StringBuilder();
            sbLine.Append("Addr 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
            if (data != null)
            {
                for (int i = 0; i < 4096; i++)
                {
                    Range range = new Range(index, (data.Length <= index + 16 ? data.Length : index + 16));
                    sbLine.Append($"{index.ToString("X4")} {BitConverter.ToString(data.Take(range).ToArray()).Replace("-", " ")}\n");
                    index += 16;

                    if (index > data.Length)
                    {
                        break;
                    }
                }

                richTextBoxFileHex.Text = sbLine.ToString();
                richTextBoxFileHex.SelectionStart = 0;
                richTextBoxFileHex.SelectionLength = 53;
                richTextBoxFileHex.SelectionColor = Color.Blue;

                index = 0;

                while(true)
                {
                    index = richTextBoxFileHex.Text.IndexOf('\n', index);
                    if (index == -1)
                    {
                        break;
                    }
                    index += 1;
                    richTextBoxFileHex.SelectionStart = index;
                    richTextBoxFileHex.SelectionLength = 4;
                    richTextBoxFileHex.SelectionColor = Color.Blue;

                    if (index > richTextBoxFileHex.Text.Length)
                    {
                        break;
                    }

                }
            }

        }

        private void loadSlot(int index)
        {
            currentSlot = index;
            labelSlot.Text = listBoxMemSlots.Text;
            checkBoxEraseOnly.Checked = slots[currentSlot].EraseOnly;
            textBoxFilePath.Text = slots[currentSlot].FilePath;
            labelBytes.Text = $"Bytes: {slots[currentSlot].Length}";
            displayData(slots[currentSlot].Data);
        }

        private void loadFileData(string path)
        {
            if (string.IsNullOrEmpty(path))
            {
                return;
            }

            if (!File.Exists(path))
            {
                MessageBox.Show("Could not find the file.");
                return;
            }

            using (FileStream fileStream = File.OpenRead(path))
            {

                if (fileStream.Length > 65530)
                {
                    MessageBox.Show("File is larger than 64KB.");                    
                    return;
                }

                slots[currentSlot].FilePath = path;
                slots[currentSlot].Length = (UInt16)fileStream.Length;
                slots[currentSlot].Data = new byte[slots[currentSlot].Length];

                fileStream.Read(slots[currentSlot].Data, 0, slots[currentSlot].Length);
            }
            

        }

        private byte[] getReadDataBytes(string response)
        {
           
            if (string.IsNullOrEmpty(response))
            {
                return new byte[0];
            }

            int startIndex = response.IndexOf("READ: ");
            if (startIndex == -1)
            {
                return new byte[0];
            }
            startIndex += "READ: ".Length;
            int endIndex = response.IndexOf('\n', startIndex);
            if (startIndex == -1)
            {
                return new byte[0];
            }

            return response.Substring(startIndex, endIndex - startIndex)
                .Split(" ", StringSplitOptions.TrimEntries | StringSplitOptions.RemoveEmptyEntries)
                .Select((val) => Convert.ToByte(val, 16))
                .ToArray();                           
        }

        private void writeToMemory()
        {
            if (!(serialPort?.IsOpen ?? false))
            {
                return;
            }

            int i = 1;

            foreach(SlotData slot in slots)
            {
                //TODO update status and progress
                progressBarWrite.Value = (i * 100) / slots.Count;    
                labelWriteStatus.Text = $"Writing Slot {i++}";
                progressBarWrite.Update();
                Application.DoEvents();
                writeSlot(slot);

             };
            labelWriteStatus.Text = $"Done";
        }

        private byte[] getAddressBytes(int address)
        {
            byte[] bytes = new byte[3];

            bytes[0] = (byte)(address & 0xFF);
            bytes[1] = (byte)((address >> 8) & 0xFF);
            bytes[2] = (byte)((address >> 16) & 0xFF);

            return bytes;
        }

        private void waitWhileBusy()
        {
            string status;
            while (true)
            {

                getDataSync();
                serialPort.WriteLine($"[{STATUS_CMD} r]");

                status = getDataSync();

                if ((getReadDataBytes(status).FirstOrDefault((byte)0) & BUSY_bm) == 0)
                {
                    break;
                }
            }

        }

        private void eraseBlock(int address)
        {
            if (!(serialPort?.IsOpen ?? false))
            {
                return;
            }

            byte[] addrBytes = getAddressBytes(address);

            
            serialPort.WriteLine($"[{WEL_CMD}] % [{ERASE_CMD} {addrBytes[2]} {addrBytes[1]} {addrBytes[0]}]");
            waitWhileBusy();

        }

        private byte[] readSlotMemory(int address)
        {
            if (!(serialPort?.IsOpen ?? false))
            {
                return new byte[0];
            }

            byte[] addrBytes = getAddressBytes(address);

            //First read the data size
            serialPort.WriteLine($"[{READ_CMD} {addrBytes[2]} {addrBytes[1]} {addrBytes[0]} 0 r:2]");
            string result = getDataSync(0);
            Debug.WriteLine(result);
            byte[] sizeBytes = getReadDataBytes(result);

            if (sizeBytes.Length < 2)
            {
                return new byte[0];
            }

            UInt16 size = BitConverter.ToUInt16(sizeBytes, 0);

            if (size == 0xFFFF || size == 0)
            {
                return new byte[0];
            }

            

            //Then read the data
            serialPort.WriteLine($"[{READ_CMD} {addrBytes[2]} {addrBytes[1]} {addrBytes[0]} 0 r:{size + 2}]");
            result = getDataSync(0);
            Debug.WriteLine(result);
            return getReadDataBytes(result);

        }

        private bool writeSlot(SlotData slot)
        {

            UInt16 startIndex = 0;
            UInt16 lengthLeft = slot.Length;
            UInt16 length = 0;            
            byte[] addrBytes = getAddressBytes(slot.StartAddress);
            byte[] sizeBytes = BitConverter.GetBytes(lengthLeft);
            byte[] pageData;
 

            try
            {

                labelSlotWriteStatus.Text = "";
                if (!slot.EraseOnly && slot.Length == 0)
                {
                    return true;
                }

                eraseBlock(slot.StartAddress);

                if (slot.EraseOnly)
                {
                    return true;    
                }
                    
                pageData = slot.Data.Prepend(sizeBytes[1]).ToArray().Prepend(sizeBytes[0]).ToArray();
                lengthLeft += 2;
                
                while (startIndex < slot.Length)
                {
                    labelSlotWriteStatus.Text = $"{((startIndex * 100) / slot.Length)}%";
                    labelSlotWriteStatus.Invalidate();
                    labelSlotWriteStatus.Update();
                    Application.DoEvents();
                    


                    length = (lengthLeft < PAGE_SIZE ? lengthLeft : (UInt16)PAGE_SIZE);
                    writePage(slot.StartAddress + startIndex, length, startIndex, pageData);

                      
                    lengthLeft -= length;
                    startIndex += length;
                }

                labelSlotWriteStatus.Text = "Done";
                return true;
            }
            catch (Exception exc)
            {

                Debug.WriteLine(exc.Message);
                labelSlotWriteStatus.Text = "Error";
                return false;

            }

        }


        private void writePage(int address, UInt16 length, UInt16 startIndex, byte[] data)
        {
            string dataString;
            string serLine;
            string result;
            UInt16 index = 0;
            UInt16 chunkLen = 0;
            UInt16 maxLen = length;
            byte[] addressBytes = getAddressBytes(address);

            serLine = $"[{WEL_CMD}] % [{PROG_CMD} {addressBytes[2]} {addressBytes[1]} {addressBytes[0]}";
            serialPort.WriteLine(serLine);
            result = getDataSync();
            Debug.WriteLine(result);

            while (index < maxLen)
            {

                chunkLen = (length > CHUNK_SIZE ? CHUNK_SIZE : length);
                dataString = String.Join(" ", data
                    .Skip(startIndex + index)
                    .Take(chunkLen)
                    .ToArray());

                serialPort.WriteLine(dataString);
                result = getDataSync();
                //Debug.WriteLine(result);

                index += CHUNK_SIZE;
                length -= CHUNK_SIZE;
            }




            serialPort.WriteLine("] %:3");
            waitWhileBusy();



        }

        private void mainForm_Load(object sender, EventArgs e)
        {
            initApp();
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            if (comboBoxCommPorts.SelectedIndex == -1)
            {
                return;
            }

            closeSerialPort();

            connectToPort();
        }

        private void mainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            closeSerialPort();
        }

        private void listBoxMemSlots_SelectedIndexChanged(object sender, EventArgs e)
        {            
            loadSlot(listBoxMemSlots.SelectedIndex);
        }

        private void checkBoxEraseOnly_CheckedChanged(object sender, EventArgs e)
        {
            slots[currentSlot].EraseOnly = checkBoxEraseOnly.Checked;
        }

        private void textBoxFilePath_Leave(object sender, EventArgs e)
        {
            if (!string.Equals(textBoxFilePath.Text, slots[currentSlot].FilePath))
            {
                loadFileData(textBoxFilePath.Text);
                loadSlot(currentSlot);
            }
        }

        private void textBoxFilePath_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)13)
            {
                loadFileData(textBoxFilePath.Text);
                loadSlot(currentSlot);
            }
        }

        private void buttonReadSlot_Click(object sender, EventArgs e)
        {
            byte[] data = readSlotMemory(slots[currentSlot].StartAddress);
            displayData(data);
        }

        private void buttonWrite_Click(object sender, EventArgs e)
        {
            writeToMemory();
        }

        private void buttonOpenPath_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                textBoxFilePath.Text = openFileDialog.FileName;
                if (!string.Equals(textBoxFilePath.Text, slots[currentSlot].FilePath))
                {
                    loadFileData(textBoxFilePath.Text);
                    loadSlot(currentSlot);
                }
            }
        }

        private void buttonWriteSlot_Click(object sender, EventArgs e)
        {
            writeSlot(slots[currentSlot]);
        }
    }
}