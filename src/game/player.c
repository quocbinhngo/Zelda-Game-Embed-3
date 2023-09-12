#include "../framebf.h"
#include "resources/player.h"
#include "player.h"
#include "game_const.h"
#include "game_controller.h"

void init_player(GameController *game_controller)
{
    // draw player character
    //   drawRectARGB32(50,50,100,100, 0x00000000, 1);

   (game_controller->game_map)[GAME_HEIGHT / 2][GAME_WIDTH / 2] = 1;
    // drawImage(GAME_WIDTH / 2, GAME_HEIGHT / 2, TILE_SIZE, TILE_SIZE, player_image_1);
    drawRectARGB32(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH / 2 + TILE_SIZE, GAME_HEIGHT / 2 + TILE_SIZE, 0xffffff,1);
}