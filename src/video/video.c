#include "video.h"
#include "../framebf.h"
#include "video_resources.h"
#include "../uart.h"
#include "../mbox.h"
#include "../time.h"

void video_mode()
{
    framebf_init(VID_SCREEN_WIDTH, VID_SCREEN_HEIGHT, VID_WIDTH, VID_HEIGHT);
    display_video(0, 0, VID_WIDTH, VID_HEIGHT, 45, epd_bitmap_allArray);
}

void display_video(int x, int y, int w, int h, int num_frames, const unsigned long **video)
{
    for (int i = 0; i < VIDEO_LOOP; i++)
    {
        for (int frame = 0; frame < num_frames; frame++)
        {
            drawImage(x, y, w, h, video[frame]);
            wait_msec(100);
        }
    }
}