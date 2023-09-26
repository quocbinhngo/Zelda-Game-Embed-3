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

void update_pause_stage(int choice_index)
{
    draw_button(200, "Continue", 0);
    draw_button(350, "Exit game", 0);

    switch (choice_index)
    {
    case 0:
    {
        draw_button(200, "Continue", 1);
        break;
    }
    case 1:
    {
        draw_button(350, "Exit game", 1);
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

    stage choices[] = {DIFF, MAP, MENU};
    int choice_index = 0;
    *option = DIFF;

    update_setting_stage(option);

    stringFont(450, 40, "Setting screen", PRIMARY_COLOR, LARGE_FONT);

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
        case 'j':
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
    DrawMap(*map);

    stringFont(275, 40, "Menu Screen, Level: ", PRIMARY_COLOR, LARGE_FONT);

    switch (*diff)
    {
    case 0:
    {
        stringFont(888, 40, "Easy", PRIMARY_COLOR, LARGE_FONT);
        break;
    }
    case 1:
    {
        stringFont(888, 40, "Medium", PRIMARY_COLOR, LARGE_FONT);

        break;
    }
    case 2:
    {
        stringFont(888, 40, "Hard", PRIMARY_COLOR, LARGE_FONT);
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
        case 'j':
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

    stringFont(350, 40, "Choose a game map: ", PRIMARY_COLOR, LARGE_FONT);
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
        case 'j':
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

    stringFont(350, 40, "Choose a difficulty: ", PRIMARY_COLOR, LARGE_FONT);
    update_diff_stage(diff);

    stringFont(250, 40, "Choose a difficulty level", PRIMARY_COLOR, LARGE_FONT);

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
        case 'j':
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

void game_stage(stage *main, GameController *game_controller, int *diff, int *map, int *start_game)
{
    game_controller->diff = *diff;

    DrawMap(*map);

    if (*start_game)
    {
        StartGame(game_controller, map);
        *start_game = 0;
    }
    else
    {
        ResumeGame(game_controller, map);
    }

    int spawn_timer = 0;
    int enemy_cnt = 0;
    game_controller->cancel_attack_timer = 0;

    while (1)
    {
        char input = getUart();

        if (!game_controller->is_game_active)
        {
            break;
        }

        if (IsPauseInput(input))
        {
            *main = PAUSE;
            return;
        }

        if (spawn_timer == (SPAWN_TIMER / (*diff + 1)) && enemy_cnt < NUM_EMEMIES)
        // if (spawn_timer == (SPAWN_TIMER / (*diff + 1)) && index < NUM_EMEMIES)
        {
            InitEnemy(game_controller, 0, *diff + 1);
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

        uart_puts("Cancel attack: ");
        uart_dec(game_controller->cancel_attack_timer);
        uart_puts("\n");
        
        if (game_controller->cancel_attack_timer == CANCEL_ATTACK_TIMER)
        {
            game_controller->cancel_attack_timer = 0;
            CancelAttack(game_controller);
        }
        else if (game_controller->cancel_attack_timer)
        {
            game_controller->cancel_attack_timer++;
        }

        if (IsMoveInput(input))
        {
            MovePlayer(game_controller, input);
        }
        else if (IsAttackInput(input))
        {
            PlayerAttack(game_controller);
        }
        else if (IsWeaponInput(input))
        {
            ChangeWeapon(game_controller);
        }

        // MoveEnemy(game_controller, &game_controller->enemy_list.enemies[0]);
        MoveEnemies(game_controller);
        CancelEnemyAttack(game_controller);

        DrawHealthBar(game_controller);
        DrawScore(game_controller);

        wait_msec(50000);
        spawn_timer++;
    }

    uart_puts("outside");

    DrawMap(*map);
    DrawGameOver(game_controller);

    while (1)
    {

        char input = getUart();

        if (input == 'j')
        {
            *main = MENU;
            *start_game = 1;
            break;
        }
    }
}

// <<<<<<< HEAD

//         enemy_movement_timer++;

//         if(enemy_movement_timer == 10){
//             for(int i = 0; i < 10; i++){
//                 if(enemies[i].active == 1){
//                     MoveEnemy(game_controller,&enemies[i],&player);
//
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

void pause_stage(stage *main, int *map, int *start_game)
{
    DrawMap(*map);
    stringFont(500, 40, "PAUSE GAME", PRIMARY_COLOR, LARGE_FONT);

    int cont_loop = 1;

    stage choices[] = {GAME, MENU};
    int choice_index = 0;

    update_pause_stage(choice_index);

    while (cont_loop)
    {
        char key = getUart();

        int previous = choice_index;

        switch (key)
        {
        case 'w':
        {
            choice_index = (choice_index - 1 + 2) % 2;
            break;
        }
        case 's':
        {
            choice_index = (choice_index + 1) % 2;
            break;
        }
        case 'j':
        {
            *main = choices[choice_index];
            cont_loop = 0;
            break;
        }
        default:
        {
            break;
        }
        }

        if (choice_index != previous)
        {
            update_pause_stage(choice_index);
        }
    }

    switch (*main)
    {
    case GAME:
    {
        *start_game = 0;
        break;
    }
    case MENU:
    {
        *start_game = 1;
        break;
    }
    default:
    {
        break;
    }
    }

    DrawMap(*map);
}
