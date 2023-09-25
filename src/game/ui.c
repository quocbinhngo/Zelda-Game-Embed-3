#include "ui.h"
#include "../framebf.h"
#include "../font/font.h"

void draw_button(int offsetY, char *string)
{
    int offsetX = (1280 - BUTTON_WIDTH) / 2;

    drawRectARGB32(offsetX, offsetY, offsetX + BUTTON_WIDTH, offsetY + BUTTON_HEIGHT, BUTTON_SECONDARY_COLOR, 1);

    stringFont(offsetX + BUTTON_PADDING_X, offsetY + BUTTON_PADDING_Y, string, BUTTON_PRIMARY_COLOR, LARGE_FONT);
    // drawRectARGB32(100, 200, 200, 500, )
}