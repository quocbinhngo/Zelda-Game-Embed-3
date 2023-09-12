#include "stage.h"
#include "../font/font.h"
#include "../image/image.h"
#include "../time.h"
#include "game_const.h"
#include "../uart.h"

// #define VIR_GAME_WIDTH 1280
// #define VIR_GAME_HEIGHT 720

// #define PHY_GAME_WIDTH 300
// #define PHY_GAME_HEIGHT 300

void game_mode()
{

    framebf_init(GAME_WIDTH, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT);

    stage cur_stage = GAME;
    stage option = GAME;

    while (1)
    {
        uart_puts("Hello world\n");

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
            uart_puts("Game stage 1\n");
            game_stage(&cur_stage);
            uart_puts("Finish game stasge\n");

            break;
        }
        }
    }
}
