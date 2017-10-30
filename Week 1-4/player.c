// AI for playing the game
// Created by: ... (z0000000)
//             ... (z0000000)
//             ... (z0000000)
//             ... (z0000000)
// Lab: (F09A)(fri10-sitar)
// Tutor: Zain Afzal
// Lab Assistant: Anna Zhang
// Created 2017-09-27 - 2017-10-27

#include "Game.h"
#include "player.h"
#include "Card.h"

#define NOT_FOUND -1

// Find a card in the player's hand that matches the specified color,
// if such a card exists.
// Returns the card index, or NOT_FOUND if no matching card was found.
static int findMatchingCardColor (Game game, color color);

// Do two cards match on either value, color, or suit?
// Returns TRUE if they match any of the above features, and
// FALSE if they don't match on any of the above features.
static int doCardsMatch (Card first, Card second);

// Determine whether the player can currently draw a card.
// If they can't draw a card, they should probably end their turn.
static int canDrawCard (Game game);

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_UNO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayUNO (Game game);

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_DUO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayDUO (Game game);

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_TRIO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayTRIO (Game game);


// This function is to be implemented by the A.I.
// It will be called when the player can make an action on their turn.
//
// !!!!!   The function is called repeatedly, until   !!!!!
// !!!!!      they make the action `END_TURN`.        !!!!!
//
// If the player's turn is skipped, this funciton
// is *not* called for that player.
//
// Don't forget about the `isValidMove` function -- it's a handy way
// to work out before you play a move whether or not it will be valid
// (and you should only ever be making valid moves).
//
// You can also use it to help you work out where you are at in the
// game, without needing to look through all of the previous state
// yourself --
//
// Looking at the diagram of valid moves at any given point in the game,
// we can see that at the start of the game, it's valid to:
//   - call somebody out for forgetting to SAY_UNO / SAY_DUO / SAY_TRIO,
//   - draw a card,
//   - play a card, *if* you have a valid card that you can play.
//
// It's not valid to end your turn unless you've done some other
// action/s (again, see the diagram).
//
// We can take advantage of that for our very simple A.I. to determine
// where we are at in our turn, and thus what move we should make.
playerMove decideMove(Game game) {
    // Start out by making a move struct, to say what our move is.
    playerMove move;

    // Set our move to be END_TURN, and check whether that's
    // a valid move -- if it is, then just end our turn (for now).
    move.action = END_TURN;

    // If it's not valid to end turn, we must need to make
    // some other action...
    //
    // What actions are valid at this point?
    if (!isValidMove(game, move)) {
        // Valid actions include:
        //   - play a card,
        //   - draw a card,
        //   - call the previous play out for forgetting to SAY_UNO etc.
        //   - self declaring SAY_UNO etc.
        // The easiest thing here is to draw a card, since we don't
        // need to try to work out if we have a valid card, etc.
        
        move.action = DRAW_CARD;
       
        color previouslyPlayedColor = cardColor(topDiscard(game));
        
        int index = findMatchingCardColor(game, previouslyPlayedColor);
        
        if (index != NOT_FOUND) {
            move.action = PLAY_CARD;
            move.card = handCard(game, index);
        }
        
    }

    return move;
}


// Find a card in the player's hand that matches the specified color,
// if such a card exists.
// Returns the card index, or NOT_FOUND if no matching card was found.
static int findMatchingCardColor (Game game, color color) {
    int length = handCardCount(game);
    int i = 0;
    
    int contains = NOT_FOUND;
    
    while (i < length && contains == NOT_FOUND) {
        Card curr = handCard(game, i);
        
        if (cardColor(curr) == color) {
            contains = i;
        }  
        
        i++;
    }
    
    return contains;
}

// Do two cards match on either value, color, or suit?
// Returns TRUE if they match any of the above features, and
// FALSE if they don't match on any of the above features.
static int doCardsMatch (Card first, Card second) {
    int contains = FALSE;
    
    if (cardColor(first) == cardColor(second)) {
        contains = TRUE;
    }

    if (cardValue(first) == cardValue(second)) {
        contains = TRUE;
    }

    if (cardSuit(first) == cardSuit(second)) {
        contains = TRUE;
    }
    
    return contains;
}

// Determine whether the player can currently draw a card.
// If they can't draw a card, they should probably end their turn.
static int canDrawCard (Game game) {
    playerMove move = {
        .action = DRAW_CARD
    };

    int isValid = FALSE;

    if (isValidMove(game, move)) {
        isValid = TRUE;
    }


   // Player has already drawn a card 
    // Player has already played a card
    // Deck is empty
    // 

    return isValid;
}

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_UNO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayUNO (Game game) {
    playerMove move = {
        .action = SAY_UNO
    };

    int isValid = FALSE;

    if (isValidMove(game, move)) {
        isValid = TRUE;

    }

    return isValid;
}

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_DUO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayDUO (Game game) {
    playerMove move = {
        .action = SAY_DUO
    };

    int isValid = FALSE;

    if (isValidMove(game, move)) {
        isValid = TRUE;
    }

    return isValid;
}

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_TRIO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayTRIO (Game game) {
    playerMove move = {
        .action = SAY_TRIO 
    };

    int isValid = FALSE;

    if (isValidMove(game, move)) {
        isValid = TRUE;
    }

    return isValid;
}




