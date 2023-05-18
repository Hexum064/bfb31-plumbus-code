/*
 * io_expander.h
 *
 * Created: 2023-04-27 19:09:04
 *  Author: Branden
 */ 


#ifndef IO_EXPANDER_H_
#define IO_EXPANDER_H_

#include <avr/io.h>

#define EXP_ADDR 0x20
#define EXP_WRITE 0x00
#define EXP_READ 0x01
#define EXP_REG_CTRL0 0x06
#define EXP_REG_CTRL1 0x07

void expander_init();
uint8_t expander_read_port(uint8_t portAddr);
uint16_t expander_read_ports();
uint8_t expander_get_val_changed();
uint16_t expander_get_last_value();

#endif /* IO_EXPANDER_H_ */