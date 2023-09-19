#include "stage.h"
#include "../font/font.h"
#include "../uart.h"
#include "../image/tmp_resources.h"
#include "player.h"
#include "game_const.h"
#include "game_controller.h"
#include "../time.h"

void menu_stage(stage *option, stage *main)
{

    // draw background
    drawImage(0, 0, GAME_WIDTH, GAME_HEIGHT, temp_imageallArray[0]);

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
    // drawImage(0, 0, PHY_GAME_WIDTH, PHY_GAME_HEIGHT, temp_imageallArray[0]);

    GameController *game_controller;

    ClearGameMap(game_controller);

    InitPlayer(game_controller);
    //InitEnemy(game_controller, &enemy);


    // uart_hex(&player);
    // uart_puts("\n");
    // uart_hex(&enemy);
    int enemy_movement_timer = 0;
    int spawn_timer = 50;
    
    int index = 0;
 
    
    while (1)
    {


        char input = getUart();
        uart_sendc(input);
        uart_puts("\n");

        if (IsMoveInput(input))
        {
            MovePlayer(game_controller, input);
        }

        else if (IsAttackInput(input))
        {
            PlayerAttack(game_controller);
        }
        wait_msec(50000);
        //MoveEnemy(game_controller, &enemy, &player);

    }

    // int offset_x = 0, offset_y = 0;
    // int player_x = PHY_GAME_WIDTH / 2, player_y = PHY_GAME_HEIGHT / 2;

    // while (1)
    // {
    //     char input = uart_getc();

    //     uart_sendc(input);

    //     switch (input)
    //     {
    //     case 'a':
    //     {
    //         break;
    //     }
    //     case 'd':
    //     {
    //         break;
    //     }
    //     case 'w':
    //     {
    //         break;
    //     }
    //     case 's':
    //     {
    //         break;
    //     }
    //     default:
    //     {
    //         break;
    //     }
    //     }

    //     unsigned int **res_data;
    //     mbox_buffer_setup(mBuf, MBOX_TAG_SETVIRTOFF, res_data, 0, 2, offset_x, offset_y);
    // }
}