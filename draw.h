#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include "allegro5/allegro.h"

void mandelbrot(unsigned* pPixelBuffer, int width, int height, double x, double y, double step);
void draw(ALLEGRO_BITMAP *bitmap, int width, int height, double x, double y, double step);

#endif
