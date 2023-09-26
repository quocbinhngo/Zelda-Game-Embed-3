#ifndef STAGE_H_
#define STAGE_H_

#include "game_controller.h"

typedef enum
{
	MENU,
	SETTING,
	GAME,
	EXIT,
	DIFF,
	MAP,
	PAUSE
} stage;

//Function to display setting menu
void setting_stage(stage *option, stage *main, int *map);

//Function to display difficulty menu
void diff_stage(stage *option, stage *main, int *diff, int *map);

//Function to display main menu
void menu_stage(stage *option, stage *main, int *diff, int *map);

//Function to start the game from the main menu
void game_stage(stage *main, GameController *game_controller, int *diff, int *map, int * start_game);

//Function to display map select menu
void map_stage(stage *option, stage *main, int *map);

//Function to pause the game and display pause menu
void pause_stage(stage *main, int *map, int *start_game);

#endif