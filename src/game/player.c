#include "../framebf.h"
#include "game.h"
#include "resources/player.h"
#include "player.h"

void init_player()
{
    // draw player character
    //   drawRectARGB32(50,50,100,100, 0x00000000, 1);

    drawImage(PHY_GAME_WIDTH / 2, PHY_GAME_HEIGHT / 2, PLAYER_SIZE, PLAYER_SIZE, player_image_1);
}