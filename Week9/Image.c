// Image ADT
//  Quinn z5142018
//  King z5176970
// Created on 2017 09 22
// Tutor's name Zain F09A

#include<stdio.h>
#include<stdlib.h>
#include "Image.h"
#include <assert.h>
#include <math.h>
typedef struct _image {
    unsigned int width;
    unsigned int height;
    pixel **array;
} image;


Image newImage (unsigned int width, unsigned int height){

    Image new = calloc(1, sizeof(image));
    if (new == NULL) {
        fprintf(stderr, "Could not allocate memory\n");
        exit(EXIT_FAILURE);
    }
    new->width = width;
    new->height = height;
    new->array = calloc(height, sizeof(pixel*));
    int i=0,j=0;
    while(i<height){
        new->array[i] = calloc(width,sizeof(pixel));
        i++;
    }
    i=0;
    pixel defaultPixel = {
        .red = 0,
        .green = 0,
        .blue = 0,
    };
    while(i<height) {
        j=0;
        while(j<width) {
            new->array[i][j]= defaultPixel;
            j++;
        }
        i++;
    }
    return new;
}

// Release all resources associated with an `Image`.
void destroyImage (Image i){
    free(i->array);
    free(i);
}
// Given an image, get the image's width.
unsigned int imageGetWidth (Image i){
    return i->width;
}

// Given an image, get the image's height.
unsigned int imageGetHeight (Image i){
    return i->height;
}


// Given an image, and a particular point, get that point's value.
pixel imageGetPixel (Image i, point p){
    return i->array[p.y][p.x];
}

// Given an image, and a particular point and a pixel, set that
// point's value to the pixel passed in.
void imageSetPixel (Image i, point p, pixel color) {
    i->array[p.y][p.x]=color;
}


////////////////////////////////////////////////////////////////////////
// For the activity "Drawing on an Image", you need to implement the
// above, and these three functions:

// Given an image, a pixel colour, a start (x,y) point, and an end
// (x,y) point, draw on the image a line from the start point to the
// end point in the specified colour.
void imageDrawLine (Image i, pixel color, point start, point end) {
    unsigned int x=0;
    unsigned int y=0;
    unsigned int tempX=0;
    unsigned int tempY=0;
    //Prefer starting point to be on the left side of the image therefore swap
    if(end.x < start.x) {
        tempX=start.x;
        tempY=start.y;
        start.x=end.x;
        start.y=end.y;
        end.x=tempX;
        end.y=tempY;
    }
    //For a verticle line, prefer the starting point to be lower than the ending point
    if(start.x == end.x && end.y < start.y) {
        tempX=start.x;
        tempY=start.y;
        start.x=end.x;
        start.y=end.y;
        end.x=tempX;
        end.y=tempY;
    }
    x=start.x;
    y=start.y;
    int factor=-1;
    if(end.y > start.y) {
        factor= 1;
    }
    //Algorithm from https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    int dx=0;
    int dy=0;
    int D=0;
    dx=end.x-start.x;
    dy=factor*(end.y-start.y);
    D=2*dy-dx;
    while(x<=end.x) {
        i->array[y][x]=color;
        if (D>0) {
            y=y+factor;
            D=D - 2*dx;
        }
        D= D+ 2*dy;
        x++;
    }
    //drawing a verticle line since the above algorithm doesnt seem to do it
    if(start.x==end.x) {
        while(y<=end.y) {
            i->array[y][start.x]=color;
            y++;
        }
    }
}

// Given an image, a color, a bottom left (x,y) point, and a top right
// (x,y) point, draw on the image a filled rectangle bounded by the
// corners in the specified colour.
void imageDrawRectangle (Image i, pixel color, point bottomLeft, point topRight) {
    unsigned int x=0;
    unsigned int y=0;
    x=bottomLeft.x;
    y=bottomLeft.y;
    while(y<=topRight.y) {
        x=bottomLeft.x;
        while(x<=topRight.x) {
            i->array[y][x]=color;
            x++;
        }
        y++;
    }
}


// Given an image, a color, a centre (x,y) point, and a radius `r`,
// draw on the image a filled circle of the given radius around the
// given centre in the specified colour.
void imageDrawCircle (Image i, pixel color, point centre, unsigned int radius) {
    int x=0;
    int y=0;
    //Set centre values to int otherwise abs() wont work.
    int yc=centre.y;
    int xc=centre.x;
    while(y<i->height) {
        x=0;
        while(x<i->width) {
            //Check if a point is in the circle or not
            if (sqrt(pow(abs(x-xc),2)+pow(abs(y-yc),2))<=radius) {
                i->array[y][x] = color;
            }
            x++;
        }
        y++;
    }
}
