/*
 * start_mode.c
 *
 * Created: 2023-04-28 22:53:35
 *  Author: Branden
 */ 

#include "start_mode.h"

volatile uint8_t start_mode = 0;
volatile uint8_t allow_portal = 0;
volatile uint8_t allow_easter_egg = 0;

uint8_t get_allow_portal()
{
	return allow_portal;
}

void set_allow_portal(uint8_t allow)
{
	allow_portal = allow;
	eeprom_write_byte((uint8_t *)2, allow_portal ? ALLOW_VAL : 0);
}

uint8_t get_allow_easter_egg()
{
	return allow_easter_egg;
}

void set_allow_easter_egg(uint8_t allow)
{
	allow_easter_egg = allow;
	eeprom_write_byte((uint8_t *)3, allow_easter_egg ? ALLOW_VAL : 0);
}

uint8_t get_start_mode()
{
	return start_mode;
}

void reset_start_mode_in_eeprom()
{
	eeprom_write_byte((uint8_t *)1, 0);
}

void enable_wdt()
{
	CCP = CCP_IOREG_gc;
	WDT_CTRL = WDT_ENABLE_bm | WDT_CEN_bm;
}

void start_mode_init()
{
	
	start_mode = eeprom_read_byte((uint8_t*)1);
	
	if (start_mode > BASE_MAX_MODE + 2 && start_mode != EASTER_EGG_START_sm)
	{
		start_mode = 0;
		reset_start_mode_in_eeprom();
	}
	
	allow_portal = eeprom_read_byte((uint8_t*)2);
	
	//TODO:Remove test case
	allow_portal = ALLOW_VAL;
	
	allow_easter_egg = eeprom_read_byte((uint8_t*)3);
	
}

void set_start_mode(uint8_t start_mode)
{
	//If start mode is set to what "Allow Portal" would be, we need to see
	//if the mode can be set to "Allow Portal", or if it can be skipped and
	//go straight to "Easter Egg" mode, or we just roll back to "Standby"
	if (start_mode == BASE_MAX_MODE + 1)
	{
		//This falls through if allow_porta is true, and allows the mode to
		//be switched to Portal mode
		
		if ((allow_portal != ALLOW_VAL) && (allow_easter_egg != ALLOW_VAL))
		{
			start_mode = 0;
		}
		else if ((allow_portal != ALLOW_VAL) && (allow_easter_egg == ALLOW_VAL))
		{
			start_mode++;
		}
	}
	else if (start_mode == BASE_MAX_MODE + 2)
	{
		//Just let this fall through if allow_easter_egg is true
		//so we can switch to easter egg mode
		if ((allow_easter_egg != ALLOW_VAL))
		{
			start_mode = 0;
		}
		
	}
	else if (start_mode > BASE_MAX_MODE + 2 && start_mode != EASTER_EGG_START_sm)
	{
		//Our default restart state
		start_mode = 0;
	}
	
	eeprom_write_byte((uint8_t *)1, start_mode);
	eeprom_busy_wait();
	enable_wdt();
	
	while(1);
	
}

void next_start_mode()
{
	start_mode++;
	set_start_mode(start_mode);
	
}
