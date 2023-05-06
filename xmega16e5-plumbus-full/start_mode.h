/*
 * start_mode.h
 *
 * Created: 2023-04-28 22:53:19
 *  Author: Branden
 */ 


#ifndef START_MODE_H_
#define START_MODE_H_

#include <avr/io.h>
#include <avr/eeprom.h>

#define BASE_MAX_MODE 4

#define STANDBY_sm 0
#define FREEPLAY_sm 1
#define GAME_EASY_sm 2
#define GAME_HARD_sm 3
#define NYAN_sm	4
#define PORTAL_sm 5
#define EASER_EGG_sm 6



void start_mode_init();
void next_start_mode();
uint8_t get_start_mode();
void reset_start_mode();
uint8_t get_allow_portal();
void set_allow_portal(uint8_t allow);
uint8_t get_allow_easter_egg();
void set_allow_easter_egg(uint8_t allow);

#endif /* START_MODE_H_ */