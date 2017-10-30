// The playing card implementation.
//
// This is an implementation of the Card ADT, which represents a single
// playing card in the game of Final Card-Down.
//
// By King (z5176970)
//    Quinn (z5142018)
// Written on 2017-09-23
// Tutor Zain Friday Sitar

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Card.h"

// The following typedef is included in Card.h:
//         typedef struct _card *Card;
// This means that a struct card has to be implemented *somewhere*, but
// not necessarily in the .h file, as we have done with concrete types.
//
// The way we implement this in an ADT is that you design your own card
// struct, with the fields etc that you need to implement your ADT.

typedef struct _card {
    char number;
    color color;
    suit suit;
} card;

// Place the prototypes for your own functions here.
// Don't forget to make them static!



// The interface functions are below. You need to implement these.

// Create a new card.
// These values can only be set at creation time.
// The number should be between 0x0 and 0xF.
Card newCard(char number, color color, suit suit) {
    Card new = calloc(1, sizeof(card));
    if (new == NULL) {
        fprintf(stderr, "Could not allocate memory\n");
        exit(EXIT_FAILURE);
    }
    new->number= number;
    new->color= color;
    new->suit= suit;

    return new;
}

// Destroy an existing card.
void destroyCard(Card card) {
    free(card);
}

// Get the card suit (HEARTS, DIAMONDS, etc).
suit cardSuit(Card card) {
    return card->suit;
}

// Get the card number (0x0 through 0xF).
char cardNumber(Card card) {
    return card->number;
}

// Get the card's color (RED, BLUE, etc).
color cardColor(Card card) {
    return card->color;
}


// Implement your own functions here, don't forget to make them static!
