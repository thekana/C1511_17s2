// Testing The playing card implementation
// By King (z5176970)
//    Quinn (z5142018)
// Written on 2017-09-23
// Tutor Zain Friday Sitar

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Card.h"
int main (int argc, char *argv[]) {
    color newColor = RED;
    suit newSuit = HEARTS;
    char newNumber = 0xA;
    Card c = newCard (newNumber, newColor, newSuit);
    assert (c != NULL);
    assert (cardNumber (c) == newNumber);
    assert (cardColor (c) == newColor);
    assert (cardSuit (c) == newSuit);
    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}
