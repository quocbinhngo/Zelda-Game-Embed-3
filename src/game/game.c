#include "stage.h"
#include "../font/font.h"
#include "../image/image.h"
#include "../time.h"
#include "game_const.h"
#include "../uart.h"
#include "game.h"

// #define VIR_GAME_WIDTH 1280
// #define VIR_GAME_HEIGHT 720

// #define PHY_GAME_WIDTH 300
// #define PHY_GAME_HEIGHT 300

void game_mode()
{

    framebf_init(GAME_WIDTH, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT);

    stage cur_stage = MENU;
    stage option = GAME;

    int cont_loop = 1;
    int map_state = GRASS_MAP;
    int diff = 0, map = 0;

    while (cont_loop)
    {
        switch (cur_stage)
        {
        case MENU:
        {
            // uart_puts("fdsfsd\n");
            menu_stage(&option, &cur_stage, &diff, &map);
            break;
        }
        case SETTING:
        {
            setting_stage(&option, &cur_stage, &map);
            break;
        }
        case DIFF:
        {
            diff_stage(&option, &cur_stage, &diff, &map);
            break;
        }
        case MAP:
        {
            map_stage(&option, &cur_stage, &map);
            cur_stage = MENU;
            break;
        }
        case GAME:
        {
            game_stage(&cur_stage, &diff, &map);
            break;
        }
        case EXIT:
        {
            cont_loop = 0;
            break;
        }
        default:
        {
            break;
        }
        }
    }
}
