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
#include "games.h"

#define MEESEEKS_ADDR 0x12
#define MEESEEKS_PLAY_CMD 0x01

volatile uint16_t display_ctr = 0;

uint8_t meeseeks_data[] = {MEESEEKS_PLAY_CMD, 0};
uint8_t easter_egg_pattern[] = {15,11,9,15,11,9,15,11,9,4,6,9,8,9,13,15};
uint8_t easter_egg_index = 0;
uint8_t easter_egg_size = sizeof(easter_egg_pattern);

void update_display_song_play_cb()
{
	if (get_start_mode() == NYAN_sm)
	{
		play_lights_nyan();
	}
	else
	{
		play_lights_portal();	
	}
	
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
	SongInitParams params;
	
	switch(mode)
	{
		case STANDBY_sm:
			sys_timer_D5_init();
			ws2812drv_init();
			break;
		case FREEPLAY_sm:
			//TCC5 out
			PORTC.DIRSET = PIN4_bm;
			note_buttons_init();
			note_player_init();
			dingle_input_init();
			ws2812drv_init();
			
			break;
		case GAME_EASY_sm:
			//TCC5 out
			PORTC.DIRSET = PIN4_bm;
			note_buttons_init();
			note_player_init();
			dingle_input_init();
			games_init(easy);
			ws2812drv_init();
			
			break;
		case GAME_HARD_sm:
			//TCC5 out
			PORTC.DIRSET = PIN4_bm;		
			note_buttons_init();
			note_player_init();
			dingle_input_init();
			games_init(hard);
			ws2812drv_init();
			
			break;
		case NYAN_sm:
			
			song_out_init();
			ws2812drv_init();
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
			
			song_player_init(params, play_lights_nyan);
			song_start();
			
			
			break;
		case PORTAL_sm:		
			if (get_allow_portal())
			{
				song_out_init();
				ws2812drv_init();
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
			
				song_player_init(params, play_lights_portal);
				song_start();
						
			}
			break;
		case EASTER_EGG_sm:
			if (get_allow_easter_egg())
			{
				sys_timer_D5_init();
				ws2812drv_init();
				note_buttons_init();
				dingle_input_init();
			}
			break;
		case EASTER_EGG_START_sm:
			
			song_out_init();
			ws2812drv_init();
			params.bmp_period = easterEggBPMPeriod;
			params.ch0.intro.track_data = easterEggIntroTreble;
			params.ch0.intro.track_size = sizeof(easterEggIntroTreble);
			params.ch0.intro.extension_data = easterEggIntroExtTreble;
			params.ch0.intro.extension_size = sizeof(easterEggIntroExtTreble);
			params.ch0.main.track_data = easterEggMainTreble;
			params.ch0.main.track_size = sizeof(easterEggMainTreble);
			params.ch0.main.extension_data = easterEggMainExtTreble;
			params.ch0.main.extension_size = sizeof(easterEggMainExtTreble);
			params.ch1.intro.track_data = easterEggIntroBass;
			params.ch1.intro.track_size = sizeof(easterEggIntroBass);
			params.ch1.intro.extension_data = easterEggIntroExtBass;
			params.ch1.intro.extension_size = sizeof(easterEggIntroExtBass);
			params.ch1.main.track_data = easterEggMainBass;
			params.ch1.main.track_size = sizeof(easterEggMainBass);
			params.ch1.main.extension_data = easterEggMainExtBass;
			params.ch1.main.extension_size = sizeof(easterEggMainExtBass);
				
			song_player_init(params, play_lights_easter_egg_intro);
			//song_start();
			song_play_once(next_start_mode);
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
	uint8_t val_changed = expander_get_val_changed();
	uint8_t playing = note_player_playing();
	if (note_buttons && val_changed && !(playing))
	{
		note_play(note_buttons);		
		
		if (note_buttons == easter_egg_pattern[easter_egg_index])
		{
			easter_egg_index++;
			
			if (easter_egg_index == easter_egg_size)
			{
				
				set_allow_easter_egg(ALLOW_VAL);
				easter_egg_index = 0;
				set_start_mode(EASTER_EGG_START_sm);
			}			
		}
		else
		{
			easter_egg_index = 0;
		}
	}

	return note_buttons;
}

uint8_t check_play_easter_egg()
{
	uint8_t note_buttons = get_note_buttons();

	if (note_buttons && expander_get_val_changed())
	{
		meeseeks_data[1] = note_buttons;
		twi_write(MEESEEKS_ADDR, meeseeks_data, sizeof(meeseeks_data));
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
	



    /* Replace with your application code */
    while (1) 
    {
		//TEMP: move to interrupt handler
		check_start_mode_pin();
		if (display_ctr >= 10)
		{		
			PORTA.OUTTGL = PIN3_bm;
			switch (get_start_mode())
			{
				case STANDBY_sm:
					play_lights_standby();
					break;
				case FREEPLAY_sm:
					note_buttons = check_play_note();
					//Use the LED array, the last value from the dingle pos, and the note buttons
 					play_lights_free_play(expander_get_last_value(), note_buttons);

					break;
				case GAME_EASY_sm:					
				case GAME_HARD_sm:
					games_step(get_note_buttons());
					break;
				case EASTER_EGG_sm:
					note_buttons = check_play_easter_egg();
					//Use the LED array, the last value from the dingle pos, and the note buttons
					play_lights_easter_egg(expander_read_ports(), note_buttons);	
					break;
			}
			display_ctr = 0;
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