#include "uart.h"
#include "mbox.h"
#include "framebf.h"
#include "image/image.h"
#include "video/video.h"
#include "font/font.h"
#include "game/game.h"

#define feature 2

void main()
{
    // set up serial console
    uart_init();
    #if feature == 1
        image_mode();
    #elif feature == 2
        video_mode();
    #elif feature == 3
        
    #elif feature == 4
        game_mode();
    #endif
}
