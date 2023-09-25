#ifndef _UI_H
#define _UI_H

#define BUTTON_START_ID 0
#define BUTTON_WIDTH 400
#define BUTTON_HEIGHT 100
#define BUTTON_PRIMARY_COLOR 0x301E83
#define BUTTON_SECONDARY_COLOR 0x00F5E300
#define BUTTON_PADDING_X 50
#define BUTTON_PADDING_Y 20

void draw_button(int offsetY, char *string, int is_primary);

#endif