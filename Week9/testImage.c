#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "Image.h"
#include<assert.h>

int main () {

    Image i = newImage(4,5);
    assert(imageGetHeight(i) == 5);
    assert(imageGetWidth(i) == 4);
    point p;
    p.x=1;
    p.y=2;
    point p1;
    p1.x=0;
    p1.y=0;
    pixel color;
    color.red=100;
    color.green=255;
    color.blue=255;
    imageSetPixel(i,p,color);
    assert(imageGetPixel(i,p).red == 100);
    assert(imageGetPixel(i,p1).red == 0);
    free(i);
    pixel color1 = {
        .red=255,
        .green=255,
        .blue=255,
    };
    Image k = newImage(600,512);
    point start = {
        .x=380,
        .y=380,
    };
    point end = {
        .x=0,
        .y=130,
    };
    point origin = {
        .x=0,
        .y=0,
    };
    imageDrawLine(k,color1,start,end);
    assert(imageGetPixel(k,end).red== 255);
    Image o = newImage(10,10);
    point p2 = {
        .x=9,
        .y=9,
    };
    point p3 = {
        .x=8,
        .y=8,
    };
    point p4 = {
        .x=7,
        .y=7,
    };
    imageDrawLine(o,color,origin,p2);
    assert(imageGetPixel(o,p3).red==100);
    assert(imageGetPixel(o,p4).red==100);
    Image A = newImage(200,200);
    point bottom = {
        .x=50,
        .y=50,
    };
    point top = {
        .x=150,
        .y=100,
    };
    imageDrawRectangle(A,color,bottom,top);
    Image C = newImage(600,512);
    point centre = {
        .x=256,
        .y=256,
    };
    int radius = 200;
    point test = {
        .x=456,
        .y=256,
    };
    imageDrawCircle(C,color,centre,radius);
    assert(imageGetPixel(C,centre).red==100);
    assert(imageGetPixel(C,test).red == 100);
    unsigned char *buf;
    int size = imageAsBMP (C, &buf);
    fwrite (buf, sizeof (unsigned char), size, stdout);
    free(buf);
    printf("All test passed!\n");
}
