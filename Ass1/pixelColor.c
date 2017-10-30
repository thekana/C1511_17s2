// Assignment 1 Mandelbrot: Pixel Color
//
// Completed by
//  ... (z0000000)
//  ... (z0000000)
//
// Modified on 2017-??-??
// Tutor's name (dayHH-lab)

#include "mandelbrot.h"
#include "pixelColor.h"

// This function should take a number (of steps taken to escape the
// Mandelbrot set), and convert it to a color.
//
// You have artistic licence here, so make your Mandelbrot look amazing.
pixel pixelColor(int steps) {
    pixel color = {
        .red = 256- steps,
        .green = 256 - steps,
        .blue = 256 - steps,
    };
    if (steps < 100 ) {
        color.red =  steps*2;
        color.green =  steps*2;
        color.blue = steps*2;
    }
/*    if (steps >250 ) {
        color.red = 255 - steps;
        color.green = 255 - steps;
        color.blue = 255 - steps;
    } else if (steps>=30 && steps < 65){
        color.red = 255 - steps;
        color.green = 51 - steps;
        color.blue = 51 - steps;
    }else if (steps>=65 && steps < 100){
        color.red = 204 + steps*4/5;
        color.green = 0 + steps*2;
        color.blue = 102 + steps/10*2;
    }else if (steps>=100 && steps < 140){
        color.red = 178 - steps;
        color.green = 102 - steps;
        color.blue = 255 - steps/2;
    }else if (steps>=140 && steps < 190){
        color.red = 0 + steps*2/3;
        color.green = 0 + steps*2/3;
        color.blue = 153 + steps*2/3;
    }else if (steps>=190 && steps < 240){
        color.red = 102 - steps/3;
        color.green = 178 + steps/2;
        color.blue = 255;
    }else if (steps < 10 ) {
        color.red = (240*steps -1) % 156;
        color.green = (240*steps-1)% 100;
        color.blue = 99;
    } else {
        color.red = 255;
        color.green = 160*steps%100;
        color.blue = 255*steps - 128;
    }
    //int a=220,b=123,c=155;
    if(steps >= MAX_STEPS) {
        color.red = 0;
        color.green = 0;
        color.blue = 0;
    } else {
        color.red = steps;//(steps * a) % MAX_STEPS;
        color.green = steps;//(steps * b) % MAX_STEPS;
        color.blue = 0;//(steps * c) % MAX_STEPS;
    }*/
    return color;
}
