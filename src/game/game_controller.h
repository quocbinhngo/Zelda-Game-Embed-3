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

//Define game controller struct
typedef struct GameController
{
    int game_map[MAP_HEIGHT][MAP_WIDTH], is_game_active;
    EnemyList enemy_list;
    Player player;

    int weapon_x, weapon_y;
    int score, diff, map;
} GameController;

//Function to start the game
void StartGame(GameController *game_controller, int *map);

//Function to clear the game map
void ClearGameMap(GameController *game_controller);


//Function to check for move input
int IsMoveInput(char c);

//Function to check for attack input
int IsAttackInput(char c);

//Function to check for exit input
int IsExitGameInput(char c);


//Function to initialize player
void InitPlayer(GameController *game_controller);

//Function to draw player on the screen
void DrawPlayer(GameController *game_controller, int player_mode);

//Function to move player around based on the input
void MovePlayer(GameController *game_controller, char input);

//Function that player character call to attack
void PlayerAttack(GameController *GameController);


//Function to initialize a new enemy
void InitEnemy(GameController *game_controller, int position);

//Function to draw enemy to the screen
void DrawEnemy(GameController *game_controller, Enemy *enemy);

//Function to erase enemy from the screen
void EraseEnemy(GameController *game_controller, Enemy *enemy);

//Function to move an enemy towards the player
void MoveEnemy(GameController *game_controller, Enemy *enemy);

//Function to move all enemies towards the player
void MoveEnemies(GameController *game_controller);

//Function enemies use to attack the player character
void EnemyAttack(GameController *game_controller);


//Function to draw the player's weapon when attacking
void DrawWeapon(GameController *game_controller);

//Function to erase the player's weapon
void EraseWeapon(GameController *GameController);


//Function to draw the player's health bar
void DrawHealthBar(GameController *game_controller);

//Function to draw the map
void DrawMap(int map_state);

//Function to redraw the map on a specific tile
void ReDrawMap(int x_coordinate, int y_coordinate, int map_state);

//Function to display the player's score
void DrawScore(GameController *game_controller);
#endif