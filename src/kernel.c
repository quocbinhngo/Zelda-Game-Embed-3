#include "uart.h"
#include "mbox.h"
#include "framebf.h"
#include "image/image.h"
#include "font/font.h"


void main()
{
    // set up serial console
    uart_init();
    // say hello
    uart_puts("\n\nHello World!\n");
    // Initialize frame buffer

    // image_mode();
    stringFont(0, 0, "Double2T", 0x2224ab);


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
