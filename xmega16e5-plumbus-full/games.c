/*
 * games.c
 *
 * Created: 2023-05-16 18:29:06
 *  Author: Branden
 */ 

#include "games.h"
#include <stdlib.h>
#include "rand_seed.h"
#include "note_player.h"
#include "io_expander.h"
#include "light_player.h"
#include "start_mode.h"

void (*step)();

//NOTE: if the game is won in hard mode, the badge switched to portal mode automatically.

typedef enum {
	
	game_start,
	play_sequence,
	get_input,	
	game_won,
	game_lost,
	
} GameState;

uint8_t * sequence;
uint8_t play_index = 0;
uint8_t progress_index = 0;
uint16_t timer_counter = 0;
uint8_t sequence_len = 0; 
uint8_t sequence_initialized = 0;

volatile GameState game_state = game_start;

uint8_t easy_game_start_notes[] = {12,8,5,1};
uint8_t hard_game_start_notes[] = {15,14,13,12};
uint8_t easy_won_notes[] = {15,12,8,5,8,5,12,8,7,3,6,3};
uint8_t game_lost_notes[] = {11,14,15,15};

void (*handle_game_won_state)();
void (*sequence_init)();
uint8_t * start_notes;
uint8_t * start_size;


void game_won_easy()
{
	play_lights_won_easy_game();
		
	if (!(note_player_playing()))
	{
		if (play_index < sizeof(easy_won_notes))
		{
			timer_counter = 0;
			note_play(easy_won_notes[play_index++]);
		}
		else
		{
			if (timer_counter++ > STEP_PAUSE)
			{
				play_index = 0;
				timer_counter = 0;
				sequence_initialized = 0;
				game_state = game_start;
				play_lights_game(expander_read_ports(), 0);
			}
		}
	}
}

void game_won_hard()
{
	if (timer_counter++ < STEP_PAUSE)
	{
		return;
	}
	
	set_allow_portal(ALLOW_VAL);
	set_start_mode(PORTAL_sm);
}

void easy_sequence_init()
{
	sequence_len = EASY_LENGTH;
	sequence = (uint8_t *)malloc(EASY_LENGTH);
	srand(get_seed());
	for (uint8_t i = 0; i < EASY_LENGTH; i++)
	{
		sequence[i] = 0x01 << (rand() % 4);
	}
	
}

void hard_sequence_init()
{
	sequence_len = HARD_LENGTH;
	sequence = (uint8_t *)malloc(HARD_LENGTH);
	srand(get_seed());
	for (uint8_t i = 0; i < HARD_LENGTH; i++)
	{
		sequence[i] = (rand() % 15) + 1;
	}
}

void games_init(GameModes mode)
{

	if (mode == easy)
	{
		sequence_init = easy_sequence_init;
		handle_game_won_state = game_won_easy;
		start_notes = easy_game_start_notes;
		start_size = sizeof(easy_game_start_notes);
	}
	else
	{
		sequence_init = hard_sequence_init;
		handle_game_won_state = game_won_hard;
		start_notes = hard_game_start_notes;
		start_size = sizeof(hard_game_start_notes);
	}
	
	
}

void games_step(uint8_t buttons)
{
	switch (game_state)
	{
		case game_start:
		
			if (!(sequence_initialized))
			{
				sequence_init();
				sequence_initialized = 1;
			}		
		
			play_lights_game(expander_read_ports(), 0);
			if (play_index == start_size && !(note_player_playing()))
			{
				play_lights_game(expander_read_ports(), 0);
				game_state = play_sequence;
				timer_counter = 0;
				play_index = 0;
				progress_index = 1;
				break;
			}
			
			if (!(note_player_playing()))
			{
				note_play(start_notes[play_index++]);
			}
			

			break;
		case play_sequence:
		
			if (timer_counter < STEP_PAUSE)
			{
				timer_counter++;
				break;
			}
		
			if (timer_counter < NOTE_PAUSE)
			{
				play_lights_game(expander_read_ports(), 0);
				timer_counter++;
				break;
			}
		
			if (play_index == progress_index)
			{
			
				play_lights_game(expander_read_ports(), 0);
				game_state = get_input;
				timer_counter = 0;
				play_index = 0;

				break;
			}
		
			if (!(note_player_playing()))
			{
				play_lights_game(expander_read_ports(), sequence[play_index]);
				note_play(sequence[play_index++]);
				timer_counter = 0;
			}
		
		
		
			break;
		case get_input:
		
			play_lights_game(expander_read_ports(), buttons);
		
			if (timer_counter++ > INPUT_TIMEOUT && !(note_player_playing()))
			{
				play_lights_game(expander_read_ports(), 0);
				game_state = game_lost;
				timer_counter = 0;
				play_index = 0;

				break;
			}

		
			if (buttons && expander_get_val_changed() && !(note_player_playing()))
			{
				timer_counter = 0;
			
				if (buttons == sequence[play_index])
				{
					note_play(buttons);
					play_index++;
				

					if (play_index == progress_index)
					{
						progress_index++;
					
						if (progress_index > sequence_len)
						{
							game_state = game_won;
						}
						else
						{
							game_state = play_sequence;
						}
					
						timer_counter = 0;
						play_index = 0;
						break;
					}
				}
				else
				{
					game_state = game_lost;
					timer_counter = 0;
					play_index = 0;
					break;
				}
			}
		
			break;
		case game_won:
			handle_game_won_state();
			break;
		case game_lost:
		
			play_lights_game_over();
			if (!(note_player_playing()))
			{
				if (play_index < sizeof(game_lost_notes))
				{
					timer_counter = 0;
					note_play(game_lost_notes[play_index++]);
				}
				else
				{
					if (timer_counter++ > STEP_PAUSE)
					{
						play_index = 0;
						timer_counter = 0;
						sequence_initialized = 0;
						game_state = game_start;
						play_lights_game(expander_read_ports(), 0);
					}
				}
			}

			break;
	}
	
}