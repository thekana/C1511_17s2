#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#define TILE_SIZE 10

typedef struct _complex {
    double re;
    double im;
} complex;

void fillMandelbrotSet(complex mandelbrotSet[TILE_SIZE][TILE_SIZE], complex center, int z);
void display(complex grid[TILE_SIZE][TILE_SIZE]);
double power2(int z);
void escapeGrid(complex grid[TILE_SIZE][TILE_SIZE], int STEP[TILE_SIZE][TILE_SIZE]);
int escapeSteps(complex c);
void displayINT(int STEP[TILE_SIZE][TILE_SIZE]);


int main () {

    complex center = {
        .re=-0.3333,
        .im=-0.546
    };
    int z=8;
    complex mandelbrotSet[TILE_SIZE][TILE_SIZE];
    int STEP[TILE_SIZE][TILE_SIZE];
    fillMandelbrotSet(mandelbrotSet,center,z);
    display(mandelbrotSet);
    escapeGrid(mandelbrotSet,STEP);
    displayINT(STEP);
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

