#ifndef _GAME_CONTROLLER_H
#define _GAME_CONTROLLER_H

#include "game_const.h"
#include "player.h"



typedef struct GameController
{
    int game_map[GAME_HEIGHT][GAME_WIDTH];

    Enemy enemy_list[];
} GameController;



void ClearGameMap(GameController *game_controller);

void InitPlayer(GameController *game_controller, Player *player);
void DrawPlayer(GameController *game_controller, Player *player);
void MovePlayer(GameController *game_controller, Player *player, char input);
int IsMoveInput(char c);

#endif