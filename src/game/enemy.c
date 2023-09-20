#include "enemy.h"

void AddEnemy(Enemy *enemy, EnemyList *enemy_list)
{
    enemy_list->enemies[enemy_list->num_enemies++] = *enemy;
}
