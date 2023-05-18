/*
 * games.h
 *
 * Created: 2023-05-16 18:29:18
 *  Author: Branden
 */ 


#ifndef GAMES_H_
#define GAMES_H_

#define EASY_LENGTH 10
#define HARD_LENGTH 15

typedef enum 
{
	easy,
	hard	
} GameModes;

void games_init(GameModes mode);
void games_step();



#endif /* GAMES_H_ */