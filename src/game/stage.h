#ifndef STAGE_H_
#define STAGE_H_

typedef enum
{
	MENU,
	SETTING,
	GAME,
	EXIT,
	DIFF,
	MAP
} stage;

void setting_stage(stage *option, stage *main, int *map_state);
void menu_stage(stage *option, stage *main, int *map_state);
void game_stage(stage *main);
void map_stage(stage *option, stage *main, int *map_state);

#endif