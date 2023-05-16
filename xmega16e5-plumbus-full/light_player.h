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

void play_lights_standby(ws2812drv_led_t * leds);
void play_lights_free_play(ws2812drv_led_t * leds, uint16_t dingle_pos, uint8_t buttons);
void play_lights_nyan(ws2812drv_led_t * leds);
void play_lights_portal(ws2812drv_led_t * leds);

#endif /* LIGHT_PLAYER_H_ */