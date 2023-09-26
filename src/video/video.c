#include "video.h"
#include "../framebf.h"
#include "video_resources.h"
#include "../uart.h"
#include "../mbox.h"

void video_mode(){
    framebf_init(SCREEN_WIDTH, SCREEN_HEIGHT, VID_WIDTH, VID_HEIGHT);
    while(1){
        display_video(0, 0, VID_WIDTH, VID_HEIGHT, 45, epd_bitmap_allArray);
    }
    
}

void display_video(int x, int y, int w, int h, int num_frames, const unsigned long **video)
{
    for (int frame = 0; frame < num_frames; frame++)
    {
       drawImage(x, y, w, h, video[frame]);
       wait_msec(50);
    }
}