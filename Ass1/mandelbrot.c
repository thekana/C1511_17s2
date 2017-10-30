// Assignment 1 Mandelbrot
//
// Completed by
//  ... (z0000000)
//  ... (z0000000)
//
// Modified on 2017-??-??
// Tutor's name (dayHH-lab)

// Add your own #includes here

#include "mandelbrot.h"
#include "pixelColor.h"
// Add your own #defines here
#include <math.h>
// Add your own function prototypes here

void fillMandelbrotSet(complex mandelbrotSet[TILE_SIZE][TILE_SIZE], complex center, int z);
double zPow2(int z);
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
    int i=0, j=0;
    while(i<TILE_SIZE) {
        j=0;
        while(j<TILE_SIZE) {
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
    double x = 0, y = 0, xTemp = 0;
    /*while (x*x+y*y < 4 && steps < MAX_STEPS) {
        xTemp = x*x - y*y + c.re;
        y = 2*x*y + c.im;
        x = xTemp;
        steps++;
    }*/
    double calcX, calcY, calcTempX;
    x=c.re;
    y=c.im;
    calcX = 0;
    calcY = 0;
    steps = 0;
    while ((steps < MAX_STEPS) && (calcX * calcX + calcY * calcY < 2 * 2)) {
        calcTempX = (calcX * calcX - calcY * calcY) + x;
        calcY = (2 * calcX * calcY) + y;
        calcX = calcTempX;
    
        steps++;
    }
    return steps;
}

// Fill a grid of TILE_SIZE by TILE_SIZE pixels, with the number of
// steps each pixel took to escape the Mandelbrot set.
void escapeGrid(int grid[TILE_SIZE][TILE_SIZE], complex center, int z) {

    complex mandelbrotSet[TILE_SIZE][TILE_SIZE];
    fillMandelbrotSet(mandelbrotSet, center, z);
    int i=0, j=0;
    while(i < TILE_SIZE) {
        j=0;
        while(j < TILE_SIZE) {
            grid[i][j] = escapeSteps(mandelbrotSet[i][j]);
            j++;
        }
        i++;
    }
}

void fillMandelbrotSet(complex mandelbrotSet[TILE_SIZE][TILE_SIZE], complex center, int z) {
    double distance=0, length=0;
    distance=1/zPow2(z);
    length = distance * (TILE_SIZE-1);
    int i=0,j=0;
    while(i<TILE_SIZE) {
        j=0;
        while(j<TILE_SIZE) {
            if(j<TILE_SIZE/2) {
                mandelbrotSet[i][j].re = (center.re - length/2 + distance*j+distance/2);
            } else {
                mandelbrotSet[i][j].re = (center.re - length/2 + distance*j-distance/2);
            }
            if(i<TILE_SIZE/2) {
                mandelbrotSet[i][j].im = (center.im - length/2 + distance*i+distance/2);
            } else {
                mandelbrotSet[i][j].im = (center.im - length/2 + distance*i-distance/2);
            }
            //mandelbrotSet[i][j].re = (center.re - length/2 + distance*j);
            //mandelbrotSet[i][j].im = (center.im - length/2 + distance*i);
            j++;
        }
        i++;
    }
}

double zPow2(int z) {

    double ans=1;
    while(z!=0) {
        ans=ans*2;
        z--;
    }
    return ans;
}


// Add your own functions here.
// Remember to make them static.
