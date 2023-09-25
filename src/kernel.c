#include "uart.h"
#include "mbox.h"
#include "framebf.h"
#include "image/image.h"
#include "video/video.h"
#include "font/font.h"
#include "game/game.h"

void main()
{
    // set up serial console
    uart_init();
    // say hello
    // Initialize frame buffer

    // image_mode();
    // stringFont(0, 0, "Tran Duc Linh", 0xafbec1);

    //game_mode();

    // image_mode();
    video_mode();

    // framebf_init(500, 500, 600, 600);
    // drawRectARGB32(0, 0, 499, 499, 0x00AABBCC, 1);
    // drawRectARGB32(600, 0, 600 + 499, 499, 0x00FF0000, 1);

    // int x_offset = 0;

    // while (1)
    // {
    //     char c = getUart();
    //     if (c == 'd')
    //     {
    //         x_offset = x_offset + 5;
    //         mbox_buffer_setup(ADDR(mBuf), MBOX_TAG_SETVIRTOFF, 2, x_offset, 0);
    //         break;
    //     }
    // }
    // drawRectARGB32(0, 0, 499, 499, 0x00FF0000, 1);

    // display_image(image_allArray[0]);

    // // echo everything back
    // while (1)
    // {
    //     // read each char
    //     char c = uart_getc();
    //     // send back
    //     uart_sendc(c);
    // }
}
