#ifndef _GAME_CONTROLLER_H
#define _GAME_CONTROLLER_H

#include "game_const.h"
#include "player.h"
#include "enemy.h"

#define NUM_EMEMIES 10

typedef struct GameController
{
    int game_map[MAP_HEIGHT][MAP_WIDTH];
    Enemy enemy_list[NUM_EMEMIES];
    
} GameController;



void ClearGameMap(GameController *game_controller);

void InitPlayer(GameController *game_controller, Player *player);
void DrawPlayer(GameController *game_controller, Player *player);
void MovePlayer(GameController *game_controller, Player *player, char input);
void InitEnemy(GameController *game_controller, Enemy *enemy, int position);
//void InitEnemy(GameController *game_controller, Enemy *enemy);
void DrawEnemy(GameController *game_controller, Enemy *enemy);
void EraseEnemy(GameController *game_controller, Enemy *enemy);
void MoveEnemy(GameController *game_controller, Enemy *enemy, Player *player);
int IsMoveInput(char c);

#endif