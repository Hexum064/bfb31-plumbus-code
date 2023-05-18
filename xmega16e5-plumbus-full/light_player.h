/*
 * light_player.h
 *
 * Created: 2023-04-30 13:53:23
 *  Author: Branden
 */ 


#ifndef LIGHT_PLAYER_H_
#define LIGHT_PLAYER_H_

#include "ws2812drv.h"

#define GRUMBO_LED_COUNT 48
#define FLOOB_LED_COUNT 8
#define LED_COUNT (GRUMBO_LED_COUNT + FLOOB_LED_COUNT)
#define MAX_BRIGHTNESS 64

void play_lights_overlay_note_button_leds(uint8_t buttons);

void play_lights_standby();
void play_lights_free_play(uint16_t dingle_pos, uint8_t buttons);
void play_lights_nyan();
void play_lights_portal();

void play_lights_game(uint16_t dingle_pos, uint8_t buttons);
void play_lights_good_play();
void play_lights_game_over();
void play_lights_won_easy_game();
void play_lights_won_hard_game();

#endif /* LIGHT_PLAYER_H_ */