#include "stage.h"
#include "../font/font.h"
#include "../uart.h"
#include "game.h"
#include "../image/tmp_resources.h"
#include "player.h"
#include "../framebf.h"
#include "../mbox.h"

void menu_stage(stage *option, stage *main)
{

    // draw background
    drawImage(0, 0, PHY_GAME_WIDTH, PHY_GAME_HEIGHT, temp_imageallArray[0]);

    stringFont(200, 200, "Hello", 0x00FF00000);
    stringFont(200, 400, "Click space to start", 0x00ffffff);

    while (1)
    {
        char key = getUart();

        if (key == ' ')
        {
            *main = *option;
            return;
        }
    }
}

void game_stage(stage *main)
{
    // Draw map
    drawImage(0, 0, PHY_GAME_WIDTH, PHY_GAME_HEIGHT, temp_imageallArray[0]);

    uart_puts("Game stage");

    // Init the player
    init_player();
    int offset_x = 0, offset_y = 0;
    int player_x = PHY_GAME_WIDTH / 2, player_y = PHY_GAME_HEIGHT / 2;

    while (1)
    {
        char input = uart_getc();

        uart_sendc(input);

        switch (input)
        {
        case 'a':
        {
            offset_x = (offset_x - PLAYER_SPEED >= 0) ? offset_x - PLAYER_SPEED : 0;
            break;
        }
        case 'd':
        {
            offset_x = (offset_x + PLAYER_SPEED < VIR_GAME_WIDTH) ? offset_x + PLAYER_SPEED : VIR_GAME_WIDTH;
            break;
        }
        case 'w':
        {
            offset_y = (offset_y - PLAYER_SPEED >= 0) ? offset_y - PLAYER_SPEED : 0;
            break;
        }
        case 's':
        {
            offset_y = (offset_y + PLAYER_SPEED < VIR_GAME_HEIGHT) ? offset_y + PLAYER_SPEED : VIR_GAME_HEIGHT;
            break;
        }
        default:
        {
            break;
        }
        }

        unsigned int **res_data;
        mbox_buffer_setup(mBuf, MBOX_TAG_SETVIRTOFF, res_data, 0, 2, offset_x, offset_y);
    }
}