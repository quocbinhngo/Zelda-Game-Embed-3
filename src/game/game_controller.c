#include "game_controller.h"
#include "resources/player.h"
#include "resources/enemy.h"
#include "player.h"


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

void ClearGameMap(GameController *game_controller)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            (game_controller->game_map)[i][j] = 0;
            // uart_sendc('0' + (game_controller->game_map)[i][j]);
            // uart_puts(" ");
        }
        // uart_puts("\n");
    }
}

void InitPlayer(GameController *game_controller, Player *player)
{
    player->coor_x = MAP_WIDTH / 2, player->coor_y = MAP_HEIGHT / 2;
    DrawPlayer(game_controller, player);

    // drawRectARGB32(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH / 2 + TILE_SIZE, GAME_HEIGHT / 2 + TILE_SIZE, 0xffffff, 1);
}

void DrawPlayer(GameController *game_controller, Player *player)
{
    (game_controller->game_map)[player->coor_x][player->coor_y] = 1;
    drawImage(player->coor_x*TILE_SIZE, player->coor_y*TILE_SIZE, TILE_SIZE, TILE_SIZE, player_image_1);

    uart_dec(player->coor_x);
    uart_puts(" ");
    uart_dec(player->coor_y);
    uart_puts("\n");
}

void ErasePlayer(GameController *game_controller, Player *player)
{
    (game_controller->game_map)[player->coor_x][player->coor_y] = 0;
    drawRectARGB32(player->coor_x*TILE_SIZE, player->coor_y*TILE_SIZE, player->coor_x*32 + TILE_SIZE, player->coor_y*32 + TILE_SIZE, 0x000, 1);
}

void MovePlayer(GameController *game_controller, Player *player, char input)
{
    int has = 0;

    ErasePlayer(game_controller, player);
    game_controller->game_map[player->coor_y][player->coor_x] = 0;
    switch (input)
    {
    case 'w':
    {
        has = 1;
        player->coor_y = (player->coor_y - PLAYER_SPEED) >= 0 ? player->coor_y - PLAYER_SPEED : 0;
        break;
    }
    case 'a':
    {
        has = 1;
        player->coor_x = (player->coor_x - PLAYER_SPEED) >= 0 ? player->coor_x - PLAYER_SPEED : 0;
        break;
    }
    case 's':
    {
        has = 1;
        player->coor_y = (player->coor_y + PLAYER_SPEED) < MAP_HEIGHT ? player->coor_y + PLAYER_SPEED : MAP_HEIGHT - PLAYER_SPEED;
        break;
    }
    case 'd':
    {
        has = 1;
        player->coor_x = (player->coor_x + PLAYER_SPEED) < MAP_WIDTH ? player->coor_x + PLAYER_SPEED : MAP_WIDTH - PLAYER_SPEED;
        break;
    }
    default:
        break;
    }

    // if (has)
    // {
    //     uart_puts("Has moved\n");
    // }
    game_controller->game_map[player->coor_y][player->coor_x] = 1;
    DrawPlayer(game_controller, player);
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
}


void DrawEnemy(GameController *game_controller, Enemy *enemy)
{
    (game_controller->game_map)[enemy->coor_x][enemy->coor_y] = 2;
    drawImage(enemy->coor_x*TILE_SIZE, enemy->coor_y*TILE_SIZE, TILE_SIZE, TILE_SIZE, enemy_image_1);

    uart_dec(enemy->coor_x);
    uart_puts(" ");
    uart_dec(enemy->coor_y);
    uart_puts("\n");
}

void EraseEnemy(GameController *game_controller, Enemy *enemy)
{
    (game_controller->game_map)[enemy->coor_x][enemy->coor_y] = 0;
    
    drawRectARGB32(enemy->coor_x*TILE_SIZE, enemy->coor_y*TILE_SIZE, enemy->coor_x*TILE_SIZE + TILE_SIZE, enemy->coor_y*TILE_SIZE + TILE_SIZE, 0x000, 1);
}

void MoveEnemy(GameController *game_controller, Enemy *enemy, Player *player)
{

    uart_puts("begin to move");
    int diff_x, diff_y;
    int direct_x, direct_y;


    if(player->coor_x < enemy->coor_x){
        diff_x = enemy->coor_x - player->coor_x;
        direct_x = 1;
    } else {
        diff_x = player->coor_x - enemy->coor_x;
        direct_x = -1;
    }


    if(player->coor_y < enemy->coor_y){
        diff_y = enemy->coor_y - player->coor_y;
        direct_y = 1;
    } else {
        diff_y = player->coor_y - enemy->coor_y;
        direct_y = -1;
    }

    // diff_x = player->coor_x < enemy->coor_x? enemy->coor_x - player->coor_x : player->coor_x - enemy->coor_x;
    // diff_y = player->coor_y < enemy->coor_y? enemy->coor_y - player->coor_y : player->coor_y - enemy->coor_y;
    int new_x = enemy-> coor_x, new_y = enemy-> coor_y;
    
    if(diff_x > diff_y){
        //move direction x
       if(direct_x > 0){
            new_x = (enemy->coor_x - ENEMY_SPEED);
       } else {
            new_x = (enemy->coor_x + ENEMY_SPEED);
       }
    }else{
        //move direction y
        if(direct_y > 0){
            new_y = enemy->coor_y - ENEMY_SPEED;
        } else {
            new_y = enemy->coor_y + ENEMY_SPEED;
        }
        
    }
    
    uart_dec(game_controller->game_map[new_y][new_x]);
    if(game_controller->game_map[new_y][new_x] == 1 || game_controller->game_map[new_y][new_x] == 2){
        
    }else{
        game_controller->game_map[enemy->coor_y][enemy->coor_x] = 0;
        uart_puts("moved");
        EraseEnemy(game_controller, enemy);
        enemy->coor_x = new_x;
        enemy->coor_y = new_y;
        game_controller->game_map[enemy->coor_y][enemy->coor_x] = 2;
        DrawEnemy(game_controller, enemy);
    }
   
    
}


