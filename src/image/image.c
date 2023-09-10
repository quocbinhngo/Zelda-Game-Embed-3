#include "image.h"
#include "../framebf.h"
#include "image_resources.h"
#include "../uart.h"

void image_mode()
{
    framebf_init(300, 300, IMAGE_WIDTH, IMAGE_HEIGHT);
    display_image(image_allArray[0]);
    int y_offset = 0;

    while (1)
    {
        char c = uart_getc();

        if (c == 'w')
        {
            y_offset += 5;
            framebf_init(400, 400, IMAGE_WIDTH, IMAGE_HEIGHT);

            drawImage(0, y_offset, IMAGE_WIDTH, IMAGE_HEIGHT, image_allArray[0]);
        }
    }
}

void display_image(const unsigned long *image)
{
    drawImage(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, image);
}
