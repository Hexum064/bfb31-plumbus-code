/*
 * io_expander.c
 *
 * Created: 2023-04-27 19:08:53
 *  Author: Branden
 */ 
#include "io_expander.h"

void expander_init()
{
	//Set up port0 and port1 as input
	uint8_t addr = EXP_ADDR;
	uint8_t cmd[] = {
		EXP_REG_CTRL0,
		0xff,
		0xff
	};
	twi_write(addr, cmd, 3);
	
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