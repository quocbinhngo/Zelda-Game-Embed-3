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

#define CANCEL_ATTACK_TIMER 15

typedef struct GameController
{
    int game_map[MAP_HEIGHT][MAP_WIDTH], is_game_active;
    EnemyList enemy_list;
    Player player;

    int weapon_x, weapon_y;
    int score, diff, map, cancel_attack_timer;
} GameController;
// struct GameController
// {
//     int game_map[MAP_HEIGHT][MAP_WIDTH], is_game_active;
//     EnemyList enemy_list;
//     Player player;
// } ;

void StartGame(GameController *game_controller, int *map);
void ResumeGame(GameController *game_controller, int *map);
void ClearGameMap(GameController *game_controller);
void PrintGameMap(GameController *game_controller);

int IsMoveInput(char c);
int IsAttackInput(char c);
int IsExitGameInput(char c);
int IsPauseInput(char c);

void InitPlayer(GameController *game_controller);
void DrawPlayer(GameController *game_controller, int player_mode);
void MovePlayer(GameController *game_controller, char input);
void PlayerAttack(GameController *GameController);
void CancelAttack(GameController *game_controller);
// <<<<<<< HEAD
// void InitEnemy(GameController *game_controller, Enemy *enemy);
// == == == =

// >>>>>>> e223fbe58205e9d34ddaeba41ca0db18ada116ff
void DrawEnemy(GameController *game_controller, Enemy *enemy);
void EraseEnemy(GameController *game_controller, Enemy *enemy);
void MoveEnemy(GameController *game_controller, Enemy *enemy);
void EnemyAttack(GameController *game_controller);
void InitEnemy(GameController *game_controller, int position, int id);
void MoveEnemies(GameController *game_controller);
// void InitEnemy(GameController *game_controller, Enemy *enemy);

void DrawWeapon(GameController *game_controller);
void EraseWeapon(GameController *GameController);

void DrawHealthBar(GameController *game_controller);
void DrawMap(int map_state);
void ReDrawMap(int x_coordinate, int y_coordinate, int map_state);
void DrawScore(GameController *game_controller);
void DrawGameOver(GameController *game_controller);

void DrawObstacle(GameController *game_controller);
#endif