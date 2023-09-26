#ifndef _VIDEO_H
#define _VIDEO_H

#define VID_HEIGHT 240
#define VID_WIDTH 320
#define VID_SCREEN_WIDTH 320
#define VID_SCREEN_HEIGHT 240
#define NUM_FRAMES 45

void video_mode();
void display_video(int x, int y, int w, int h, int num_frames, const unsigned long **video);

#endif