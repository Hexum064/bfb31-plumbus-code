/*
 * games.h
 *
 * Created: 2023-05-16 18:29:18
 *  Author: Branden
 */ 


#ifndef GAMES_H_
#define GAMES_H_

#define EASY_LENGTH 8
#define HARD_LENGTH 12
#define INPUT_TIMEOUT 25 //Needs to be longer than the time it takes for a note to play
#define STEP_PAUSE 5
#define NOTE_PAUSE (STEP_PAUSE + 3)

typedef enum 
{
	easy,
	hard	
} GameModes;

void games_init(GameModes mode);
void games_step(unsigned char buttons);



#endif /* GAMES_H_ */