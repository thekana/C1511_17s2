// Assignment 1 Mandelbrot
//
// Completed by
//  KING (z5176970)
//
//
// Modified on 2017-??-??
// Tutor's name (dayHH-lab)

// Add your own #includes here
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mandelbrot.h"
#include "pixelColor.h"
#include <math.h>
// For writing BMP
#define PIXEL_START 26
#define PIXEL_BYTES 3
#define PIXEL_ALIGN 4
#define PIXEL_BITS  24
#define HEADER_SIZE 12

int escapeSteps(complex c);
void escapeGrid(int grid[TILE_SIZE][TILE_SIZE], complex center, int z);
double zPow2(int z);
void fillMandelbrotSet(complex mandelbrotSet[TILE_SIZE][TILE_SIZE], complex center, int z);
void drawMandelbrot(pixel pixels[TILE_SIZE][TILE_SIZE], complex center, int z);
void writeImage(int output, pixel pixels[TILE_SIZE][TILE_SIZE]);
pixel pixelColor(int steps);

int main () {
    pixel pixels[TILE_SIZE][TILE_SIZE];
    complex center = {
    .re= 0.41472377,
    .im= -0.3449
    };
    //center.im=-center.im;
    int z=22;
    drawMandelbrot(pixels,center,z);
    writeImage(STDOUT_FILENO, pixels);
}

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


int escapeSteps(complex c) {

    int steps = 0;
    double x = 0, y = 0, xTemp = 0;
    while (sqrt(x*x+y*y) <= 2 && steps < 400) {
        xTemp = x*x - y*y + c.re;
        y = 2*x*y + c.im;
        x = xTemp;
        steps++;
    }
    return steps;
}

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

double zPow2(int z) {

    double ans=1;
    while(z!=0) {
        ans=ans*2;
        z--;
    }
    return ans;
}

void fillMandelbrotSet(complex mandelbrotSet[TILE_SIZE][TILE_SIZE], complex center, int z) {
    double distance=0, length=0;
    distance=1/zPow2(z);
    length = distance * (TILE_SIZE-1);
    int i=0,j=0;
    while(i<TILE_SIZE) {
        j=0;
        while(j<TILE_SIZE) {
            mandelbrotSet[i][j].re = (center.re - length/2 + distance*j);
            mandelbrotSet[i][j].im = (center.im - length/2 + distance*i);
            j++;
        }
        i++;
    }
}

void writeImage(int output, pixel pixels[TILE_SIZE][TILE_SIZE]) {
    // Initial BM bytes
    write(output, "BM", 2);

    // File size
    unsigned int rowSize = TILE_SIZE * PIXEL_BYTES;
    unsigned int rowPadding = 0;
    if (rowSize % PIXEL_ALIGN != 0) {
        // Padd pixel to align properly
        rowPadding = PIXEL_ALIGN - (rowSize % PIXEL_ALIGN);
        rowSize += rowPadding;
    }

    unsigned int fileSize = PIXEL_START + (rowSize * TILE_SIZE);
    write(output, (char *)&fileSize, sizeof(fileSize));

    // 4 reserved bytes
    write(output, "\0\0\0\0", 4);

    // start of pixel data
    // pixels start immediately after header
    unsigned int pixelStart = PIXEL_START;
    write(output, (char *)&pixelStart, sizeof(pixelStart));

    // Size of header
    unsigned int headerSize = HEADER_SIZE;
    write(output, (char *)&headerSize, sizeof(headerSize));

    // Image width and height
    unsigned short size = TILE_SIZE;
    write(output, (char *)&size, sizeof(size));
    write(output, (char *)&size, sizeof(size));

    // Number of image planes (1)
    unsigned short planes = 1;
    write(output, (char *)&planes, sizeof(planes));

    // Number of bits per pixel (24)
    unsigned short bitsPerPixel = PIXEL_BITS;
    write(output, (char *)&bitsPerPixel, sizeof(bitsPerPixel));

    // Write each of the pixels
    unsigned int padding = 0x01234567;
    int y = 0;
    while (y < TILE_SIZE) {
        int x = 0;
        while (x < TILE_SIZE) {
            // Write the blue, green, then red pixels
            pixel pixel = pixels[y][x];
            write(output, &(pixel.blue), sizeof(pixel.blue));
            write(output, &(pixel.green), sizeof(pixel.green));
            write(output, &(pixel.red), sizeof(pixel.red));
            x++;
        }

        // Write the row padding bytes
        write(output, (char *)&padding, rowPadding);
        y++;
    }
}

pixel pixelColor(int steps) {
    pixel color = {
        .red = 0,
        .green = 0,
        .blue = 0
    };
    //Shades of Gray
    if(steps >= 399) {
        color.red = 0;
        color.green = 0;
        color.blue = 0;
    } else {
        color.red = steps -1;
        color.green = steps -1;
        color.blue = steps -1;
    }
//    if (steps < 40) {
//        color.red = 0;
//        color.green = 0;
//        color.blue = 0;
//    }
//
//    if(steps == 256) {
//        color.red = 0;
//        color.green = 0;
//        color.blue = 0;
//    } else {
//        color.red = 


/*

    if(steps==256) {
        color.red = 0;
        color.green = 0;
        color.blue = 0;
    } else if (steps <=21 && steps <=25) {
        color.red = 0;
        color.green = 0;
        color.blue = 0;
    } else if (steps <=100 && steps <=110) {
        color.red = 0;
        color.green = 0;
        color.blue = 255;
    } else if (steps <=10 && steps <=20) {
        color.red = 64;
        color.green = 224;
        color.blue = 194;
    } else {
        color.red = 255;
        color.green = 100;
        color.blue = 200;
    }
*/


    return color;
}
