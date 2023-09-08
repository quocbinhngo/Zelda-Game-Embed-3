#include "image.h"
#include "../framebf.h"

void display_image(const unsigned long *image) {
    framebf_init(IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);
    drawImage(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, image);
}
