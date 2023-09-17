#include "enemy.h"
#include "../uart.h"
void AddEnemy(Enemy *enemy, EnemyList *enemy_list)
{     
    uart_dec(enemy_list->num_enemies);
    enemy_list->enemies[(enemy_list->num_enemies)] = enemy;
    enemy_list->num_enemies += 1;
}
