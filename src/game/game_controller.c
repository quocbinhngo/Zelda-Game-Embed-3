#include "game_controller.h"
#include "resources/player.h"
#include "resources/player_attack.h"
#include "resources/game_background.h"
#include "resources/enemy.h"
#include "resources/weapon.h"
#include "resources/map.h"
#include "resources/obstacle.h"
#include "player.h"
#include "../uart.h"
#include "../font/font.h"
#include "../framebf.h"
#include "resources/enemy_attack.h"

int IsMoveInput(char c)
{
    // Check if input is w, a, s, d
    switch (c)
    {
    case 'a':
    case 'd':
    case 'w':
    case 's':
    {
        return 1;
    }
    default:
    {
        return 0;
    }
    }
}

int IsAttackInput(char c)
{
    // Check if input is j
    return c == 'j';
}

int IsWeaponInput(char c)
{
    // Check if input is k
    return c == 'k';
}

int IsExitGameInput(char key) { return key == 'j'; }

int IsPauseInput(char c)
{
    // escape key
    return c == 27;
}

void StartGame(GameController *game_controller, int *map)
{
    game_controller->is_game_active = 1;
    game_controller->map = *map;

    ClearGameMap(game_controller, map);
    //InitObstacleGameMap(game_controller);
    InitPlayer(game_controller);

    game_controller->enemy_list.num_enemies = 0;
}

void ResumeGame(GameController *game_controller, int *map)
{
    DrawPlayer(game_controller, NORMAL_MODE);
    DrawObstacle(game_controller);
    //InitObstacleGameMap(game_controller);
}

void ClearGameMap(GameController *game_controller, int *map)
{
    game_controller->score = 0;


    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            (game_controller->game_map)[i][j] = (*map == 0 ? map_1[i][j] : (*map == 1 ? map_2[i][j] : map_3[i][j]));
        }
    }

    DrawObstacle(game_controller);
    
}

void InitObstacleGameMap(GameController *game_controller)
{
    game_controller->game_map[10][10] = 3;
    game_controller->game_map[11][10] = 3;
    game_controller->game_map[11][11] = 4;
    game_controller->game_map[11][12] = 5;

    DrawObstacle(game_controller);
}

void PrintGameMap(GameController *game_controller)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            uart_dec((game_controller->game_map)[i][j]);
            uart_puts(" ");
        }
        uart_puts("\n");
    }

    for (int i = 0; i < 10; i++)
    {
        uart_puts("\n");
    }
}

void InitPlayer(GameController *game_controller)
{
    Player player;

    //Assign starting location and default values for player
    player.coor_x = MAP_WIDTH / 2, player.coor_y = MAP_HEIGHT / 2;
    player.dir = DOWN;
    player.hp = MAX_HP;

    game_controller->player = player;
    game_controller->weapon = 0;
    DrawPlayer(game_controller, NORMAL_MODE);

    // drawRectARGB32(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH / 2 + TILE_SIZE, GAME_HEIGHT / 2 + TILE_SIZE, 0xffffff, 1);
}

void DrawPlayer(GameController *game_controller, int player_mode)
{
    // Player* player = game_controller->player;
    uart_puts("Player coor: ");
    uart_dec(game_controller->player.coor_x);
    uart_puts(" ");
    uart_dec(game_controller->player.coor_y);
    uart_puts("\n\n");

    (game_controller->game_map)[game_controller->player.coor_y][game_controller->player.coor_x] = PLAYER_CODE;

    //Draw character sprite based on current player mode
    switch (player_mode)
    {
    case NORMAL_MODE:
    {
        drawCharacterImage(game_controller->player.coor_x * TILE_SIZE, game_controller->player.coor_y * TILE_SIZE, TILE_SIZE, TILE_SIZE, player_image_allArray[game_controller->player.dir]);
        break;
    }
    case ATTACK_MODE:
    {
        drawCharacterImage(game_controller->player.coor_x * TILE_SIZE, game_controller->player.coor_y * TILE_SIZE, TILE_SIZE, TILE_SIZE, player_attack_image_allArray[game_controller->player.dir]);
        break;
    }

    default:
    {
        break;
    }
    }
}

void ErasePlayer(GameController *game_controller)
{
    // Player* player = game_controller->player;
    (game_controller->game_map)[game_controller->player.coor_y][game_controller->player.coor_x] = BLANK_CODE;
    ReDrawMap(game_controller->player.coor_x, game_controller->player.coor_y, game_controller->map);
}

void MovePlayer(GameController *game_controller, char input)
{
    Player *player = &game_controller->player;

    // ErasePlayer(game_controller, player);

    int new_x = player->coor_x, new_y = player->coor_y;

    //Calculate the player's new position based on the move input
    switch (input)
    {
    case 'w':
    {
        new_y = (player->coor_y - PLAYER_SPEED) >= 0 ? player->coor_y - PLAYER_SPEED : 0;
        player->dir = UP;
        break;
    }
    case 'a':
    {
        new_x = (player->coor_x - PLAYER_SPEED) >= 0 ? player->coor_x - PLAYER_SPEED : 0;
        player->dir = LEFT;
        break;
    }
    case 's':
    {
        new_y = (player->coor_y + PLAYER_SPEED) < MAP_HEIGHT ? player->coor_y + PLAYER_SPEED : MAP_HEIGHT - PLAYER_SPEED;
        player->dir = DOWN;
        break;
    }
    case 'd':
    {
        new_x = (player->coor_x + PLAYER_SPEED) < MAP_WIDTH ? player->coor_x + PLAYER_SPEED : MAP_WIDTH - PLAYER_SPEED;
        player->dir = RIGHT;
        break;
    }
    default:
        break;
    }

    //Check if the new location is blank & move the player there if it is
    switch ((game_controller->game_map)[new_y][new_x])
    {
    case BLANK_CODE:
    {
        ErasePlayer(game_controller);
        EraseWeapon(game_controller);

        player->coor_x = new_x, player->coor_y = new_y;
        DrawPlayer(game_controller, NORMAL_MODE);
        break;
    }
    // case ENEMY_CODE:
    // {
    //     DrawPlayer(game_controller, NORMAL_MODE);

    //     // for (int i = 0; i < game_controller->enemy_list.num_enemies; i++)
    //     // {
    //     //     Enemy *cur_enemy = &(game_controller->enemy_list.enemies[i]);
    //     //     if (cur_enemy->coor_x == new_x && cur_enemy->coor_y == new_y)
    //     //     {
    //     //         EnemyAttack(game_controller, cur_enemy);
    //     //         break;
    //     //     }
    //     // }
    // }
    // case 3:
    // {
    // }
    default:
    {
        break;
    }
    }
}

void ChangeWeapon(GameController *game_controller)
{
    //Cycle between 3 different weapons
    game_controller->weapon = (game_controller->weapon + 1) % 3;
}

void InitEnemy(GameController *game_controller, int position, int id)
{
    Enemy enemy;
    enemy.id = id;
    enemy.is_attack = 0;
    // uart_puts("Ptr enemy: ");
    // uart_hex(&enemy);
    // uart_puts("\n");

    //Check which position the enemy will spawn in
    switch (position)
    {
    case 0:
    {
        enemy.coor_x = 0, enemy.coor_y = 0;
        break;
    }
    case 1:
    {
        enemy.coor_x = MAP_WIDTH, enemy.coor_y = 0;
        break;
    }
    case 2:
    {
        enemy.coor_x = MAP_WIDTH, enemy.coor_y = MAP_HEIGHT;
        break;
    }
    case 3:
    {
        enemy.coor_x = 0, enemy.coor_y = MAP_HEIGHT;
        break;
    }
    default:
    {
        enemy.coor_x = 0, enemy.coor_y = 0;
        break;
    }
    }

    game_controller->game_map[enemy.coor_y][enemy.coor_x] = 2;
    enemy.active = 1;

    DrawEnemy(game_controller, &enemy);
    AddEnemy(&enemy, &game_controller->enemy_list);
}

void DrawEnemy(GameController *game_controller, Enemy *enemy)
{

    (game_controller->game_map)[enemy->coor_y][enemy->coor_x] = ENEMY_CODE;

    if (enemy->is_attack)
    {
        drawCharacterImage(enemy->coor_x * TILE_SIZE, enemy->coor_y * TILE_SIZE, TILE_SIZE, TILE_SIZE, enemy_attack_image_allArray[enemy->id - 1]);
    }
    else
    {
        drawCharacterImage(enemy->coor_x * TILE_SIZE, enemy->coor_y * TILE_SIZE, TILE_SIZE, TILE_SIZE, enemy_image_allArray[enemy->id - 1]);
    }
}

void EraseEnemy(GameController *game_controller, Enemy *enemy)
{
    (game_controller->game_map)[enemy->coor_y][enemy->coor_x] = BLANK_CODE;
    ReDrawMap(enemy->coor_x, enemy->coor_y, game_controller->map);
}

void MoveEnemy(GameController *game_controller, Enemy *enemy)
{
    Player *player = &game_controller->player;

    enemy->moveCount++;

    // if (enemy->moveCount < (MOVE_DELAY / (game_controller->diff + 1)))
    if (enemy->moveCount < (MOVE_DELAY / (game_controller->diff + 1)))
    {
        return;
    }

    enemy->moveCount = 0;

    int diff_x, diff_y;
    int direct_x, direct_y;

    //Calculate the direction towards the player
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
    int sub_new_x = enemy->coor_x, sub_new_y = enemy->coor_y;

    //Move towards the direction between x and y with shorter distance
    if (diff_x > diff_y)
    {
        //move direction x
        new_x = (direct_x > 0) ? (enemy->coor_x - ENEMY_SPEED) : (enemy->coor_x + ENEMY_SPEED);
        sub_new_y = (direct_y > 0) ? enemy->coor_y - ENEMY_SPEED : enemy->coor_y + ENEMY_SPEED;
    }
    else
    {
        // move direction y
        new_y = (direct_y > 0) ? enemy->coor_y - ENEMY_SPEED : enemy->coor_y + ENEMY_SPEED;
        sub_new_x = (direct_x > 0) ? (enemy->coor_x - ENEMY_SPEED) : (enemy->coor_x + ENEMY_SPEED);
    }

    //Check if the new enemy position is blank or has the player
    switch ((game_controller->game_map)[new_y][new_x])
    {
    case BLANK_CODE:
    {
        //move to the new position if blank
        EraseEnemy(game_controller, enemy);
        enemy->coor_x = new_x, enemy->coor_y = new_y;

        DrawEnemy(game_controller, enemy);
        break;
    }
    case PLAYER_CODE:
    {
        //attack if encounter the player but stand still
        EnemyAttack(game_controller, enemy);
        break;
    }
    default:
    {
        if ((game_controller->game_map)[sub_new_y][sub_new_x] == BLANK_CODE){
            EraseEnemy(game_controller, enemy);
            enemy->coor_x = sub_new_x, enemy->coor_y = sub_new_y;

            DrawEnemy(game_controller, enemy);
        }
        break;
    }
    }
}

void EnemyAttack(GameController *game_controller, Enemy *enemy)
{
    //Draw enemy attack sprite
    EraseEnemy(game_controller, enemy);
    enemy->is_attack = 1;
    DrawEnemy(game_controller, enemy);

    Player *player = &game_controller->player;
    //Reduce player health
    player->hp -= 10;

    if (player->hp > 0)
    {
        return;
    }

    //If player health reaches 0 then erase player and end the game
    game_controller->game_map[player->coor_y][player->coor_x] = BLANK_CODE;
    game_controller->is_game_active = 0;
    ErasePlayer(game_controller);
}

void PlayerAttack(GameController *game_controller)
{
    Player *player = &game_controller->player;
    int attack_loc_x = player->coor_x, attack_loc_y = player->coor_y;

    ErasePlayer(game_controller);
    DrawPlayer(game_controller, ATTACK_MODE);

    //Check which direction the player is facing to calculate the attack tile
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

    //Do nothing if the attack tile has an obstacle
    if (game_controller->game_map[attack_loc_y][attack_loc_x] >= 3)
    {
        return;
    }

    game_controller->weapon_x = attack_loc_x, game_controller->weapon_y = attack_loc_y;

    //Check if any enemy in the enemy list is in the attack tile
    for (int i = 0; i < game_controller->enemy_list.num_enemies; i++)
    {
        Enemy *enemy = &game_controller->enemy_list.enemies[i];

        if (enemy->coor_x == attack_loc_x && enemy->coor_y == attack_loc_y && enemy->active)
        {
            game_controller->enemy_list.enemies[i].active = 0;
            EraseEnemy(game_controller, enemy);
            game_controller->score++;
        }
    }

    //Draw attack weapon
    DrawWeapon(game_controller);
    game_controller->cancel_attack_timer = 1;

}

void CancelAttack(GameController *game_controller)
{
    ErasePlayer(game_controller);
    EraseWeapon(game_controller);
    DrawPlayer(game_controller, NORMAL_MODE);
}

void MoveEnemies(GameController *game_controller)
{
    //Move every active enemy towards the player
    for (int i = 0; i < game_controller->enemy_list.num_enemies; i++)
    {
        Enemy *enemy = &(game_controller->enemy_list.enemies[i]);
        if (!enemy->active)
        {
            continue;
        }

        MoveEnemy(game_controller, enemy);
    }
}

void DrawWeapon(GameController *game_controller)
{
    drawCharacterImage(game_controller->weapon_x * TILE_SIZE, game_controller->weapon_y * TILE_SIZE, TILE_SIZE, TILE_SIZE, weapon_image_allArray[game_controller->weapon]);
}

void EraseWeapon(GameController *game_controller)
{
    ReDrawMap(game_controller->weapon_x, game_controller->weapon_y, game_controller->map);
}

void DrawHealthBar(GameController *game_controller)
{
    drawRectARGB32(17, GAME_HEIGHT - 33, 223, GAME_HEIGHT - 7, 0xb9c4bc, 1);
    drawRectARGB32(20, GAME_HEIGHT - 30, 220, GAME_HEIGHT - 10, 0x00000000, 1);
    drawRectARGB32(20, GAME_HEIGHT - 30, game_controller->player.hp * 2 + 20, GAME_HEIGHT - 10, 0x00FF0000, 1);
}

void DrawMap(int map_state)
{
    for (int y = 0; y < GAME_HEIGHT; y++)
    {
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            drawPixelARGB32(x, y, game_background_image_allArray[map_state][y * GAME_WIDTH + x]);
        }
    }
}

void ReDrawMap(int x_coordinate, int y_coordinate, int map_state)
{
    for (int y_pixel = y_coordinate * TILE_SIZE; y_pixel < y_coordinate * TILE_SIZE + TILE_SIZE; y_pixel++)
    {
        for (int x_pixel = x_coordinate * TILE_SIZE; x_pixel < x_coordinate * TILE_SIZE + TILE_SIZE; x_pixel++)
        {
            drawPixelARGB32(x_pixel, y_pixel, game_background_image_allArray[map_state][y_pixel * GAME_WIDTH + x_pixel]);
        }
    }
}

void DrawScore(GameController *game_controller)
{
    char temp_buffer[5], score[5];
    int currentScore = game_controller->score, i = 4, j = 0;
    //Turn score to string
    do
    {
        temp_buffer[i] = (currentScore % 10) + '0';
        i--;
        currentScore /= 10;
    } while (currentScore != 0);
    for (i = i + 1; i < 5; i++)
    {
        score[j] = temp_buffer[i];
        j++;
    }
    score[j] = 0;

    stringFont((MAP_WIDTH / 2 - 5) * TILE_SIZE, TILE_SIZE, "Score: ", 0x00ffffff, LARGE_FONT);
    //If the tiles are occupied by player, the tile will not be redrawn since it will erase the player
    //
    if (game_controller->game_map[1][MAP_WIDTH / 2 + 2] != PLAYER_CODE)
    {
        ReDrawMap(MAP_WIDTH / 2 + 2, 1, game_controller->map);
    }
    if (game_controller->game_map[1][MAP_WIDTH / 2 + 3] != PLAYER_CODE)
    {
        ReDrawMap(MAP_WIDTH / 2 + 3, 1, game_controller->map);
    }
    if (game_controller->game_map[1][MAP_WIDTH / 2 + 4] != PLAYER_CODE)
    {
        ReDrawMap(MAP_WIDTH / 2 + 4, 1, game_controller->map);
    }
    if (game_controller->game_map[2][MAP_WIDTH / 2 + 2] != PLAYER_CODE)
    {
        ReDrawMap(MAP_WIDTH / 2 + 2, 2, game_controller->map);
    }
    if (game_controller->game_map[2][MAP_WIDTH / 2 + 3] != PLAYER_CODE)
    {
        ReDrawMap(MAP_WIDTH / 2 + 3, 2, game_controller->map);
    }
    if (game_controller->game_map[2][MAP_WIDTH / 2 + 4] != PLAYER_CODE)
    {
        ReDrawMap(MAP_WIDTH / 2 + 4, 2, game_controller->map);
    }

    //Display the score
    stringFont((MAP_WIDTH / 2 + 2) * TILE_SIZE, TILE_SIZE, score, 0x00ffffff, LARGE_FONT);
}

void DrawGameOver(GameController *game_controller)
{
    //Turn score to string
    char temp_buffer[5], score[5];
    int currentScore = game_controller->score, i = 4, j = 0;
    do
    {
        temp_buffer[i] = (currentScore % 10) + '0';
        i--;
        currentScore /= 10;
    } while (currentScore != 0);
    for (i = i + 1; i < 5; i++)
    {
        score[j] = temp_buffer[i];
        j++;
    }
    score[j] = 0;
    // Draw game over window
    drawRectARGB32(GAME_WIDTH / 4, GAME_HEIGHT / 4, GAME_WIDTH * 3 / 4, GAME_HEIGHT * 3 / 4, 0x00000000, 1);
    drawRectARGB32(GAME_WIDTH / 4 + 2, GAME_HEIGHT / 4 + 2, GAME_WIDTH * 3 / 4 - 2, GAME_HEIGHT * 3 / 4 - 2, 0xb07a05, 1);
    drawRectARGB32(GAME_WIDTH / 4 + 10, GAME_HEIGHT / 4 + 10, GAME_WIDTH * 3 / 4 - 10, GAME_HEIGHT * 3 / 4 - 10, 0x00000000, 1);
    drawRectARGB32(GAME_WIDTH / 4 + 12, GAME_HEIGHT / 4 + 12, GAME_WIDTH * 3 / 4 - 12, GAME_HEIGHT * 3 / 4 - 12, 0xebb134, 1);

    stringFont((MAP_WIDTH / 2 - 5) * TILE_SIZE, GAME_HEIGHT / 2 - 150, "Game Over", 0x00ffffff, LARGE_FONT);
    stringFont((MAP_WIDTH / 2 - 4) * TILE_SIZE, GAME_HEIGHT / 2 - 50, "Score: ", 0x00ffffff, LARGE_FONT);
    stringFont((MAP_WIDTH / 2 + 3) * TILE_SIZE, GAME_HEIGHT / 2 - 50, score, 0x00ffffff, LARGE_FONT);

    stringFont((MAP_WIDTH / 3 * 4 + 4) * TILE_SIZE, (MAP_HEIGHT / 2 + 3) * TILE_SIZE, "Press 'j' to get back to Menu screen", 0x00ffffff, SMALL_FONT);
}

void CancelEnemyAttack(GameController *game_controller)
{
    //Loop through enemy list to cancel attacking enemy
    for (int i = 0; i < game_controller->enemy_list.num_enemies; i++)
    {
        Enemy *enemy = &(game_controller->enemy_list.enemies[i]);
        if (enemy->is_attack == 0)
        {
            continue;
        }

        if (enemy->is_attack < 15)
        {
            enemy->is_attack++;
            continue;
        }

        enemy->is_attack = 0;
        EraseEnemy(game_controller, enemy);
        DrawEnemy(game_controller, enemy);

    }
}

void DrawObstacle(GameController *game_controller)
{
    //Loop through game map and draw obstacle
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (game_controller->game_map[y][x] >= 3)
            {
                drawCharacterImage(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, obstacle_allArray[(game_controller->game_map[y][x] - 3) + (game_controller->map == 0 ? 0 : (game_controller->map == 1 ? 3 : 6))]);
            }
        }
        
    }
}
