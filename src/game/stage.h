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

void setting_stage(stage *option, stage *main);
void diff_stage(stage *option, stage *main, int *diff);
void menu_stage(stage *option, stage *main, int *diff);
void game_stage(stage *main, int *diff);

#endif