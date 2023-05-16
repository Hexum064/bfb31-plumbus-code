/*
 * xmega16e5-plumbus-full.c
 *
 * Created: 2023-04-27 18:36:00
 * Author : Branden
 */ 

#define F_CPU 32000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "i2c.h"
#include "ws2812drv.h"
#include "start_mode.h"
#include "note_player.h"
#include "song_player.h"
#include "light_player.h"
#include "sound_data.h"
#include "io_expander.h"



volatile uint16_t display_ctr = 0;
volatile uint8_t note_played = 0;

/***********LED test code start*************/

volatile ws2812drv_led_t leds[LED_COUNT];

/***********LED test code end*************/

void update_display_song_play_cb()
{
	if (get_start_mode() == NYAN_sm)
	{
		play_lights_nyan(leds);
	}
	else
	{
		play_lights_portal(leds);	
	}
	ws2812drv_start_transfer(leds, LED_COUNT);
}

void clk_init()
{
	CCP = CCP_IOREG_gc;
	OSC_CTRL = OSC_RC32MEN_bm;
	
	while(!(OSC_STATUS & OSC_RC32MRDY_bm)){};
	
	CCP = CCP_IOREG_gc;
	CLK_CTRL = CLK_SCLKSEL_RC32M_gc;
	
	CCP = CCP_IOREG_gc;
	CLK_PSCTRL = 0;
	
}

void interrupt_init()
{
	PMIC_CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
}

void io_init()
{
	
	//Mode change pin
	PORTA.DIRCLR = PIN0_bm;
	PORTA.PIN0CTRL = PORT_OPC_PULLUP_gc;

	//Mode indication lights (all off by default)
	PORTD.DIRSET = PIN5_bm | PIN6_bm | PIN7_bm;
	PORTD.OUTCLR = PIN5_bm | PIN6_bm | PIN7_bm;
	
	//Hall sensor enable (off by default)
	PORTC.DIRSET = PIN7_bm;
	PORTC.OUTCLR = PIN7_bm;
	
	//DACA0 out
	PORTA.DIRSET = PIN2_bm;
	

}

void note_buttons_init()
{
	//Turn on hall sensors
	PORTC.OUTSET = PIN7_bm;
	
	//note button
	PORTA.DIRCLR = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
	PORTA.PIN4CTRL = PORT_OPC_PULLUP_gc;
	PORTA.PIN5CTRL = PORT_OPC_PULLUP_gc;
	PORTA.PIN6CTRL = PORT_OPC_PULLUP_gc;
	PORTA.PIN7CTRL = PORT_OPC_PULLUP_gc;
}

void dingle_input_init()
{
	expander_init();
}

void song_out_init()
{
	//TCC5 and TCD5 out 
	PORTC.DIRSET = PIN4_bm; 	
	PORTD.DIRSET = PIN4_bm;
	//Force dac0 output high 
	PORTA.OUTSET = PIN2_bm;
}

void start_up(uint8_t mode)
{
	switch(mode)
	{
		case STANDBY_sm:
			break;
		case FREEPLAY_sm:
			//TCC5 out
			PORTC.DIRSET = PIN4_bm;
			note_buttons_init();
			note_player_init();
			dingle_input_init();
			
			break;
		case GAME_EASY_sm:
			note_buttons_init();
			note_player_init();
			dingle_input_init();
			
			break;
		case GAME_HARD_sm:
			note_buttons_init();
			note_player_init();
			dingle_input_init();
			
			break;
		case NYAN_sm:
			
			song_out_init();
			SongInitParams params;
			params.bmp_period = nyanBPMPeriod;
			params.ch0.intro.track_data = nyanIntroTreble;
			params.ch0.intro.track_size = sizeof(nyanIntroTreble);
			params.ch0.intro.extension_data = nyanIntroExtTreble;
			params.ch0.intro.extension_size = sizeof(nyanIntroExtTreble);
			params.ch0.main.track_data = nyanMainTreble;
			params.ch0.main.track_size = sizeof(nyanMainTreble);
			params.ch0.main.extension_data = nyanMainExtTreble;
			params.ch0.main.extension_size = sizeof(nyanMainExtTreble);
			params.ch1.intro.track_data = nyanIntroBass;
			params.ch1.intro.track_size = sizeof(nyanIntroBass);
			params.ch1.intro.extension_data = nyanIntroExtBass;
			params.ch1.intro.extension_size = sizeof(nyanIntroExtBass);			
			params.ch1.main.track_data = nyanMainBass;
			params.ch1.main.track_size = sizeof(nyanMainBass);
			params.ch1.main.extension_data = nyanMainExtBass;
			params.ch1.main.extension_size = sizeof(nyanMainExtBass);
			
			song_player_init(params, update_display_song_play_cb);
			song_start();
			
			
			break;
		case PORTAL_sm:
		//TODO: remove test case
			if (get_allow_portal() || 1)
			{
				song_out_init();
				SongInitParams params;
				params.bmp_period = portalBPMPeriod;
				params.ch0.intro.track_data = portalIntroTreble;
				params.ch0.intro.track_size = sizeof(portalIntroTreble);
				params.ch0.intro.extension_data = portalIntroExtTreble;
				params.ch0.intro.extension_size = sizeof(portalIntroExtTreble);
				params.ch0.main.track_data = portalMainTreble;
				params.ch0.main.track_size = sizeof(portalMainTreble);
				params.ch0.main.extension_data = portalMainExtTreble;
				params.ch0.main.extension_size = sizeof(portalMainExtTreble);
				params.ch1.intro.track_data = portalIntroBass;
				params.ch1.intro.track_size = sizeof(portalIntroBass);
				params.ch1.intro.extension_data = portalIntroExtBass;
				params.ch1.intro.extension_size = sizeof(portalIntroExtBass);
				params.ch1.main.track_data = portalMainBass;
				params.ch1.main.track_size = sizeof(portalMainBass);
				params.ch1.main.extension_data = portalMainExtBass;
				params.ch1.main.extension_size = sizeof(portalMainExtBass);
			
				song_player_init(params, update_display_song_play_cb);
				song_start();
						
			}
			break;
		case EASER_EGG_sm:
			if (get_allow_easter_egg())
			{
				note_buttons_init();
			}
			break;			
	}	
}


void check_start_mode_pin()
{
	if (!(PORTA.IN & PIN0_bm))
	{
		//Simple blocking debounce
		_delay_ms(25);
		if(!(PORTA.IN & PIN0_bm))
		{
			//Hold until the pin is released.
			while (!(PORTA.IN & PIN0_bm));
			next_start_mode();
		}
	}	
}

void set_startup_mode_lights(uint8_t mode)
{
	uint8_t temp = PORTD.OUT & 0x1F;
	temp |= ((mode + 1) << 5);
	PORTD.OUT = temp;
}

uint8_t get_note_buttons()
{
	return ((~PORTA.IN) & 0xF0) >> 4;
}

uint8_t check_play_note()
{
	uint8_t note_buttons = get_note_buttons();
	uint8_t val_changed = get_val_changed();
	
	if (note_buttons && val_changed && !(note_played))
	{
		PORTA.OUTTGL = PIN3_bm;
		note_played = 1;
		note_play(note_buttons);		
	}
	
	if (!(val_changed))
	{
		note_played = 0;
	}
	
	return note_buttons;
}

int main(void)
{
	uint8_t note_buttons;
	
	//Debug pin
	PORTA.DIRSET = PIN3_bm;
	PORTA.OUTCLR = PIN3_bm;
	
		
	cli();
	clk_init();
	interrupt_init();
	sei();
		
	io_init();
	expander_init();

	
	//Hold until the pin is released.
	while (!(PORTA.IN & PIN0_bm));

	start_mode_init();
	set_startup_mode_lights(get_start_mode());
	start_up(get_start_mode());	
	reset_start_mode_in_eeprom();
	
	//Needs to come last. Still not sure why
	ws2812drv_init();

    /* Replace with your application code */
    while (1) 
    {
		//TEMP: move to interrupt handler
		check_start_mode_pin();
		
		if (get_start_mode() == FREEPLAY_sm)
		{
			note_buttons = check_play_note();
			
			//TEMP: Testing display stuff
			if (display_ctr >= 10)
			{
				//Use the LED array, the last value from the dingle pos, and the note buttons
				play_lights_free_play(leds, get_last_value(), note_buttons);
				ws2812drv_start_transfer(leds, LED_COUNT);
				display_ctr = 0;
				
			}			
		}

    }
}

ISR(TCC4_OVF_vect)
{
// 	PORTA.OUTTGL = PIN3_bm;
	song_interrupt_handler();
}

ISR(EDMA_CH0_vect)
{
	note_interrupt_handler();
}

ISR(TCD5_CCA_vect)
{
	display_ctr++;
}