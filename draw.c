#include "draw.h"

void draw(ALLEGRO_BITMAP *bitmap, int width, int height, double x, double y, double step)
{
    ALLEGRO_LOCKED_REGION *region = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
    unsigned *pPixelBuffer = (unsigned*) region -> data;
    pPixelBuffer += width;
    pPixelBuffer -= width * height;
    mandelbrot(pPixelBuffer, width, height, x, y, step);
    al_unlock_bitmap(bitmap);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(bitmap, 0, 0, 0);
    al_flip_display();
}