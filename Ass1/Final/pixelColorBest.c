// Assignment 1 Mandelbrot: Pixel Color
//
// Completed by
// Jasvir Boparoy (z5165068)
// Kanadech (King) (z5176970)
//
// Modified on 2017-09-05 - 2017-09-14
// Tutor's name: Zain Afzal and Anna Zhang (fri10-Sitar) (F09A)

#include "mandelbrot.h"
#include "pixelColor.h"

int redColourCode(int steps);
int greenColourCode(int steps);
int blueColourCode(int steps);
int reseter(int steps);
// This function should take a number (of steps taken to escape the
// Mandelbrot set), and convert it to a color.
//
// You have artistic licence here, so make your Mandelbrot look amazing.

// Takes in integer steps and returns color which is a struct of
// red, green and blue.
pixel pixelColor(int steps) {
    // Assigns everything to black first for debugging purposes
    pixel color = {
        .red = 256- steps,
        .green = 256 - steps,
        .blue = 256 - steps,
    };

    // uses three functions to determine appropriate colour codes
    if (steps<150) {
    color.red = redColourCode(steps);
    color.green = greenColourCode(steps);
    color.blue = blueColourCode(steps);
    }

    return color;
}

// Takes in value of steps and does some calculations
// Returns value between 0 and 255 for red colour
int redColourCode(int steps) {

    steps = steps * 6;
    steps = reseter(steps);

    /*while (steps > 256) {
        if (steps % 2 == 0) {
            steps = steps / 2;
        } else {
            steps = steps * 36 + 3; // causes number to become even
        }
    }*/
    return steps;
}

// Takes in value of steps and does some calculations
// Returns value between 0 and 255 for green colour
int greenColourCode(int steps) {

    steps = steps * 5;
    steps = reseter(steps);

    /*while (steps > 256) {
        if (steps % 2 == 0) {
            steps = steps / 2;
        } else {
            steps = steps * 91 - 1; // causes number to become even
        }
    }*/

    return steps;
}

// Takes in value of steps and does some calculations
// Returns value between 0 and 255 for blue colour
int blueColourCode(int steps) {
    steps = steps * 2;
    steps = reseter(steps);
    /*while (steps > 256) {
        if (steps % 2 == 0) {
            steps = steps / 2;
        } else {
            steps = steps * 5 + 1; // causes number to become even
        }
    }*/

    return steps;
}

int reseter(int steps) {
    while (steps > 256) {
        if (steps % 6 == 0) {
            steps = steps / 6;
        } else {
            steps = steps + 1; // causes number to become even
        }
    }

    return steps;
}
