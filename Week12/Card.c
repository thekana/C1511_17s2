#include <stdlib.h>
//#include <err.h>
#include "Card.h"

typedef struct _card {
    suit suit;
    value value;
    color color;
} card;

Card newCard(value value, color color, suit suit) {
    Card cardNew = calloc(1, sizeof(card));

    if (cardNew == NULL) {
        //errx(EXIT_FAILURE, "Failed to create a new card");
    }

    cardNew->value = value;
    cardNew->color = color;
    cardNew->suit = suit;

    return cardNew;
}

void destroyCard (Card card) {
    free (card);
}

suit cardSuit (Card card) {
    return card->suit;
}

value cardValue (Card card) {
    return card->value;
}

color cardColor (Card card) {
    return card->color;
}