/*
 * io_expander.c
 *
 * Created: 2023-04-27 19:08:53
 *  Author: Branden
 */ 
#include "io_expander.h"
#include "i2c.h"

volatile uint16_t last_val = 0;

void expander_init()
{
	twi_init();
	
	//Set up port0 and port1 as input
	uint8_t addr = EXP_ADDR;
	uint8_t cmd[] = {
		EXP_REG_CTRL0,
		0xff,
		0xff
	};
	twi_write(addr, cmd, 3);
	last_val = expander_read_ports();
}

uint8_t expander_read_port(uint8_t portAddr)
{
	uint8_t port_val;
	uint8_t addr = EXP_ADDR;
	
	uint8_t cmd[] = {
		portAddr
	};
	
	twi_write(addr, cmd, sizeof cmd);
	
	twi_read(addr, &port_val, 1);
	
	return port_val;
	
}

uint16_t expander_read_ports()
{
	uint16_t port_data;
	
	port_data = expander_read_port(0x00) + (expander_read_port(0x01) << 8);
	return port_data;
	
}


uint8_t get_val_changed()
{
	uint16_t val = expander_read_ports();
	
	if (val == last_val)
	{
		return 0;
	}
	
	if (val > last_val)
	{
		last_val = val;
		return 2;		
	}
	
	last_val = val;
	return 1;	
}