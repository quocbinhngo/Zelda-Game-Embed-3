#ifndef _ENEMY_H
#define _ENEMY_H

#define ENEMY_SPEED 1
#define MOVE_DELAY 10
#define NUM_EMEMIES 2000
#define SPAWN_TIMER 50

typedef struct Enemy
{
    int coor_x, coor_y, active, moveCount, id, is_attack;
} Enemy;

typedef struct EnemyList
{
    Enemy enemies[NUM_EMEMIES];
    int num_enemies;
} EnemyList;

void AddEnemy(Enemy *enemy, EnemyList *enemy_list);

#endif