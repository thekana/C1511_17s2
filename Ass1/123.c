#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#define TILE_SIZE 512

#define PIXEL_START 26
#define PIXEL_BYTES 3
#define PIXEL_ALIGN 4
#define PIXEL_BITS  24
#define HEADER_SIZE 12

typedef struct _complex {
    double re;
    double im;
} complex;

typedef struct _pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;

void fillMandelbrotSet(complex mandelbrotSet[TILE_SIZE][TILE_SIZE], complex center, int z);
void display(complex grid[TILE_SIZE][TILE_SIZE]);
double power2(int z);
void escapeGrid(complex grid[TILE_SIZE][TILE_SIZE], int STEP[TILE_SIZE][TILE_SIZE]);
int escapeSteps(complex c);
void displayINT(int STEP[TILE_SIZE][TILE_SIZE]);
pixel pixelColor(int steps);
void writeImage(int output, pixel pixels[TILE_SIZE][TILE_SIZE]);


int main () {

    complex center = {
        .re=0,
        .im=-0
    };
    int z=8;
    complex mandelbrotSet[TILE_SIZE][TILE_SIZE];
    int STEP[TILE_SIZE][TILE_SIZE];
    fillMandelbrotSet(mandelbrotSet,center,z);
    display(mandelbrotSet);
    escapeGrid(mandelbrotSet,STEP);
    displayINT(STEP);

    pixel pixels[TILE_SIZE][TILE_SIZE];
    int i=0, j=0;
    while(i<TILE_SIZE) {
        j=0;
        while(j<TILE_SIZE) {
            pixels[i][j].red = pixelColor(STEP[i][j]).red;
            pixels[i][j].green = pixelColor(STEP[i][j]).green;
            pixels[i][j].blue = pixelColor(STEP[i][j]).blue;
            j++;
        }
        i++;
    }

    writeImage(STDOUT_FILENO, pixels);
}

void fillMandelbrotSet(complex mandelbrotSet[TILE_SIZE][TILE_SIZE], complex center, int z) {
    double distance=0, length=0;
    printf("%lf\n",distance=1/power2(z));
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
    printf("%lf + %lfi\n",mandelbrotSet[0][0].re,mandelbrotSet[0][0].im);
    //printf("%lf + %lfi\n",mandelbrotSet[0][511].re,mandelbrotSet[0][511].im);
}

void display(complex grid[TILE_SIZE][TILE_SIZE])
{
    int i=TILE_SIZE-1, j=0;
    while(i>=0) {
        j=0;
        while(j<TILE_SIZE) {
            if (grid[i][j].im < 0) {
                printf("%lf%lfi ",grid[i][j].re,grid[i][j].im);
            } else {
                printf("%lf+%lfi ",grid[i][j].re,grid[i][j].im);
            }
            j++;
        }
        printf("\n");
        i--;
    }
}

void displayINT(int STEP[TILE_SIZE][TILE_SIZE]) {

    int i=TILE_SIZE-1, j=0;
    while(i>=0) {
        j=0;
        while(j<TILE_SIZE) {
            printf("%d ",STEP[i][j]);
            j++;
        }
        printf("\n");
        i--;
    }
}

double power2(int z) {

    double ans=1;
    while(z!=0) {
        ans=ans*2;
        z--;
    }
    return ans;
}

void escapeGrid(complex grid[TILE_SIZE][TILE_SIZE], int STEP[TILE_SIZE][TILE_SIZE]) {
    //int STEP[TILE_SIZE][TILE_SIZE];
    int i=0, j=0;
    while(i < TILE_SIZE) {
        j=0;
        while(j < TILE_SIZE) {
            STEP[i][j] = escapeSteps(grid[i][j]);
            //printf("%d ",STEP[i][j]);
            j++;
        }
        i++;
    }
}

int escapeSteps(complex c) {

    int steps = 0;
    double x=0, y=0;

    while (x*x+y*y <= 4 && steps < 256) {
        x = x*x - y*y + c.re;
        y = 2*x*y + c.im;
        steps++;
    }

    return steps;
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
    if(steps==256) {
        color.red = 0;
        color.green = 0;
        color.blue = 0;
    } else { 
        color.red = 255;
        color.green = 255;
        color.blue = 255;
    }
    // COMPLETE THIS FUNCTION

    return color;
}
