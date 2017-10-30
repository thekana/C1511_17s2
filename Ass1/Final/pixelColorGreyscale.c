// Assignment 1 Mandelbrot: Pixel Color
//
// Completed by
// Jasvir Boparoy (z5165068)
// Kanadech (King) (z5176970)
//
// Modified on 2017-09-14
// Tutor's name: Zain Afzal and Anna (frid10-Sitar) (F09A)

#include "mandelbrot.h"
#include "pixelColor.h"

// This function should take a number (of steps taken to escape the
// Mandelbrot set), and convert it to a color.
//
// You have artistic licence here, so make your Mandelbrot look amazing.
pixel pixelColor(int steps) {
    pixel color = {
        .red = 255 - steps,
        .green = 255 - steps,
        .blue = 255 - steps
    };

    return color;
}
