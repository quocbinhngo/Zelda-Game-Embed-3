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

void setting_stage(stage *option, stage *main, int *map);
void diff_stage(stage *option, stage *main, int *diff, int *map);
void menu_stage(stage *option, stage *main, int *diff, int *map);
void game_stage(stage *main, GameController *game_controller, int *diff, int *map, int * start_game);
void map_stage(stage *option, stage *main, int *map);
void pause_stage(stage *main, stage *map, int *start_game);

#endif