// The playing card interface. v0.0.2
//
// !!! DO NOT CHANGE THIS FILE !!!
//
// This interface represents a single playing card
// in the game of Final Card-Down.

#ifndef CARD_H
#define CARD_H

typedef struct _card *Card;

// The various colors that a card can have.
typedef enum {
    RED,
    BLUE,
    GREEN,
    YELLOW,
    PURPLE
} color;

// The various suits that a card can have.
typedef enum {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES,
    QUESTIONS
} suit;

// Create a new card.
// These values can only be set at creation time.
// The number should be between 0x0 and 0xF.
Card newCard(char number, color color, suit suit);

// Destroy an existing card.
void destroyCard(Card card);

// Get the card number (0x0 through 0xF).
char cardNumber(Card card);

// Get the card's color (RED, BLUE, etc).
color cardColor(Card card);

// Get the card suit (HEARTS, DIAMONDS, etc).
suit cardSuit(Card card);


#endif // CARD_H