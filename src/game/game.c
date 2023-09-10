#include "stage.h"
#include "../font/font.h"
#include "../image/image.h"
#include "../time.h"
#include "game.h"


// #define VIR_GAME_WIDTH 1280
// #define VIR_GAME_HEIGHT 720

// #define PHY_GAME_WIDTH 300
// #define PHY_GAME_HEIGHT 300

void game_mode()
{

    framebf_init(PHY_GAME_WIDTH, PHY_GAME_HEIGHT, VIR_GAME_WIDTH , VIR_GAME_HEIGHT);

    stage cur_stage = MENU;
    stage option = GAME;

    // wait_msec(2000000);

    while (1)
    {

        switch (cur_stage)
        {
        case MENU:
        {
            // uart_puts("fdsfsd\n");
            menu_stage(&option, &cur_stage);
            break;
        }
        case GAME:
        {
            game_stage(&cur_stage);
            break;
        }
        }
    }
}