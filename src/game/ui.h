#ifndef _UI_H
#define _UI_H

#define BUTTON_START_ID 0
#define BUTTON_WIDTH 800
#define BUTTON_HEIGHT 100
#define PRIMARY_COLOR 0x00000000
#define SECONDARY_COLOR  0x00FFFFFF
#define TERTINARY_COLOR_1 0x000A360A
#define BUTTON_PADDING_X 50
#define BUTTON_PADDING_Y 20

void draw_button(int offsetY, char *string, int is_primary);

#endif