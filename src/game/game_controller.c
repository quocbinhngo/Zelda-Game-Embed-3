#include "game_controller.h"
#include "resources/player.h"
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
            (game_controller->game_map)[i][j] = 1;
            // uart_sendc('0' + (game_controller->game_map)[i][j]);
            // uart_puts(" ");
        }
        // uart_puts("\n");
    }
}

void InitPlayer(GameController *game_controller, Player *player)
{
    player->coor_x = GAME_WIDTH / 2, player->coor_y = GAME_HEIGHT / 2;
    DrawPlayer(game_controller, player);

    // drawRectARGB32(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH / 2 + TILE_SIZE, GAME_HEIGHT / 2 + TILE_SIZE, 0xffffff, 1);
}

void DrawPlayer(GameController *game_controller, Player *player)
{
    (game_controller->game_map)[player->coor_x][player->coor_y] = 1;
    drawImage(player->coor_x, player->coor_y, TILE_SIZE, TILE_SIZE, player_image_1);

    uart_dec(player->coor_x);
    uart_puts(" ");
    uart_dec(player->coor_y);
    uart_puts("\n");
}

void ErasePlayer(GameController *game_controller, Player *player)
{
    (game_controller->game_map)[player->coor_x][player->coor_y] = 0;
    drawRectARGB32(player->coor_x, player->coor_y, player->coor_x + TILE_SIZE, player->coor_y + TILE_SIZE, 0x000, 1);
}

void MovePlayer(GameController *game_controller, Player *player, char input)
{
    int has = 0;

    ErasePlayer(game_controller, player);

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
        player->coor_y = (player->coor_y + PLAYER_SPEED) < GAME_HEIGHT ? player->coor_y + PLAYER_SPEED : GAME_HEIGHT - PLAYER_SPEED;
        break;
    }
    case 'd':
    {
        has = 1;
        player->coor_x = (player->coor_x + PLAYER_SPEED) < GAME_WIDTH ? player->coor_x + PLAYER_SPEED : GAME_WIDTH - PLAYER_SPEED;
        break;
    }
    default:
        break;
    }

    // if (has)
    // {
    //     uart_puts("Has moved\n");
    // }

    DrawPlayer(game_controller, player);
}