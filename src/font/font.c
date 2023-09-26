#include "font.h"
#include "../framebf.h"
#include "small_font_resources.h"
#include "large_lowercase_font_resources.h"
#include "large_uppercase_font_resources.h"
#include "large_number_font_resources.h"
#include "large_symbol_font_resources.h"

void drawChar_lower(int offsetX, int offsetY, unsigned int attr, int charIndex)
{
    int width = alphabet_lowercase_width[charIndex];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            if (alphabet_lowercase[charIndex][y * width + x] == 1)
            {
                drawPixelARGB32(x + offsetX, y + offsetY, attr);
            }
        }
    }
}
void drawChar_upper(int offsetX, int offsetY, unsigned int attr, int charIndex)
{
    int width = alphabet_uppercase_width[charIndex];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            if (alphabet_uppercase[charIndex][y * width + x] == 1)
            {
                drawPixelARGB32(x + offsetX, y + offsetY, attr);
            }
        }
    }
}
void drawChar_number(int offsetX, int offsetY, unsigned int attr, int charIndex)
{
    int width = number_img_width[charIndex];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            if (number_img[charIndex][y * width + x] == 1)
            {
                drawPixelARGB32(x + offsetX, y + offsetY, attr);
            }
        }
    }
}
void drawChar_symbol33_47(int offsetX, int offsetY, unsigned int attr, int charIndex)
{
    int width = symbol_img_width33_47[charIndex];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            if (symbol_img33_47[charIndex][y * width + x] == 1)
            {
                drawPixelARGB32(x + offsetX, y + offsetY, attr);
            }
        }
    }
}
void drawChar_symbol58_64(int offsetX, int offsetY, unsigned int attr, int charIndex)
{
    int width = symbol_img_width58_64[charIndex];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            if (symbol_img58_64[charIndex][y * width + x] == 1)
            {
                drawPixelARGB32(x + offsetX, y + offsetY, attr);
            }
        }
    }
}
void drawChar_symbol91_96(int offsetX, int offsetY, unsigned int attr, int charIndex)
{
    int width = symbol_img_width91_96[charIndex];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            if (symbol_img91_96[charIndex][y * width + x] == 1)
            {
                drawPixelARGB32(x + offsetX, y + offsetY, attr);
            }
        }
    }
}
void drawChar_symbol123_126(int offsetX, int offsetY, unsigned int attr, int charIndex)
{
    int width = symbol_img_width123_126[charIndex];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            if (symbol_img123_126[charIndex][y * width + x] == 1)
            {
                drawPixelARGB32(x + offsetX, y + offsetY, attr);
            }
        }
    }
}
void draw_num(int num, int offsetX, int offsetY, int erase)
{
    // 31x32
    if (num > 0 && num < 6)
    {
        int offset = (num - 1) * 31;
        for (int x = offset; x < offset + 31; x++)
        {
            for (int y = 0; y < 32; y++)
            {
                if (one2five[y * 155 + x] > 0)
                {
                    drawPixelARGB32(x - offset + offsetX, y + offsetY, 0x00FFFFFF);

                    // if (erase)
                    //     drawPixelARGB32(x - offset + offsetX, y + offsetY, background_img[(int)(y + offsetY) * 1024 + (int)(x - offset + offsetX)]);
                    // else
                    //     drawPixelARGB32(x - offset + offsetX, y + offsetY, 0x00FFFFFF);
                }
            }
        }
    }
    else
    {
        int offset = 4 * 31;
        if (num != 0)
            offset = (num - 6) * 31;
        for (int x = offset; x < offset + 31; x++)
        {
            for (int y = 0; y < 32; y++)
            {
                if (six2zero[y * 155 + x] > 0xc0)
                {

                    drawPixelARGB32(x - offset + offsetX, y + offsetY, 0x00FFFFFF);
                    // if (erase)
                    //     drawPixelARGB32(x - offset + offsetX, y + offsetY, background_img[(int)(y + offsetY) * 1024 + (int)(x - offset + offsetX)]);
                    // else
                    // drawPixelARGB32(x - offset + offsetX, y + offsetY, 0x00FFFFFF);
                }
            }
        }
    }
}

void draw_nums(int num, int offsetX, int offsetY, int erase)
{
    if (num == 0)
    {
        draw_num(0, offsetX, offsetY, erase);
        return;
    }
    int c = 0; /* digit position */
    int n = num;
    while (n != 0)
    {
        n /= 10;
        c++;
    }
    c -= 1;
    n = num;
    /* extract each digit */
    while (c >= 0)
    {
        int cur_num = n % 10;
        draw_num(cur_num, offsetX + (31 * c), offsetY, erase);
        n /= 10;
        c--;
    }
}

// function to assign font value to an array
void assignArray(unsigned int *des, int fontIndex)
{
    for (int i = fontIndex; i < fontIndex + 8; i++)
    {
        *des = convertedFont[i];
        des += 1;
    }
}

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
void drawCharacterFont(int x, int y, char character, unsigned int color)
{
    unsigned int a[8];
    int charIndex = character - 33;

    assignArray(&a[0], charIndex * 8);

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
void stringFont(int x, int y, char *string, unsigned int color, int size)
{
    if (size == SMALL_FONT)
    {

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

        return;
    }

    // framebf_init(FONT_WIDTH, FONT_HEIGHT, FONT_WIDTH, FONT_HEIGHT);
    stringFontLarge(x, y, string, color);
}

void stringFontLarge(int offsetX, int offsetY, char *string, unsigned int attr)
{
    int offsetWidth = offsetX;
    while (*string != '\0')
    {
        if (*string >= 'a' && *string <= 'z')
        {
            drawChar_lower(offsetWidth, offsetY, attr, *string - 'a');
            offsetWidth += alphabet_lowercase_width[*string - 'a'] + 7;
        }
        else if (*string >= 'A' && *string <= 'Z')
        {
            drawChar_upper(offsetWidth, offsetY, attr, *string - 'A');
            offsetWidth += alphabet_uppercase_width[*string - 'A'] + 7;
        }
        else if (*string >= '0' && *string <= '9')
        {
            drawChar_number(offsetWidth, offsetY, attr, *string - '0');
            offsetWidth += number_img_width[*string - '0'] + 7;
        }
        else if (*string >= 33 && *string <= 47)
        {
            drawChar_symbol33_47(offsetWidth, offsetY, attr, *string - 33);
            offsetWidth += symbol_img_width33_47[*string - 33] + 7;
        }
        else if (*string >= 58 && *string <= 64)
        {
            drawChar_symbol58_64(offsetWidth, offsetY, attr, *string - 58);
            offsetWidth += symbol_img_width58_64[*string - 58] + 7;
        }
        else if (*string >= 91 && *string <= 96)
        {
            drawChar_symbol91_96(offsetWidth, offsetY, attr, *string - 91);
            offsetWidth += symbol_img_width91_96[*string - 91] + 7;
        }
        else if (*string >= 123 && *string <= 126)
        {
            drawChar_symbol123_126(offsetWidth, offsetY, attr, *string - 123);
            offsetWidth += symbol_img_width123_126[*string - 123] + 7;
        }
        else if (*string == ' ')
        {
            offsetWidth += 7 * 3;
        }
        string++;
    }
}

void font_mode()
{
    framebf_init(FONT_WIDTH, FONT_HEIGHT, FONT_WIDTH, FONT_HEIGHT);
    stringFont(200, 100, "Nguyen The Bao Ngoc", 0x00AA0000, SMALL_FONT);
    stringFont(200, 120, "Vo Duc Tan", 0x00BB00, SMALL_FONT);
    stringFont(200, 140, "Doan Tran Thien Phuc", 0x0000CC, SMALL_FONT);
    stringFont(200, 160, "Ngo Quoc Binh", 0xAABB00, SMALL_FONT);
    stringFont(200, 180, "0123456789", 0x00BBCC, SMALL_FONT);
    stringFont(200, 200, "!@#$%^&*()", 0xAA00CC, SMALL_FONT);

}