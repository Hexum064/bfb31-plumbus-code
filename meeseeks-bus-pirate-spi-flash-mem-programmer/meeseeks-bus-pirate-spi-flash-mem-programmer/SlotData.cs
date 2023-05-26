using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace meeseeks_bus_pirate_spi_flash_mem_programmer
{
    internal class SlotData
    {
        private const int SLOT_SIZE = 0x10000;
        
        public SlotData(int slotIndex)
        {
            StartAddress = slotIndex * SLOT_SIZE;
        }

        public int SlotNumber { get; set; } = 0;
        public string FilePath { get; set; } = "";
        public bool EraseOnly { get; set; } = false;
        public byte[] Data { get; set; }
        public UInt16 Length { get; set; } = 0;
        public int StartAddress { get; private set; } = 0;

    }
}
