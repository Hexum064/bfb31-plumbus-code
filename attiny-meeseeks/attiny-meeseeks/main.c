/*
 * attiny-meeseeks.c
 *
 * Created: 2023-05-19 22:02:55
 * Author : Branden
 */ 

#define F_CPU 10000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#define I2C_ADDR 0x12
#define PLAY_SOUND_CMD 0x01

#define MAX_FILE_SIZE 65530
#define EEPROM_INIT 0xA1 //just a random number. was thinking of steak at the time

#define ERASE_CMD  0xD8
#define WEL_CMD  0x06
#define READ_CMD  0x0B
#define STATUS_CMD  0x05
#define PROG_CMD  0x02
#define BUSY_bm  0x01
#define WEL_bm  0x02
#define PAGE_SIZE  256

#define PLAY_TIMER_TOP 1250 //For no clock prescaler at 10mhz

#define DEBOUNCE_TIME 50 //50 ms
#define RECORD_HOLD_TIME 1000 //1000 ms
#define RECORD_RESET_TIME 3000 //3000 ms
#define BLINK_TIME 100 //100 ms
#define RESET_PER 5000 //5000 ms

volatile uint16_t address_offset_flags = 0;
volatile uint8_t i2c_data = 0;
volatile uint8_t current_slot = 0;
volatile uint8_t recording_slot = 255; //Need this to roll over to 0 the first time
volatile uint8_t play_sound_cmd_rcvd = 0;
volatile uint8_t sound_playing = 0;
volatile uint16_t sound_len = 0;
volatile uint16_t sound_index = 0;
volatile uint8_t recording = 0;
volatile uint16_t debounce_count = 0;
volatile uint16_t hold_time = 0;
volatile uint8_t rec_button_down = 0;
volatile uint8_t rec_button_unreleased = 0;
volatile uint16_t record_reset_count = 0;
volatile uint8_t counting_record_reset = 0;
volatile uint16_t blink_count = 0;
volatile uint8_t blink_on = 0;
volatile uint16_t buff_len = 0;
volatile uint16_t buff_len_to_write = 0;
volatile uint16_t block_addr_to_write = 0;
volatile uint8_t first_page = 0;

uint8_t buffer0[256];
uint8_t buffer1[256];

uint8_t * current_buffer;
uint8_t * buffer_to_write;

void clk_init()
{
	CCP = 0xD8;
	CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSC20M_gc;
	
	while (!(CLKCTRL.MCLKSTATUS && CLKCTRL_OSC20MS_bm));
	
	CCP = 0xD8;
	CLKCTRL.MCLKCTRLB = CLKCTRL_PEN_bm | CLKCTRL_PDIV_2X_gc;
}

void i2c_init()
{
	TWI0.SADDR = I2C_ADDR << 1;
	TWI0.CTRLA = TWI_SDASETUP_4CYC_gc | TWI_SDAHOLD_OFF_gc;
	TWI0.SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_SMEN_bm | TWI_ENABLE_bm;
// 	TWI0.SCTRLB = TWI_SCMD_RESPONSE_gc;
	
}

void spi_init()
{
	PORTA.DIRSET = PIN1_bm | PIN3_bm | PIN4_bm; //MOSI, CLK, and CS pin
	PORTA.DIRCLR = PIN2_bm; //MISO
	PORTA.OUTSET = PIN4_bm; //Disable CS
	SPI0.CTRLA = SPI_MASTER_bm | SPI_CLK2X_bm | SPI_PRESC_DIV4_gc | SPI_ENABLE_bm;
	SPI0.CTRLB = 0;
}

void spi_disable()
{
	PORTA.DIRCLR = PIN1_bm | PIN3_bm | PIN4_bm; //Set these back to hi-z
	SPI0.CTRLA = 0;
}

void play_timer_init()
{
	
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	
}

void play_timer_start()
{
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm;
	TCA0.SINGLE.PER = PLAY_TIMER_TOP;
}

void play_timer_stop()
{
	TCA0.SINGLE.CTRLA = 0;
	TCA0.SINGLE.PER = 0;
}

void vref_init()
{
	VREF.CTRLA = 0x03 | 0x20 ; //DAC0 REF Select: 4.5 and ADC0 Ref 2.5
	VREF.CTRLB = VREF_DAC0REFEN_bm | VREF_ADC0REFEN_bm;
}

void dac_init()
{
	PORTA.OUTSET = PIN6_bm;

	DAC0.CTRLA = DAC_OUTEN_bm | DAC_ENABLE_bm;	
}

void adc_init()
{
	PORTB.OUTCLR = PIN4_bm; //ADC0 AIN9
	ADC0.CTRLB = 0; //No sample accum yet
	ADC0.CTRLC = ADC_REFSEL_INTREF_gc;
	ADC0.MUXPOS = ADC_MUXPOS_AIN9_gc;	
	ADC0.CTRLA = ADC_RESSEL_8BIT_gc | ADC_ENABLE_bm; //not doing freerun yet

	
}

void sys_timer_init()
{
	TCB0.CTRLB = TCB_CNTMODE_INT_gc;
	TCB0.INTCTRL = TCB_CAPT_bm;
	TCB0.CTRLA = TCB_CLKSEL_CLKDIV2_gc | TCB_ENABLE_bm;
	TCB0.CCMP = 5000; //Clk should be 5000000 so this should give a 1kHz tick
		
}

void record_button_init()
{
	PORTB.DIRCLR = PIN3_bm;
	PORTB.PIN3CTRL = PORT_PULLUPEN_bm;
}

void leds_init()
{
	PORTC.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm;
}

void mem_init()
{
	
}

void leds_set(uint8_t val)
{
	if (val & 0x8)
	{
		PORTC.OUTSET = PIN0_bm;
	}
	else
	{
		PORTC.OUTCLR = PIN0_bm;
	}
	
	if (val & 0x4)
	{
		PORTC.OUTSET = PIN1_bm;
	}
	else
	{
		PORTC.OUTCLR = PIN1_bm;
	}
	
	if (val & 0x2)
	{
		PORTC.OUTSET = PIN2_bm;
	}
	else
	{
		PORTC.OUTCLR = PIN2_bm;
	}
	
	if (val & 0x1)
	{
		PORTC.OUTSET = PIN3_bm;
	}
	else
	{
		PORTC.OUTCLR = PIN3_bm;
	}
	

}

void spi_write(uint8_t data)
{
	
	SPI0.DATA = data;
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
}

uint8_t spi_read()
{
	spi_write(0);
	return SPI0.DATA;
}

void CS_En()
{
	PORTA.OUTCLR = PIN4_bm; //Drive CS low
}

void CS_Dis()
{
	PORTA.OUTSET = PIN4_bm; //Drive CS high
}


void mem_busy_wait()
{
	while(1)
	{
		CS_En();
		spi_write(STATUS_CMD);
		uint8_t status = spi_read();
		CS_Dis();
		if (!(status & BUSY_bm))
		{
			return;
		}
	}
}

uint16_t read_slot_size(uint8_t slot)
{
	uint16_t len = 0;
	
	CS_En();
	spi_write(READ_CMD);
	spi_write(slot); //Addr bits 23-16
	spi_write(0); //Addr bits 15-8
	spi_write(0); //Addr bits 7-0
	spi_write(0); //For fast read
	len = (uint16_t)(spi_read()) + (uint16_t)(spi_read() << 8);
	CS_Dis();
	return len;
}

uint8_t get_sound_byte(uint8_t addrHi, uint8_t addrMid, uint8_t addrLo)
{
	uint8_t soundByte = 0;
	CS_En();
	spi_write(READ_CMD);
	spi_write(addrHi); //Addr bits 23-16
	spi_write(addrMid); //Addr bits 15-8
	spi_write(addrLo); //Addr bits 7-0
	spi_write(0); //For fast read
	soundByte = spi_read();
	CS_Dis();
	return soundByte;
}

void play_sound(uint8_t slot)
{
//This stops another sound from being started if one is currently playing
// 	if (sound_playing)
// 	{		
// 		return;
// 	}


	
	uint8_t offset = 0;
	//increase slot to +16 if specified slot's address offset flag is set so the "user" section of memory can be read if it has been set

	
	spi_init();
	if (address_offset_flags & (1 << slot))
	{
		slot += 16;
	}
	current_slot = slot;
	
	sound_playing = 1;
	sound_len = read_slot_size(current_slot);
	if (sound_len == 0xffff)
	{
		sound_playing = 0;
		sound_len = 0;
		spi_disable();
		leds_set(0);
		return;
	}
	sound_index = 0;
	play_timer_start();
}

void enable_write()
{
	CS_Dis();
	CS_En();
	spi_write(WEL_CMD);
	CS_Dis();	
}

void erase_slot(uint8_t slot)
{
	enable_write();
	CS_En();
	spi_write(ERASE_CMD);
	spi_write(slot); //addr hi
	spi_write(0); //addr med
	spi_write(0); //addr lo
	CS_Dis();
	
	mem_busy_wait();	
}

void reset_record_slot_select()
{
	recording_slot = 255; //Need this to roll over to 0 the first time
	counting_record_reset = 0;
	leds_set(0);	
}

void select_recording_slot()
{
	leds_set(recording_slot + 1);
	record_reset_count = 0;
	counting_record_reset = 1;
}


void start_next_page(uint16_t blockAddr)
{
	CS_Dis(); //End current page
	
	enable_write();
	
	CS_En();
	spi_write(PROG_CMD);
	//We only record to the "user" area of memory, so add 16
	spi_write(recording_slot + 16); //addr hi
	spi_write(0xFF & (blockAddr >> 8)); //addr med
	spi_write(0xFF & blockAddr); //addr lo 
	//leave CS enabled for now
}

void write_buffer(uint16_t len)
{
	
	
	start_next_page(block_addr_to_write);
	for (uint16_t i = 0; i < len; i++)
	{
		spi_write(buffer_to_write[i]);
	}
	CS_Dis();
	
	if (block_addr_to_write == 2)
	{
		block_addr_to_write = 0;
	}
	block_addr_to_write += PAGE_SIZE;
	
}

void write_recording_len(uint16_t len)
{
	CS_Dis();
	
	enable_write();
	
	CS_En();
	spi_write(PROG_CMD);
	//bump recording_slot to +16 this is because we can assume that if we are recording, we will do so in the "user" section of memory
	spi_write(recording_slot + 16); //addr hi
	spi_write(0); //addr med
	spi_write(0); //addr lo
	spi_write(0xFF & len);
	spi_write(0xFF & (len >> 8));
	CS_Dis();
}

void start_recording()
{	
	//bump recording_slot to +16 and set address offset flag for the slot			
	address_offset_flags |= (1 << recording_slot);
	update_offset_flags();
	leds_set(0);
	spi_init();
	erase_slot(recording_slot + 16);	
	first_page = 1;
	block_addr_to_write = 2;
	current_buffer = buffer0;
	buffer_to_write = buffer1;
	sound_len = 0;
	recording = 1;
	counting_record_reset = 0;
	blink_count = 0;

}


void stop_recording()
{
	mem_busy_wait();
	if (buff_len > 0)
	{
		buffer_to_write = current_buffer;
		write_buffer(buff_len);
	}
	mem_busy_wait();
	write_recording_len(sound_len);
	play_timer_stop();
	spi_disable();
	recording = 0;
	leds_set(0);
	recording_slot = 255;
	debounce_count = 0;
	rec_button_down = 0;	
	rec_button_down = 0;
	counting_record_reset = 0;
	rec_button_unreleased = 0;
}

void eeprom_init()
{
	if (eeprom_read_byte((uint8_t *)1) != EEPROM_INIT)
	{		
		eeprom_write_word((uint16_t *)3, 0x0000);
		eeprom_write_byte((uint8_t *)1, EEPROM_INIT);
	}
}

void update_offset_flags()
{
	eeprom_write_word((uint16_t *)3, address_offset_flags);
}

void get_offset_flags()
{
	address_offset_flags = eeprom_read_word((uint16_t *)3);
}

void play_reset_flash()
{
	for (uint8_t i = 0; i < 6; i++)
	{
		PORTC.OUTTGL = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm;
		_delay_ms(100);
	}
}



int main(void)
{
	cli();
	clk_init();
	play_timer_init();
	vref_init();
	dac_init();
	adc_init();
	sys_timer_init();
	
	sei();
	
	mem_init();
	eeprom_init();
	i2c_init();
	leds_init();
	record_button_init();

	//Test for reset here
	rec_button_down = 1;
	debounce_count = 0;
	while(debounce_count < RESET_PER)
	{
		if (PORTB.IN & PIN3_bm)
		{
			debounce_count = 0;
			break;
		}
	}
	
	//Reset if conditions met
	if (debounce_count >= RESET_PER)
	{
		address_offset_flags = 0;
		update_offset_flags();
		play_reset_flash();
	}
	
	rec_button_down = 0;
	debounce_count = 0;
	
	//Debug out
	PORTA.DIRSET = PIN7_bm;

    while (1) 
    {
		if (buff_len_to_write)
		{
			write_buffer(buff_len_to_write);
			buff_len_to_write = 0;
		}
		
		if (blink_count > BLINK_TIME)
		{
			blink_count = 0;
			if (blink_on)
			{
				blink_on = 0;
				leds_set(0);
			}
			else
			{
				blink_on = 1;
				leds_set(recording_slot + 1);
			}
		}		
		
		if (!(PORTB.IN & PIN3_bm) && !(rec_button_down)) //button down
		{
			//Debug
			PORTA.OUTSET = PIN7_bm;
			//starts a debounce
			rec_button_down = 1;
			debounce_count = 0;		
			rec_button_unreleased = 0;


		}
		else if (PORTB.IN & PIN3_bm)
		{
			
			
			if (debounce_count > DEBOUNCE_TIME)
			{
				
				//ends a debounce
				
				if (recording)// && !(rec_button_unreleased))
				{
					stop_recording();
					
				}
				else if (!(recording))
				{
					//move rec slot	
					recording_slot = ((++recording_slot) % 15);
					select_recording_slot();
					
				}				
			}
			
			//debug
			PORTA.OUTCLR = PIN7_bm;
			rec_button_down = 0;	
			debounce_count = 0;
			
		}
		
		if (rec_button_down && debounce_count > RECORD_HOLD_TIME && !(recording) && recording_slot != 0xFF)
		{
// 			rec_button_unreleased = 1;
			start_recording();
			play_timer_start();
		}		
		
		if (counting_record_reset && record_reset_count > RECORD_RESET_TIME)
		{
			reset_record_slot_select();
		}
    }
}

ISR(TWI0_TWIS_vect)
{
	
	if (TWI0.SSTATUS & TWI_DIF_bm)
	{
		
		i2c_data = TWI0.SDATA;
		
		if (recording)
		{
			return;
		}
		
		if (!(play_sound_cmd_rcvd) && i2c_data == PLAY_SOUND_CMD)
		{
			play_sound_cmd_rcvd = 1;
		}else if (play_sound_cmd_rcvd)

		{	
			play_sound_cmd_rcvd = 0;
			reset_record_slot_select();
			leds_set(i2c_data);					
			play_sound(i2c_data - 1);
		}
		
	}
	
	if (TWI0.SSTATUS & TWI_APIF_bm)
	{
		TWI0.SCTRLB = TWI_ACKACT_ACK_gc | TWI_SCMD_RESPONSE_gc;		
	}
}

ISR(TCA0_OVF_vect)
{
	//clear the flag
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
	
	
	if (recording)
	{
		ADC0.COMMAND = ADC_STCONV_bm;
		while(!(ADC0.INTFLAGS & ADC_RESRDY_bm));
		uint8_t data = ADC0.RES;
		current_buffer[buff_len] = data;
		sound_len++;
		buff_len++;
		
		if (sound_len >= MAX_FILE_SIZE)
		{			
			stop_recording();
		}
		
		if (buff_len == PAGE_SIZE || (first_page && buff_len == (PAGE_SIZE - 2)))
		{
			first_page = 0;
			uint8_t * temp = current_buffer;
			current_buffer = buffer_to_write;
			buffer_to_write = temp;				
			buff_len_to_write = buff_len;
			buff_len = 0;			
		}
	}
	else
	{

		uint16_t addr = sound_index + 2;
		uint8_t addrHi = current_slot;
		if (address_offset_flags & (1 << current_slot))
		{
			addrHi += 16;
		}
		uint8_t addrMid = ((addr >> 8) & 0xFF);
		uint8_t addrLo = (addr & 0xFF); //Need to start at +2
		uint8_t sound_byte = get_sound_byte(addrHi, addrMid, addrLo);
		DAC0.DATA = sound_byte >> 0;
		sound_index++;
	
		if (sound_index >= sound_len)
		{
			spi_disable();
			play_timer_stop();
			leds_set(0);
			sound_playing = 0;
		}
	}
}

ISR(TCB0_INT_vect)
{
	TCB0.INTFLAGS |= TCB_CAPT_bm;
	
	if (rec_button_down)
	{
		debounce_count++;		
	}
	
	if (recording)
	{
		blink_count++;
	}
	
	if (counting_record_reset)
	{
		record_reset_count++;
	}
}