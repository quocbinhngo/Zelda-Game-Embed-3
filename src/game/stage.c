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
    draw_button(200, "Start", 0);
    draw_button(350, "Settings", 0);
    draw_button(500, "Exit", 0);

    switch (*option)
    {
    case GAME:
    {
        draw_button(200, "Start", 1);
        break;
    }
    case SETTING:
    {
        draw_button(350, "Settings", 1);
        break;
    }
    case EXIT:
    {
        draw_button(500, "Exit", 1);
    }
    default:
    {
        break;
    }
    }
}

void update_diff_stage(int *diff)
{
    draw_button(200, "Easy", 0);
    draw_button(350, "Medium", 0);
    draw_button(500, "Hard", 0);

    switch (*diff)
    {
    case 0:
    {
        draw_button(200, "Easy", 1);
        break;
    }
    case 1:
    {
        draw_button(350, "Medium", 1);
        break;
    }
    case 2:
    {
        draw_button(500, "Hard", 1);
        break;
    }
    default:
    {
        break;
    }
    }
}

void update_setting_stage(stage *option)
{
    draw_button(200, "Difficulty", 0);
    draw_button(350, "Map background", 0);
    draw_button(500, "Home", 0);

    switch (*option)
    {
    case DIFF:
    {
        draw_button(200, "Difficulty", 1);
        break;
    }
    case MAP:
    {
        draw_button(350, "Map background", 1);
        break;
    }
    case MENU:
    {
        draw_button(500, "Home", 1);
        break;
    }
    default:
    {
        break;
    }
    }
}

void update_map_stage(stage *option)
{
    draw_button(200, "Grass", 0);
    draw_button(350, "Desert", 0);
    draw_button(500, "Dungeon", 0);

    switch (*option)
    {
    case 0:
    {
        draw_button(200, "Grass", 1);
        break;
    }
    case 1:
    {
        draw_button(350, "Desert", 1);
        break;
    }
    case 2:
    {
        draw_button(500, "Dungeon", 1);
        break;
    }
    default:
    {
        break;
    }
    }
}

void setting_stage(stage *option, stage *main, int *map)
{
    DrawMap(*map);
    int cont_loop = 1;
    
    stringFont(500, 40, "Settings: ", BUTTON_PRIMARY_COLOR, LARGE_FONT);

    stage choices[] = {DIFF, MAP, MENU};
    int choice_index = 0;
    *option = DIFF;

    update_setting_stage(option);

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

        if (cont_loop)
        {
            *option = choices[choice_index];
            if (*option != previous)
            {
                update_setting_stage(option);
            }
        }
    }

    DrawMap(*map);
}

void menu_stage(stage *option, stage *main, int *diff, int *map)
{
    char *levelStr;
    DrawMap(*map);

    stringFont(500, 40, "Level: ", BUTTON_PRIMARY_COLOR, LARGE_FONT);

    switch (*diff)
    {
    case 0:
    {
        stringFont(700, 40, "Easy", BUTTON_PRIMARY_COLOR, LARGE_FONT);
        break;
    }
    case 1:
    {
        stringFont(700, 40, "Medium", BUTTON_PRIMARY_COLOR, LARGE_FONT);
        break;
    }
    case 2:
    {
        stringFont(700, 40, "Hard", BUTTON_PRIMARY_COLOR, LARGE_FONT);
        break;
    }
    default:
    {
        break;
    }
    }

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

    DrawMap(*map);
}

void map_stage(stage *option, stage *main, int *map)
{
    DrawMap(*map);
    update_map_stage(option);
    int cont_loop = 1;

    stringFont(350, 40, "Choose a game map: ", BUTTON_PRIMARY_COLOR, LARGE_FONT);
    stage choices[] = {0, 1, 2};
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
            *map = *option;
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
            update_map_stage(option);
        }
    }

    DrawMap(*map);
}

void diff_stage(stage *option, stage *main, int *diff, int *map)
{
    DrawMap(*map);

    stringFont(350, 40, "Choose a difficulty: ", BUTTON_PRIMARY_COLOR, LARGE_FONT);
    update_diff_stage(diff);

    int cont_loop = 1;

    update_diff_stage(diff);

    while (cont_loop)
    {
        char key = getUart();

        int previous = *diff;

        switch (key)
        {
        case 'w':
        {
            *diff = (*diff - 1 + 3) % 3;
            break;
        }
        case 's':
        {
            *diff = (*diff + 1) % 3;
            break;
        }
        case '\n':
        {
            cont_loop = 0;
            *main = MENU;
            break;
        }
        default:
        {
            break;
        }
        }

        if (*diff != previous)
        {
            update_diff_stage(diff);
        }
    }

    DrawMap(*map);
}

void game_stage(stage *main, int *diff, int *map)
{
    GameController game_controller_obj;
    game_controller_obj.diff = *diff;
    GameController *game_controller = &game_controller_obj;

    DrawMap(*map);
    StartGame(game_controller, *map);

    int enemy_movement_timer = 0;
    int spawn_timer = 0;
    int enemy_cnt = 0;

    while (1)
    {

        char input = getUart();

        if (!game_controller->is_game_active && IsExitGameInput(input))
        {
        }

        if (!game_controller->is_game_active)
        {
            continue;
        }

        if (spawn_timer == (SPAWN_TIMER / (*diff + 1)) && enemy_cnt < NUM_EMEMIES)
        // if (spawn_timer == (SPAWN_TIMER / (*diff + 1)) && index < NUM_EMEMIES)
        {

            InitEnemy(game_controller, 0);
            spawn_timer = 0;
            enemy_cnt++;

            // if (game_controller->diff > 0)
            // {
            //     uart_puts("init 2nd enemy\n");
            //     InitEnemy(game_controller, 1);
            //     enemy_cnt++;
            // }

            // if (game_controller->diff > 1)
            // {
            //     InitEnemy(game_controller, 2);
            //     InitEnemy(game_controller, 3);
            //     enemy_cnt += 2;
            // }
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
