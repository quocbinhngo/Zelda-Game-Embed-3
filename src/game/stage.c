#include "stage.h"
#include "../font/font.h"
#include "../uart.h"
#include "../image/tmp_resources.h"
#include "player.h"
#include "game_const.h"
#include "game_controller.h"
#include "../time.h"
#include "ui.h"



void menu_stage(stage *option, stage *main)
{
    
    draw_button(100, "Start");
    draw_button(300, "Options");

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
     GameController game_controller_obj;
     GameController *game_controller = &game_controller_obj;

    StartGame(game_controller);


    int enemy_movement_timer = 0;
    int spawn_timer = 50;

    int index = 0;

    while (1)
    {

        char input = getUart();
        uart_sendc(input);
        uart_puts("\n");

        if (!game_controller->is_game_active && IsExitGameInput(input))
        {
            //
        }

        if (!game_controller->is_game_active)
        {
            continue;
        }

        if (spawn_timer == SPAWN_TIMER && index < NUM_EMEMIES)
        {

            InitEnemy(game_controller, 0);

            spawn_timer = 0;
            index++;
        }

        if (IsMoveInput(input))
        {
            MovePlayer(game_controller, input);
        }
        else if (IsAttackInput(input))
        {
            PlayerAttack(game_controller);
        }

        // MoveEnemy(game_controller, &game_controller->enemy_list.enemies[0]);
        MoveEnemies(game_controller);
        
        DrawHealthBar(game_controller);
        wait_msec(50000);
        spawn_timer++;
        
    }
}

// <<<<<<< HEAD

//         enemy_movement_timer++;

//         if(enemy_movement_timer == 10){
//             for(int i = 0; i < 10; i++){
//                 if(enemies[i].active == 1){
//                     MoveEnemy(game_controller,&enemies[i],&player);
//                 }
//             }
//             // MoveEnemy(game_controller, &enemies[0], &player);
//             // MoveEnemy(game_controller, &enemies[1], &player);
//             enemy_movement_timer = 0;
//         }

//         spawn_timer++;
// =======

//         wait_msec(50000);
// >>>>>>> e223fbe58205e9d34ddaeba41ca0db18ada116ff
//     }

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
