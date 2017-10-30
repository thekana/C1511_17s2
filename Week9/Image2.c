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
    new->array = calloc(width, sizeof(pixel*));
    int i=0,j=0;
    while(i<width){
        new->array[i] = calloc(height,sizeof(pixel));
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
            new->array[j][i]= defaultPixel;
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
    return i->array[p.x][p.y];
}

// Given an image, and a particular point and a pixel, set that
// point's value to the pixel passed in.
void imageSetPixel (Image i, point p, pixel color) {
    i->array[p.x][p.y]=color;
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
        i->array[x][y]=color;
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
            i->array[start.x][y]=color;
            y++;
        }
    }
}

// Given an image, a color, a bottom left (x,y) point, and a top right
// (x,y) point, draw on the image a filled rectangle bounded by the
// corners in the specified colour.
//void imageDrawRectangle (
//    Image i, pixel color, point bottomLeft, point topRight);


// Given an image, a color, a centre (x,y) point, and a radius `r`,
// draw on the image a filled circle of the given radius around the
// given centre in the specified colour.
//void imageDrawCircle (
//    Image i, pixel color, point centre, unsigned int radius);


////////////////////////////////////////////////////////////////////////
// For the challenge activity "An Elliptical Workout", you need to
// implement the eight non-challenge functions above, and this function:

// Given an image, a color, a centre (x,y) point, and the two ellipse
// parameters `a` and `b`, draws an ellipse around the centre, with
// `a` and `b` as parameters, on the image.
//
// The Cartesian form of an ellipse is, for a centre (cx, cy) and two
// non-negative real terms `a` and `b`:
//
//     (x - cx)²   (y - cy)²
//     --------- + --------- = 1
//        a²           b²
//void imageDrawEllipse (
//    Image i, pixel color, point centre, double a, double b);


////////////////////////////////////////////////////////////////////////
// For the challenge activity "Reticulating Splines", you need to
// implement the eight non-challenge functions above, and this function:

// Given an image, a colour, a "precision", a start (`x0`,`y0`)
// point, two control points (`x1`,`y1`) and (`x2`,`y2`), and an
// end point (`x3,y3`), draw on the image a order-3 Bézier curve
// bounded by those points, in that colour, whose `t` values
// increase by the specified precision at each iteration.
//
// The function for a Bézier curve is, for (x,y) points P₀, P₁,
// P₂, P₃, for all real values `t` from 0 to 1,
//
//     B(t) =   (1 - t)³    P₀
//          + 3 (1 - t)² t  P₁
//          + 3 (1 - t)  t² P₂
//          +            t³ P₃
//
// For each `t`, the coördinate is the combination of `x` values
// and of `y` values, with a simple binomial expansion.
//void imageDrawBezer (
//    Image i, pixel color, double precision,
//    point p0, point p1, point p2, point p3);


////////////////////////////////////////////////////////////////////////
// We also provide this useful helper function in `imageAsBMP.c`:

// Given an image, and a reference to a buffer, allocates an array of
// `unsigned char`s to fit the header and pixels in, containing a BMP
// image, and returns the size of the allocation.
//
// Strictly, this definition shouldn't be in this ADT header file, as
// it is an ADT consumer, but we're keeping it here for convenience.
// You could write a somewhat better version of this with access to
// the ADT's innards.
//
// To use it, you would do:
//
//     unsigned char *buf;
//     int size = imageAsBMP (i, &buf);
//
// Now you have a full image in `buf`; you could write this to
// standard output, for example, by using the `fwrite` standard
// library function from <stdio.h>:
//
//     fwrite (buf, sizeof (unsigned char), size, stdout);
//
// This writes `buf`, which contains `size` items of `unsigned char`
// size each, to `stdout`.
//int imageAsBMP (Image i, unsigned char **buf);
