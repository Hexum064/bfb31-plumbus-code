/*
 * song_player.h
 *
 * Created: 2023-04-28 23:01:49
 *  Author: Branden
 */ 


#ifndef SONG_PLAYER_H_
#define SONG_PLAYER_H_

#include <stdlib.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "sound_data.h"



struct Track
{
	uint8_t * track_data;
	uint16_t track_size;
	uint8_t * extension_data;	
	uint16_t extension_size;
};

struct Channel
{
	struct Track intro;
	struct Track main;	
};

struct SongInitParams
{	
	struct Channel ch0;
	struct Channel ch1;	
	uint16_t bmp_period;
};

void song_player_init(struct SongInitParams params, void (*update_display_cb)());
void song_start();

#endif /* SONG_PLAYER_H_ */