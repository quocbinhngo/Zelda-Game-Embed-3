#ifndef FONT_H_
#define FONT_H_

#define FONT_WIDTH 1280
#define FONT_HEIGHT 720

#define SMALL_FONT 0
#define LARGE_FONT 1

void assignArray(unsigned int des[8], int fontIndex);

// function to count the how many pixel required by a character
int countSpaces(char character);

// function to draw the character on screen at pixel coordinate (x,y) with text color
void drawCharacterFont(int x, int y, char charater, unsigned int color);

// function to draw a string on screen at pixel coordinate (x,y) with text color
void stringFont(int x, int y, char *string, unsigned int color, int size);

// Font value for each character.

void stringFontLarge(int offsetX, int offsetY, char *string, unsigned int attr);

#endif