#include "ui.h"
#include "../framebf.h"
#include "../font/font.h"
#include "../uart.h"

void draw_button(int offsetY, char *string, int is_primary)
{
    int offsetX = (1280 - BUTTON_WIDTH) / 2;
    uart_dec(BUTTON_WIDTH);
    uart_dec(offsetX);

    int text_color,
        background_color;
    if (is_primary)
    {
        text_color = BUTTON_SECONDARY_COLOR, background_color = BUTTON_PRIMARY_COLOR;
    }
    else
    {
        text_color = BUTTON_PRIMARY_COLOR, background_color = BUTTON_SECONDARY_COLOR;
    }

    drawRectARGB32(offsetX, offsetY, offsetX + BUTTON_WIDTH, offsetY + BUTTON_HEIGHT, background_color, 1);

    stringFont(offsetX + BUTTON_PADDING_X, offsetY + BUTTON_PADDING_Y, string, text_color, LARGE_FONT);
    // drawRectARGB32(100, 200, 200, 500, )
}