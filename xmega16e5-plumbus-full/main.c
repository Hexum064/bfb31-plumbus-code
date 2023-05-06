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

#include <stdlib.h>
#include "i2c.h"
#include "ws2812drv.h"
#include "start_mode.h"




void start_up()
{
	switch(get_start_mode())
	{
		case STANDBY_sm:
			break;
		case FREEPLAY_sm:
			break;
		case GAME_EASY_sm:
			break;
		case GAME_HARD_sm:
			break;
		case NYAN_sm:
			break;
		case PORTAL_sm:
			if (get_allow_portal())
			{
				
			}
			break;
		case EASER_EGG_sm:
			if (get_allow_easter_egg())
			{
				
			}
			break;			
	}
	
	reset_start_mode();
}

int main(void)
{
	start_mode_init();
	start_up();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

