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
/*pixel pixelColor(int steps) {
    pixel color = {
        .red = 0,
        .green = 0,
        .blue = 0
    };

    if(steps > 250) {
        color.red = 0;
        color.green = 0;
        color.blue = 0;
    } else {
        color.red = steps - 1;
        color.green = steps - 1;
        color.blue = 0;
    }

    return color;
}*/

pixel pixelColor(int steps) {
    
    int redness = 0;
    int greeness = 0;
    int blueness = 0;
    
    if (steps<30 && steps>=0){
        redness = 0 + steps*4;
        greeness = 0 + steps*4;
        blueness = 0 + steps*4;
    
    }else if (steps>=30 && steps < 65){
            redness = 255 - steps;
            greeness = 51 - steps;
            blueness = 51 - steps;
    }else if (steps>=65 && steps < 100){
            redness = 204 + steps;
            greeness = 0 + steps*2;
            blueness = 102 + steps;
    }else if (steps>=100 && steps < 140){
            redness = 178 - steps;
            greeness = 102 - steps;
            blueness = 255 - steps/2;
    }else if (steps>=140 && steps < 190){
            redness = 0 + steps*2/3;
            greeness = 0 + steps*2/3;
            blueness = 153 + steps*2/3;
    }else if (steps>=190 && steps < 256){
            redness = 102 - steps/2;
            greeness = 178 + steps/2;
            blueness = 255;
    }
    

    pixel color = {
        .red = redness,
        .green = greeness,
        .blue = blueness
    };
    
    return color;
}
