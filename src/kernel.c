#include "uart.h"
#include "mbox.h"
#include "framebf.h"
#include "image/image.h"
#include "video/video.h"
#include "font/font.h"
#include "game/game.h"

#define IMAGE_MODE 1
#define VIDEO_MODE 2
#define FONT_MODE 3
#define GAME_MODE 4
#define feature GAME_MODE

void main()
{
    // set up serial console
    uart_init();
#if feature == IMAGE_MODE
    image_mode();
#elif feature == VIDEO_MODE
    video_mode();
#elif feature == FONT_MODE
    font_mode();
#elif feature == GAME_MODE
    game_mode();
#endif
}
