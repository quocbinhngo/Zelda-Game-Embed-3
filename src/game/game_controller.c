#include "game_controller.h"
#include "resources/player.h"
#include "resources/player_attack.h"
#include "resources/game_background.h"
#include "resources/enemy.h"
#include "resources/weapon.h"
#include "player.h"
#include "../uart.h"
#include "../font/font.h"

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

int IsExitGameInput(char key) { return key == 'j'; }

int IsPauseInput(char c)
{
    // escape key
    return c == 27;
}

void StartGame(GameController *game_controller, int *map)
{
    game_controller->is_game_active = 1;
    game_controller->map = map;

    ClearGameMap(game_controller);
    InitPlayer(game_controller);

    game_controller->enemy_list.num_enemies = 0;
}

void ResumeGame(GameController *game_controller, int *map)
{
    DrawPlayer(game_controller, NORMAL_MODE);
}

void ClearGameMap(GameController *game_controller)
{
    game_controller->score = 0;
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
    Player player;

    player.coor_x = MAP_WIDTH / 2, player.coor_y = MAP_HEIGHT / 2;
    player.dir = DOWN;
    player.hp = MAX_HP;

    game_controller->player = player;
    DrawPlayer(game_controller, NORMAL_MODE);

    // drawRectARGB32(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH / 2 + TILE_SIZE, GAME_HEIGHT / 2 + TILE_SIZE, 0xffffff, 1);
}

void DrawPlayer(GameController *game_controller, int player_mode)
{

    // Player* player = game_controller->player;
    (game_controller->game_map)[game_controller->player.coor_x][game_controller->player.coor_y] = PLAYER_CODE;

    switch (player_mode)
    {
    case NORMAL_MODE:
    {
        drawImage(game_controller->player.coor_x * TILE_SIZE, game_controller->player.coor_y * TILE_SIZE, TILE_SIZE, TILE_SIZE, player_image_allArray[game_controller->player.dir]);
        break;
    }
    case ATTACK_MODE:
    {
        drawImage(game_controller->player.coor_x * TILE_SIZE, game_controller->player.coor_y * TILE_SIZE, TILE_SIZE, TILE_SIZE, player_attack_image_allArray[game_controller->player.dir]);
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
    (game_controller->game_map)[game_controller->player.coor_x][game_controller->player.coor_y] = BLANK_CODE;
    ReDrawMap(game_controller->player.coor_x, game_controller->player.coor_y, game_controller->map);
}

void MovePlayer(GameController *game_controller, char input)
{
    Player *player = &game_controller->player;
    int has = 0;

    // ErasePlayer(game_controller, player);

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
        EraseWeapon(game_controller);

        player->coor_x = new_x, player->coor_y = new_y;
        DrawPlayer(game_controller, NORMAL_MODE);
        break;
    }
    case ENEMY_CODE:
    {
        DrawPlayer(game_controller, NORMAL_MODE);
        EnemyAttack(game_controller);
    }
    default:
    {
        break;
    }
    }
}

void InitEnemy(GameController *game_controller, int position)
{
    Enemy enemy;

    uart_puts("Ptr enemy: ");
    uart_hex(&enemy);
    uart_puts("\n");

    switch (position)
    {
    case 0:
        enemy.coor_x = 0, enemy.coor_y = 0;
        break;
    case 1:
        enemy.coor_x = MAP_WIDTH, enemy.coor_y = 0;
        break;
    case 2:
        enemy.coor_x = MAP_WIDTH, enemy.coor_y = MAP_HEIGHT;
        break;
    case 3:
        enemy.coor_x = 0, enemy.coor_y = MAP_HEIGHT;
        break;
    default:
        break;
    }

    game_controller->game_map[enemy.coor_y][enemy.coor_x] = 2;
    enemy.active = 1;

    DrawEnemy(game_controller, &enemy);
    AddEnemy(&enemy, &game_controller->enemy_list);
}

void DrawEnemy(GameController *game_controller, Enemy *enemy)
{
    (game_controller->game_map)[enemy->coor_x][enemy->coor_y] = ENEMY_CODE;
    drawImage(enemy->coor_x * TILE_SIZE, enemy->coor_y * TILE_SIZE, TILE_SIZE, TILE_SIZE, enemy_image_1);
}

void EraseEnemy(GameController *game_controller, Enemy *enemy)
{
    (game_controller->game_map)[enemy->coor_x][enemy->coor_y] = BLANK_CODE;

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

    uart_puts("move cnt\n");
    uart_dec(enemy->moveCount);

    enemy->moveCount = 0;

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
        enemy->coor_x = new_x, enemy->coor_y = new_y;

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
    Player *player = &game_controller->player;
    player->hp -= 10;

    if (player->hp > 0)
    {
        return;
    }

    game_controller->game_map[player->coor_x][player->coor_y] = BLANK_CODE;
    game_controller->is_game_active = 0;
    ErasePlayer(game_controller);
}

void PlayerAttack(GameController *game_controller)
{
    Player *player = &game_controller->player;
    int attack_loc_x = player->coor_x, attack_loc_y = player->coor_y;

    ErasePlayer(game_controller);
    DrawPlayer(game_controller, ATTACK_MODE);

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

    game_controller->weapon_x = attack_loc_x, game_controller->weapon_y = attack_loc_y;

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

    DrawWeapon(game_controller);

    // cancel danh animation
    // for (int i = 0; i < 1e9; i++) {
    // }

    // ErasePlayer(game_controller);
    // DrawPlayer(game_controller, NORMAL_MODE);
}

void MoveEnemies(GameController *game_controller)
{
    for (int i = 0; i < game_controller->enemy_list.num_enemies; i++)
    {
        Enemy *enemy = &game_controller->enemy_list.enemies[i];
        if (!enemy->active)
        {
            continue;
        }

        MoveEnemy(game_controller, enemy);
    }
}

void DrawWeapon(GameController *game_controller)
{
    drawImage(game_controller->weapon_x * TILE_SIZE, game_controller->weapon_y * TILE_SIZE, TILE_SIZE, TILE_SIZE, weapon_image_allArray[0]);
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
    drawRectARGB32(GAME_WIDTH / 2 + 25, TILE_SIZE, GAME_WIDTH / 2 + 50, TILE_SIZE + 10, 0x00000000, 1);
    stringFont(GAME_WIDTH / 2 - 25, TILE_SIZE, "Score: ", 0x00ffffff, SMALL_FONT);
    stringFont(GAME_WIDTH / 2 + 25, TILE_SIZE, score, 0x00ffffff, SMALL_FONT);
}