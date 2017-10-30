// Assignment 1 Mandelbrot
//
// Completed by
//  ... (z0000000)
//  ... (z0000000)
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
#define num 256
// Add your own #defines here
int escapeSteps(complex c);
void escapeGrid(int grid[TILE_SIZE][TILE_SIZE], complex center, int z);
double power2(int z);
void fillMandelbrotSet(complex mandelbrotSet[TILE_SIZE][TILE_SIZE], complex center, int z);
void display(int grid[TILE_SIZE][TILE_SIZE]);
void drawMandelbrot(pixel pixels[TILE_SIZE][TILE_SIZE], complex center, int z);
void writeImage(int output, pixel pixels[TILE_SIZE][TILE_SIZE]);
pixel pixelColor(int steps);

int main () {
    //int grid[TILE_SIZE][TILE_SIZE];
    pixel pixels[TILE_SIZE][TILE_SIZE];
    complex center = {
    .re= 0.41472377,
    .im= -0.3449
    };
    //center.im=-center.im;
    int z=12;
    //escapeGrid(grid, center, z);
    //display(grid);
    drawMandelbrot(pixels,center,z);
    writeImage(STDOUT_FILENO, pixels);
}

void drawMandelbrot(pixel pixels[TILE_SIZE][TILE_SIZE], complex center, int z) {
    // hint: use this array to store the result from escapeGrid.
    int grid[TILE_SIZE][TILE_SIZE];
    escapeGrid(grid, center, z);
    int i=0, j=0;
    while(i<TILE_SIZE) {
        j=0;
        while(j<TILE_SIZE) {
            pixels[i][j] = pixelColor(grid[i][j]);
            //pixels[i][j].green = pixelColor(grid[i][j]).green;
            //pixels[i][j].blue = pixelColor(grid[i][j]).blue;
            j++;
        }
        i++;
    }


}


int escapeSteps(complex c) {

    int steps = 0, stop=0;
    double x=0, y=0, xTemp=0, yTemp=0;
//    x=c.re;
//    y=c.im;
    while (steps < num) {
        xTemp = x*x - y*y + c.re;
        yTemp = 2*x*y + c.im;
        x=xTemp;
        y=yTemp;
        if (x*x+y*y > 4) {
            stop = steps;
            steps ==255;
        }
        steps++;
    }
//    double calcX, calcY, calcTempX;
//    
 //   calcX = 0;
   // calcY = 0;
    //steps = 0;
  //  while ((steps < num) && (calcX * calcX + calcY * calcY < 2 * 2)) {
   //     calcTempX = (calcX * calcX - calcY * calcY) + x;
     //   calcY = (2 * calcX * calcY) + y;
   //     calcX = calcTempX;
    
  //      steps++;
   // }
   

    return stop;
//}
/*int escapeSteps(complex c) {
    int steps = 1;
    int stop = 0;
    double absZn = 0;
    double imag = 0;
    double real = 0;
    double znReal = 0;
    double znImag = 0;
    
    while (steps < 256){
        znReal = pow(real,2) - pow(imag,2) + c.re;
        znImag = (2 * imag * real) + c.im;
        absZn = pow((pow(znReal,2) + pow(znImag,2)), 0.5);
        if (absZn > 2){
            stop = steps;
            steps = 255;
        }
        real = znReal;
        imag = znImag;
        steps++;
    }
    return stop;
}*/
}
// Fill a grid of TILE_SIZE by TILE_SIZE pixels, with the number of
// steps each pixel took to escape the Mandelbrot set.
void escapeGrid(int grid[TILE_SIZE][TILE_SIZE], complex center, int z) {

    int i=0,j=0;
    double xStart;
    double x=center.re;
    double y=center.im;
    complex c;
    double distBetweenPixels = 1/power2(z);
    double regionLength = distBetweenPixels * (TILE_SIZE - 1);
    x = x - (regionLength / 2);
    xStart = x;
    y = y - (regionLength / 2);

    while (i < TILE_SIZE) {
        x = xStart;
        j=0;
        while (j < TILE_SIZE) {
            c.re = x;
            c.im = y;
            grid[i][j]=escapeSteps(c);
            j++;
            x += distBetweenPixels;
        }
        i++;
        y += distBetweenPixels;
    }
/*    complex mandelbrotSet[TILE_SIZE][TILE_SIZE];
    fillMandelbrotSet(mandelbrotSet, center, z);
    int i=0, j=0;
    while(i < TILE_SIZE) {
        j=0;
        while(j < TILE_SIZE) {
            grid[i][j] = escapeSteps(mandelbrotSet[i][j]);
            j++;
        }
        i++;
    }*/
}

double power2(int z) {

    double ans=1;
    while(z!=0) {
        ans=ans*2;
        z--;
    }
    return ans;
}

void fillMandelbrotSet(complex mandelbrotSet[TILE_SIZE][TILE_SIZE], complex center, int z) {
    double distance=0, length=0;
    printf("%lf\n",distance=1/power2(z));
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
            j++;
        }
        i++;
    }
    //printf("%lf + %lfi\n",mandelbrotSet[0][0].re,mandelbrotSet[0][0].im);
    //printf("%lf + %lfi\n",mandelbrotSet[0][511].re,mandelbrotSet[0][511].im);

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

/*    pixel color = {
        .red = 0,
        .green = 0,
        .blue = 0
    };
    int a=220,b=123,c=155;
    if(steps<=50) {
        color.red = 0;
        color.green = 0;
        color.blue = 0;
    } else {
        color.red = (steps -1)% MAX_STEPS;//(steps * a) % MAX_STEPS;
        color.green = 0;//(steps * b) % MAX_STEPS;
        color.blue = (steps-1)% MAX_STEPS;//(steps * c) % MAX_STEPS;
    }
    return color;*/
    pixel color = {
        .red = 0,
        .green = 0,
        .blue = 0
    };

    if (steps<30 && steps>=0){
        color.red = 0 + steps*4;
        color.green= 0 + steps*4;
        color.blue= 0 + steps*4;
    
    }else if (steps>=30 && steps < 65){
            color.red = 255 - steps;
            color.green = 51 - steps;
            color.blue = 51 - steps;
    }else if (steps>=65 && steps < 100){
            color.red = 204 + steps;
            color.green = 0 + steps*2;
            color.blue = 102 + steps;
    }else if (steps>=100 && steps < 140){
            color.red = 178 - steps;
            color.green = 102 - steps;
            color.blue = 255 - steps/2;
    }else if (steps>=140 && steps < 190){
            color.red = 0 + steps*2/3;
            color.green = 0 + steps*2/3;
            color.blue = 153 + steps*2/3;
    }else if (steps>=190 && steps < 256){
            color.red = 102 - steps/2;
            color.green = 178 + steps/2;
            color.blue = 255;
    }
    return color;
}
