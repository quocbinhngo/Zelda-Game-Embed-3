#include "font.h"
#include "../framebf.h"

// function to count the how many pixel required by a character
int countSpaces(char character)
{
    int fontIndex = (character - 33) * 8;
    for (int i = 0; i < 8; i++)
    {
        for (int index = fontIndex; index < fontIndex + 8; index++)
        {
            char val = convertedFont[index];
            if (((val & (0b1 << i)) >> i) == 0b1)
            {
                return 8 - i;
            }
        }
    }
    return 0;
}

// function to draw the character on screen at pixel coordinate (x,y) with text color
void drawCharacterFont(int x, int y, char charater, unsigned int color)
{
    unsigned int a[8];
    int charIndex = charater - 33;

    assignArray(&a, charIndex * 8);

    int xa = 0;

    for (int y_offset = y; y_offset < y + 8; y_offset++)
    {
        unsigned int test = a[xa];

        int i = 0;
        for (int x_offset = x + 7; x_offset >= x; x_offset--)
        {

            if (((test & (0b1 << i)) >> i) == 0b1)
            {
                drawPixelARGB32(x_offset, y_offset, color);
            }
            i++;
        }
        xa += 1;
    }
}

// function to draw a string on screen at pixel coordinate (x,y) with text color
void stringFont(int x, int y, char *string, unsigned int color)
{

    framebf_init(FONT_WIDTH, FONT_HEIGHT, FONT_WIDTH, FONT_HEIGHT);
    int x1 = x;

    while (*string != '\0')
    {

        if (*string == ' ')
        {
            x1 += 8;
        }
        else
        {
            drawCharacterFont(x1, y, *string, color);
            x1 += countSpaces(*string) + 1;
        }
        string++;
    }
}