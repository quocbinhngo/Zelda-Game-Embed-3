#include "stage.h"
#include "../font/font.h"
#include "../uart.h"
#include "../image/tmp_resources.h"
#include "player.h"
#include "game_const.h"
#include "game_controller.h"
#include "../time.h"
#include "ui.h"

void update_menu_stage(stage *option)
{
    draw_button(100, "Start", 0);
    draw_button(300, "Settings", 0);
    draw_button(500, "Exit", 0);

    switch (*option)
    {
    case GAME:
    {
        uart_puts("menu");
        draw_button(100, "START", 1);
        break;
    }
    case SETTING:
    {
        uart_puts("setting");
        draw_button(300, "SETTING", 1);
        break;
    }
    case EXIT:
    {
        uart_puts("exit");
        draw_button(500, "EXIT", 1);
    }
    default:
    {
        uart_puts("default");
        break;
    }
    }
}

void menu_stage(stage *option, stage *main)
{

    update_menu_stage(option);
    int cont_loop = 1;

    stage choices[] = {GAME, SETTING, EXIT};
    int choice_index = 0;

    while (cont_loop)
    {
        char key = getUart();

        stage previous = *option;

        switch (key)
        {
        case 'w':
        {
            choice_index = (choice_index - 1 + 3) % 3;
            break;
        }
        case 's':
        {
            choice_index = (choice_index + 1) % 3;
            break;
        }
        case '\n':
        {
            *main = *option;
            cont_loop = 0;
            break;
        }
        default:
        {
            break;
        }
        }

        *option = choices[choice_index];
        if (*option != previous)
        {
            update_menu_stage(option);
        }
    }
}

void game_stage(stage *main)
{
    GameController game_controller_obj;
    GameController *game_controller = &game_controller_obj;

    DrawMap(game_controller);

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
        DrawScore(game_controller);
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
