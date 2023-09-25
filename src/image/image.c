#include "image.h"
#include "../framebf.h"
#include "image_resources.h"
#include "../uart.h"
#include "../mbox.h"

int get_x_offset(int image_index)
{
    return image_index * IMAGE_WIDTH;
}

void image_mode()
{

    framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, IMAGE_WIDTH * (image_allArray_LEN), IMAGE_HEIGHT);
    int y_offset = 0, x_offset = 0, image_index = 0;
    display_image(image_allArray[0]);

    while (1)
    {
        char c = uart_getc();

        switch (c)
        {
        case 's':
        {
            y_offset = (SCREEN_HEIGHT + y_offset + 5 < IMAGE_HEIGHT) ? y_offset + 5 : y_offset;
            mbox_buffer_setup(ADDR(mBuf), MBOX_TAG_SETVIRTOFF, 2, x_offset, y_offset);
            break;
        }
        case 'w':
        {
            y_offset = (y_offset - 5 >= 0) ? y_offset - 5 : y_offset;
            mbox_buffer_setup(ADDR(mBuf), MBOX_TAG_SETVIRTOFF, 2, x_offset, y_offset);
            break;
        }
        case 'a':
        {
            image_index = (image_index - 1 + image_allArray_LEN) % image_allArray_LEN, y_offset = 0;
            drawImage(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, image_allArray[image_index]);
            mbox_buffer_setup(ADDR(mBuf), MBOX_TAG_SETVIRTOFF, 2, x_offset, y_offset);
            break;
        }
        case 'd':
        {
            image_index = (image_index + 1 + image_allArray_LEN) % image_allArray_LEN, y_offset = 0;
            drawImage(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, image_allArray[image_index]);
            mbox_buffer_setup(ADDR(mBuf), MBOX_TAG_SETVIRTOFF, 2, x_offset, y_offset);
            break;
        }
        default:
            break;
        }
    }
}

// void display_image(const unsigned long **image, int image_len)
// {
//     // drawImage(0, 0 , IMAGE_WIDTH, IMAGE_HEIGHT, image[0]);
//     // drawImage(9 * SCREEN_WIDTH / 10, 0, IMAGE_WIDTH , IMAGE_HEIGHT, image[1]);

//     for (int i = 0; i < image_len; i++)
//     {
//         drawImage(i * IMAGE_WIDTH, 0, IMAGE_WIDTH, IMAGE_HEIGHT, image[i]);

//         for (int j = 0; j < IMAGE_HEIGHT; j++)
//         {
//             drawPixelARGB32(i * IMAGE_WIDTH + 10, j, 0x00FF0000);
//         }
//     }
// }

void display_image(const unsigned long *image)
{
    drawImage(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, image);
}
