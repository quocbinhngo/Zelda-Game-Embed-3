#ifndef _PLAYER_H
#define _PLAYER_H

#define PLAYER_SPEED 1
#define ATTACK_DELAY 5

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define MAX_HP 100

typedef struct Player
{
    int coor_x, coor_y;
    int dir;
    int hp;
} Player;

#endif