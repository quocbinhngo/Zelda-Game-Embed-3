#ifndef FRAMEBF_H_
#define FRAMEBF_H_

void framebf_init(int physicalWidth, int physicalHeight, int virtualWidth, int virtualHeight);
void drawPixelARGB32(int x, int y, unsigned int attr);
void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill);
void drawImage(int x, int y, int w, int h, const unsigned long *image);
void drawCharacterImage(int x, int y, int w, int h, const unsigned long *image);
// void drawSubImage(int x, int y, int w, int h, const unsigned long *image);


void redrawBackground(int x, int y);
#endif