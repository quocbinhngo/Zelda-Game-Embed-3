#include "game_controller.h"
#include "resources/player.h"
#include "resources/enemy.h"
#include "player.h"
#include "../uart.h"

int IsMoveInput(char c)
{
    switch (c)
    {
    case 'a':
    case 'd':
    case 'w':
    case 's':
    {
        return 1;
    }
    /* code */
    default:
    {
        return 0;
    }
    }
}

int IsAttackInput(char c)
{
    switch (c)
    {
    case 'j':
    {
        return 1;
    }
    /* code */
    default:
    {
        return 0;
    }
    }
}

void ClearGameMap(GameController *game_controller)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {

            (game_controller->game_map)[i][j] = BLANK_CODE;

        }
    }
}

void InitPlayer(GameController *game_controller)
{
    Player *player = (&game_controller->player);
    player->coor_x = MAP_WIDTH / 2, player->coor_y = MAP_HEIGHT / 2;
    player->dir = DOWN;
    DrawPlayer(game_controller);

    // drawRectARGB32(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH / 2 + TILE_SIZE, GAME_HEIGHT / 2 + TILE_SIZE, 0xffffff, 1);
}

void DrawPlayer(GameController *game_controller)
{
    Player *player = (&game_controller->player);
    (game_controller->game_map)[player->coor_x][player->coor_y] = PLAYER_CODE;
    drawImage(player->coor_x * TILE_SIZE, player->coor_y * TILE_SIZE, TILE_SIZE, TILE_SIZE, player_image_allArray[player->dir]);
}

void ErasePlayer(GameController *game_controller)
{
    Player *player = (&game_controller->player);
    (game_controller->game_map)[player->coor_x][player->coor_y] = BLANK_CODE;
    drawRectARGB32(player->coor_x * TILE_SIZE, player->coor_y * TILE_SIZE, player->coor_x * 32 + TILE_SIZE, player->coor_y * 32 + TILE_SIZE, 0x000, 1);
}

void MovePlayer(GameController *game_controller, char input)
{
    Player *player = (&game_controller->player);
    int has = 0;

    ErasePlayer(game_controller);

    int new_x = player->coor_x, new_y = player->coor_y;

    switch (input)
    {
    case 'w':
    {
        has = 1;
        new_y = (player->coor_y - PLAYER_SPEED) >= 0 ? player->coor_y - PLAYER_SPEED : 0;
        player->dir = UP;
        break;
    }
    case 'a':
    {
        has = 1;
        new_x = (player->coor_x - PLAYER_SPEED) >= 0 ? player->coor_x - PLAYER_SPEED : 0;
        player->dir = LEFT;
        break;
    }
    case 's':
    {
        has = 1;
        new_y = (player->coor_y + PLAYER_SPEED) < MAP_HEIGHT ? player->coor_y + PLAYER_SPEED : MAP_HEIGHT - PLAYER_SPEED;
        player->dir = DOWN;
        break;
    }
    case 'd':
    {
        has = 1;
        new_x = (player->coor_x + PLAYER_SPEED) < MAP_WIDTH ? player->coor_x + PLAYER_SPEED : MAP_WIDTH - PLAYER_SPEED;
        player->dir = RIGHT;
        break;
    }
    default:
        break;
    }


    switch ((game_controller->game_map)[new_x][new_y])
    {
    case BLANK_CODE:
    {
        ErasePlayer(game_controller);
        player->coor_x = new_x, player->coor_y = new_y;
        DrawPlayer(game_controller);
        break;
    }
    case ENEMY_CODE:
    {
        EnemyAttack(game_controller);
    }
    default:
    {
        break;
    }
    }

}

void InitEnemy(GameController *game_controller, Enemy *enemy, int position)
{
    switch (position)
    {
    case 0:
        enemy->coor_x = 0, enemy->coor_y = 0;
        break;
    case 1:
        enemy->coor_x = MAP_WIDTH, enemy->coor_y = 0;
        break;
    case 2:
        enemy->coor_x = MAP_WIDTH, enemy->coor_y = MAP_HEIGHT;
        break;
    case 3:
        enemy->coor_x = 0, enemy->coor_y = MAP_HEIGHT;
        break;
    default:
        break;
    }

    game_controller->game_map[enemy->coor_y][enemy->coor_x] = 2;
    enemy->active = 1;


    
    DrawEnemy(game_controller, enemy);
    AddEnemy(enemy, game_controller->enemy_list);

    uart_hex(enemy);
    uart_puts(" ");
    uart_hex((game_controller->enemy_list->enemies[0]));
    uart_puts("\n");
}


void DrawEnemy(GameController *game_controller, Enemy *enemy)
{
    (game_controller->game_map)[enemy->coor_x][enemy->coor_y] = ENEMY_CODE;
    drawImage(enemy->coor_x * TILE_SIZE, enemy->coor_y * TILE_SIZE, TILE_SIZE, TILE_SIZE, enemy_image_1);

    uart_dec(enemy->coor_x);
    uart_puts(" ");
    uart_dec(enemy->coor_y);
    uart_puts("\n");
}

void EraseEnemy(GameController *game_controller, Enemy *enemy)
{
    (game_controller->game_map)[enemy->coor_x][enemy->coor_y] = BLANK_CODE;

    drawRectARGB32(enemy->coor_x * TILE_SIZE, enemy->coor_y * TILE_SIZE, enemy->coor_x * TILE_SIZE + TILE_SIZE, enemy->coor_y * TILE_SIZE + TILE_SIZE, 0x000, 1);
}

void MoveEnemy(GameController *game_controller, Enemy *enemy)
{
    Player *player = (&game_controller->player);
    enemy->moveCount++;

    if (enemy->moveCount < MOVE_DELAY)
    {
        return;
    }

    enemy->moveCount = 0;

    uart_puts("begin to move\n");
    int diff_x, diff_y;
    int direct_x, direct_y;

    if (player->coor_x < enemy->coor_x)
    {
        diff_x = enemy->coor_x - player->coor_x;
        direct_x = 1;
    }
    else
    {
        diff_x = player->coor_x - enemy->coor_x;
        direct_x = -1;
    }

    if (player->coor_y < enemy->coor_y)
    {
        diff_y = enemy->coor_y - player->coor_y;
        direct_y = 1;
    }
    else
    {
        diff_y = player->coor_y - enemy->coor_y;
        direct_y = -1;
    }

    // diff_x = player->coor_x < enemy->coor_x? enemy->coor_x - player->coor_x : player->coor_x - enemy->coor_x;
    // diff_y = player->coor_y < enemy->coor_y? enemy->coor_y - player->coor_y : player->coor_y - enemy->coor_y;
    int new_x = enemy->coor_x, new_y = enemy->coor_y;

    if (diff_x > diff_y)
    {
        new_x = (direct_x > 0) ? (enemy->coor_x - ENEMY_SPEED) : (enemy->coor_x + ENEMY_SPEED);
    }

    else
    {
        // move direction y
        new_y = (direct_y > 0) ? enemy->coor_y - ENEMY_SPEED : enemy->coor_y + ENEMY_SPEED;
    }

    switch ((game_controller->game_map)[new_x][new_y])
    {
    case BLANK_CODE:
    {
        EraseEnemy(game_controller, enemy);
        enemy->coor_x = new_x;
        enemy->coor_y = new_y;

        uart_puts("Enemy loc: ");
        uart_dec(enemy->coor_x);
        uart_puts(" ");
        uart_dec(enemy->coor_y);
        uart_puts("\n");

        DrawEnemy(game_controller, enemy);
        break;
    }
    case PLAYER_CODE:
    {
        EnemyAttack(game_controller);
        break;
    }
    default:
    {
        break;
    }
    }
}

void EnemyAttack(GameController *game_controller)
{
}

void PlayerAttack(GameController *game_controller)
{
    Player *player = (&game_controller->player);
    
    int attack_loc_x = player->coor_x, attack_loc_y = player->coor_y;

    switch (player->dir)
    {
    case UP:
    {
        if (attack_loc_y - 1 < 0)
        {
            return;
        }
        attack_loc_y--;
        break;
    }
    case RIGHT:
    {
        if (attack_loc_x + 1 >= MAP_WIDTH)
        {
            return;
        }
        attack_loc_x++;
        break;
    }
    case DOWN:
    {
        if (attack_loc_y + 1 >= MAP_HEIGHT)
        {
            return;
        }
        attack_loc_y++;
        break;
    }
    case LEFT:
    {
        if (attack_loc_x - 1 < 0)
        {
            return;
        }
        attack_loc_x--;
        break;
    }
    default:
    {
        break;
    }
    }

    for (int i = 0; i < game_controller->enemy_list->num_enemies; i++)
    {
        Enemy *enemy = game_controller->enemy_list->enemies[i];

        uart_puts("Attack: ");
        uart_dec(attack_loc_x);
        uart_puts(" ");
        uart_dec(attack_loc_y);
        uart_puts("\n");

        uart_puts("Enemy: ");
        uart_dec(enemy->coor_x);
        uart_puts(" ");
        uart_dec(enemy->coor_y);
        uart_puts("\n\n");

        if (enemy->coor_x == attack_loc_x && enemy->coor_y == attack_loc_y)
        {
        }
    }
}