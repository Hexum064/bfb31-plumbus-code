/*
 * games.c
 *
 * Created: 2023-05-16 18:29:06
 *  Author: Branden
 */ 

#include "games.h"
#include <stdlib.h>
#include <avr/io.h>
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
	sequence_played,
	game_won,
	game_lost,
	
} GameState;

uint8_t * sequence;
uint8_t play_index = 0;
uint8_t progress_index = 0;
uint16_t timer_counter = 0;

volatile GameState game_state = game_start;

uint8_t game_start_notes[] = {13,10,7,3,12,8,5,1};
uint8_t easy_won_notes[] = {15,12,8,5,8,5,12,8,7,3,6,3};
uint8_t game_lost_notes[] = {11,14,15,15};



void step_easy()
{
	switch (game_state)
	{
		case game_start:
 			
			play_lights_game(expander_read_ports(), 0);
			if (play_index == sizeof(game_start_notes) && !(note_player_playing()))
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
				note_play(game_start_notes[play_index++]);				
			}
			

			break;
		case play_sequence:
 			
			if (timer_counter < 5)
			{
				timer_counter++;
				break;
			}
			
			if (timer_counter < 8)
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
			break;
		case sequence_played:
			break;
		case game_won:
			break;
		case game_lost:
			break;
	}
	
	
}

void step_hard()
{
	
}

uint16_t get_seed()
{
	ADCA.CTRLB|=ADC_CURRLIMIT1_bm|ADC_CONMODE_bm; //medium current consumption, maximum sampling speed 150ksps, resolution 12-bit right adjusted, signed mode
 
	ADCA.REFCTRL|=ADC_REFSEL0_bm; //INTVCC2 i.e. Vcc/1.6 is selected as reference voltage
 
	ADCA.EVCTRL=0x00;               //no event channel input is selected
 
	ADCA.PRESCALER|=ADC_PRESCALER2_bm; //prescaler 64 is selected and peripheral clock is 8MHz
 
	ADCA.INTFLAGS=ADC_CH0IF_bm; //clear interrupt flag by writing one to it
 
	ADCA.CH0.CTRL|=ADC_CH_INPUTMODE0_bm; //signed mode, single ended positive input selected
 
	ADCA.CH0.MUXCTRL|=ADC_CH_MUXPOS1_bm; //select PIN1 as input for ADC
 
	ADCA.CTRLA=ADC_ENABLE_bm | ADC_START_bm; //enable ADC and start
	
	while(!(ADCA.INTFLAGS & ADC_CH0IF_bm));
	
	ADCA.INTFLAGS=ADC_CH0IF_bm;  //clear flag immediately after conversion
	
	uint16_t result = ADCA.CH0.RES;
	
	ADCA.CTRLA = 0;
	return result;
}

void easy_sequence_init()
{
	sequence = (uint8_t *)malloc(EASY_LENGTH);
	srand(get_seed());
	for (uint8_t i = 0; i < EASY_LENGTH; i++)
	{
		sequence[i] = 0x01 << (rand() % 4);
	}
	
}

void hard_sequence_init()
{
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
		easy_sequence_init();
	}
	else
	{
		hard_sequence_init();
	}
	
	
}

void games_step()
{
				
	step_easy();
}