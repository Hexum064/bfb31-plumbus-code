/*
 * note_player.h
 *
 * Created: 2023-04-30 13:52:26
 *  Author: Branden
 */ 


#ifndef NOTE_PLAYER_H_
#define NOTE_PLAYER_H_

#include "sound_data.h"

#define STARTING_NOTE_INDEX 7

void note_player_init();
void note_play(uint8_t note_index);

#endif /* NOTE_PLAYER_H_ */