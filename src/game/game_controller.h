#ifndef _GAME_CONTROLLER_H
#define _GAME_CONTROLLER_H

#include "game_const.h"
#include "player.h"
#include "enemy.h"

#define BLANK_CODE 0
#define PLAYER_CODE 1
#define ENEMY_CODE 2

#define NORMAL_MODE 0
#define ATTACK_MODE 1

typedef struct GameController
{
    int game_map[MAP_HEIGHT][MAP_WIDTH], is_game_active;
    EnemyList enemy_list;
    Player player;

    int weapon_x, weapon_y;
} GameController;
// struct GameController
// {
//     int game_map[MAP_HEIGHT][MAP_WIDTH], is_game_active;
//     EnemyList enemy_list;
//     Player player;
// } ;


void StartGame(GameController *game_controller);
void ClearGameMap(GameController *game_controller);

int IsMoveInput(char c);
int IsAttackInput(char c);
int IsExitGameInput(char c);

void InitPlayer(GameController *game_controller);
void DrawPlayer(GameController *game_controller, int player_mode);
void MovePlayer(GameController *game_controller, char input);
void PlayerAttack(GameController *GameController);
// <<<<<<< HEAD
// void InitEnemy(GameController *game_controller, Enemy *enemy);
// == == == =

// >>>>>>> e223fbe58205e9d34ddaeba41ca0db18ada116ff
void DrawEnemy(GameController *game_controller, Enemy *enemy);
void EraseEnemy(GameController *game_controller, Enemy *enemy);
void MoveEnemy(GameController *game_controller, Enemy *enemy);
void EnemyAttack( GameController *game_controller);
void InitEnemy( GameController *game_controller, int position);
void MoveEnemies(GameController *game_controller);
// void InitEnemy(GameController *game_controller, Enemy *enemy);

void DrawWeapon(GameController *game_controller);
void EraseWeapon(GameController *GameController);
#endif