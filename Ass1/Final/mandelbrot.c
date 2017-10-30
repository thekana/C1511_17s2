// Assignment 1 Mandelbrot
//
// Completed by
// Jasvir Boparoy (z5165068)
// Kanadech (King) (z5176970)
//
// Modified on 2017-09-05 - 2017-09-14
// Tutor's name: Zain Afzal and Anna Zhang (fri10-Sitar) (F09A)

// Add your own #includes here

#include "mandelbrot.h"
#include "pixelColor.h"

// Add your own #defines here
// abs(z) can't exceed this number other it's not in mandelbrot
#define ESCAPED 4

// Add your own function prototypes here
static void fillMandelbrotSet(complex mandelbrotSet[TILE_SIZE][TILE_SIZE], complex center, int z);
static double power(int base, int exponent);

// Draw a single Mandelbrot tile, by calculating and colouring each of
// the pixels in the tile.
//
// Your function "returns" this tile by filling in the `pixels` 2D array
// that is passed in to your function.
//
// The `pixels` array is TILE_SIZE high and TILE_SIZE wide.
// The bottom left corner of the image is pixels[0][0].
//
// `center` is a complex number, representing the center of the tile.
// `z` is used to calculate the distance between each pixel in the image.
// Each pixel is 2^(-z) apart from each other.
void drawMandelbrot(pixel pixels[TILE_SIZE][TILE_SIZE], complex center, int z) {
    int grid[TILE_SIZE][TILE_SIZE];
    escapeGrid(grid, center, z);
    int i = 0;
    int j = 0;
    while (i < TILE_SIZE) {
        j = 0;
        while (j < TILE_SIZE) {
            pixels[i][j] = pixelColor(grid[i][j]);
            j++;
        }
        i++;
    }
}

// Determine the number of steps required to escape the Mandelbrot set,
// for the given complex number `c`.
int escapeSteps(complex c) {
    int steps = 0;
    double x = 0;
    double y = 0;
    double xTemp = 0;

    while (x * x + y * y <= ESCAPED && steps < MAX_STEPS) {
        xTemp = x * x - y * y + c.re;
        y = 2 * x * y + c.im;
        x = xTemp;
        steps++;
    }
    if(steps==MAX_STEPS) {
        steps=NO_ESCAPE;
    }
    return steps;
}

// Fill a grid of TILE_SIZE by TILE_SIZE pixels, with the number of
// steps each pixel took to escape the Mandelbrot set.
void escapeGrid(int grid[TILE_SIZE][TILE_SIZE], complex center, int z) {

    complex mandelbrotSet[TILE_SIZE][TILE_SIZE];
    fillMandelbrotSet(mandelbrotSet, center, z);
    int i = 0;
    int j = 0;
    while (i < TILE_SIZE) {
        j = 0;
        while (j < TILE_SIZE) {
            grid[i][j] = escapeSteps(mandelbrotSet[i][j]);
            j++;
        }
        i++;
    }
}

// Add your own functions here.
// Remember to make them static.

// fills a matrix with the real and imaginary values/coordinates
// of each pixel
// takes in complex multidimensional array, center of type complex
// and z (the zoom level)
// uses this information to calculate exact coordinates of each pixel
// and enters this in array.re and array.im
static void fillMandelbrotSet(complex mandelbrotSet[TILE_SIZE][TILE_SIZE], complex center, int z) {
    double distance = 0;
    double length = 0;
    distance = 1 / power(2, z);
    length = distance * (TILE_SIZE - 1);
    int i = 0;
    int j = 0;
    while (i < TILE_SIZE) {
        j = 0;
        while (j < TILE_SIZE) {
            mandelbrotSet[i][j].re = (center.re - length / 2 + distance * j);
            mandelbrotSet[i][j].im = (center.im - length / 2 + distance * i);
            j++;
        }
        i++;
    }
}

// takes in the base and exponent
// returns the base ^ exponent as double
// only takes in integers
static double power(int base, int exponent) {
    double powered = 1;
    while (exponent != 0) {
        powered = powered * base;
        exponent--;
    }
    return powered;

}
