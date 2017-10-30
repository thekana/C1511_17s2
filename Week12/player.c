// A.I. player for FINAL CARD DOWN
//
// By King z5176970,
//    Quinn z5142018
//
// Written on 2017-10-22
// Tutor Zain (FRI F09A)

#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "player.h"
#include "Card.h"
#include <assert.h>
#define NOT_FOUND -1

// Find a card in the player's hand that matches the specified color,
// if such a card exists.
// Returns the card index, or NOT_FOUND if no matching card was found.
static int findMatchingCardColor (Game game, color color);
static int findMatchingCardSuit (Game game, suit suit);
static int findMatchingCardValue (Game game, value value);
static int findMatchingCard(Game game, Card topCard);
static int findMatchingDeclaredCard(Game game, Card topCard, color declared);
static int didIPlayCard(Game game);
static int didIDrawCard(Game game);
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

//Additional helper functions we may need

static int shouldSayTRIO (Game game);

static color declareColor(Game game);

static color previouslyDeclaredColor (Game game);


static int doIHaveACardToPlay(Game game, Card topCard);
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
    move.action = END_TURN;
    // Retrieve the top card from the discard pile
    Card topCard = topDiscard(game);
    // If it's not valid to end turn, we must need to make

    // PLay card action
    if (!isValidMove(game, move)) {
        if(doIHaveACardToPlay(game,topCard)) {
            //Need to check for declare draw 2 and other special cards for now just simple matching
            // Checking if we have anything on hand that matches
            int index = NOT_FOUND;
            if(currentTurn(game) != 0 && cardValue(topCard) == DECLARE) {
                    color declared = previouslyDeclaredColor(game);
                    index = findMatchingDeclaredCard(game, topCard, declared);
            } else {
                index = findMatchingCard(game, topCard);
            }
            if(index == NOT_FOUND) {
                move.action = DRAW_CARD;
            } else {
                move.action = PLAY_CARD;
                move.card = handCard(game,index);
            }
            if(cardValue(move.card) == DECLARE){
                //TODO Implement a function that selects proper nextColor
                move.nextColor = RED;
            }
        }
    }
    //Saying stuff (NOT callout)
    if(handCardCount(game) == 3 && didIPlayCard(game) ) {
        if(shouldSayTRIO(game)==TRUE) {
            move.action = SAY_TRIO;
        }
    } else if (handCardCount(game) == 2 && didIPlayCard(game)) {
        if(shouldSayDUO(game)==TRUE) {
            move.action = SAY_DUO;
        }
    } else if (handCardCount(game) == 1 && didIPlayCard(game)) {
        if(shouldSayUNO(game)==TRUE) {
            move.action = SAY_UNO;
        }
    }

    if (!isValidMove(game, move)) {
        move.action = DRAW_CARD;
    }
    return move;
}


// Find a card in the player's hand that matches the specified color,
// if such a card exists.
// Returns the card index, or NOT_FOUND if no matching card was found.
static int findMatchingCardColor (Game game, color color) {
    int playerNumber = 0;
    int handCardNumber =0;
    playerNumber = currentPlayer(game);
    handCardNumber = playerCardCount(game,playerNumber);
    int i = 0;
    int index = NOT_FOUND;
    while(i<handCardNumber && index == NOT_FOUND){
        Card curr = handCard(game,i);
        if(cardColor(curr)==color){
            index = i;
        } else {
            i++;
        }
    }
    return index;
}
static int findMatchingCardValue (Game game, value value) {
    int playerNumber = 0;
    int handCardNumber =0;
    playerNumber = currentPlayer(game);
    handCardNumber = playerCardCount(game,playerNumber);
    int i = 0;
    int index = NOT_FOUND;
    while(i<handCardNumber && index == NOT_FOUND){
        Card curr = handCard(game,i);
        if(cardValue(curr)==value){
            index = i;
        } else {
            i++;
        }
    }
    return index;
}
static int findMatchingCardSuit (Game game, suit suit) {
    int playerNumber = 0;
    int handCardNumber =0;
    playerNumber = currentPlayer(game);
    handCardNumber = playerCardCount(game,playerNumber);
    int i = 0;
    int index = NOT_FOUND;
    while(i<handCardNumber && index == NOT_FOUND){
        Card curr = handCard(game,i);
        if(cardSuit(curr)== suit){
            index = i;
        } else {
            i++;
        }
    }
    return index;
}


static int findMatchingCard(Game game, Card topCard) {
    int index = NOT_FOUND;
    if (findMatchingCardSuit(game,cardSuit(topCard)) != NOT_FOUND) {
        index = findMatchingCardSuit(game,cardSuit(topCard));
    } else if (findMatchingCardValue(game,cardValue(topCard)) != NOT_FOUND) {
        index = findMatchingCardValue(game,cardValue(topCard));
    } else if(findMatchingCardColor(game,cardColor(topCard)) != NOT_FOUND) {
        index = findMatchingCardColor(game,cardColor(topCard));
    }
    return index;
}

static int findMatchingDeclaredCard(Game game, Card topCard, color declared) {
    int index = NOT_FOUND;
    if (findMatchingCardSuit(game,cardSuit(topCard)) != NOT_FOUND) {
        index = findMatchingCardSuit(game,cardSuit(topCard));
    } else if (findMatchingCardValue(game,cardValue(topCard)) != NOT_FOUND) {
        index = findMatchingCardValue(game,cardValue(topCard));
    } else if(findMatchingCardColor(game,declared) != NOT_FOUND) {
        index = findMatchingCardColor(game,declared);
    }
    return index;
}
// Do two cards match on either value, color, or suit?
// Returns TRUE if they match any of the above features, and
// FALSE if they don't match on any of the above features.
static int doCardsMatch (Card first, Card second) {
    int match = FALSE;
    if(cardColor(first)==cardColor(second)){
        match = TRUE;
    }else if(cardValue(first)==cardValue(second)){
        match = TRUE;
    }else if(cardSuit(first)==cardSuit(second)){
        match = TRUE;
    }
    return match;
}

// Determine whether the player can currently draw a card.
// If they can't draw a card, they should probably end their turn.
static int canDrawCard (Game game) {
    playerMove move = {
        .action = DRAW_CARD
    };
    int isValid = FALSE;
    if(isValidMove(game,move)){
        isValid = TRUE;
    }
    return isValid;
}

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_UNO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayUNO (Game game) {
    int isValid = FALSE;
    int length = handCardCount(game);
    //Checking if I have said it before
    int i = 0;
    int answer = FALSE;
    while(i < turnMoves(game,currentTurn(game))) {
        if (pastMove(game, currentTurn(game), i).action == SAY_UNO) {
            answer = TRUE;
        }
        i++;
    }
    if (length == 1 && answer == FALSE) {
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
    int isValid = FALSE;
    int length = handCardCount(game);
    //Checking if I have said it before
    int i = 0;
    int answer = FALSE;
    while(i < turnMoves(game,currentTurn(game))) {
        if (pastMove(game, currentTurn(game), i).action == SAY_DUO) {
            answer = TRUE;
        }
        i++;
    }
    if (length == 2 && answer == FALSE) {
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
    int isValid = FALSE;
    int length = handCardCount(game);
    //Checking if I have said it before
    int i = 0;
    int answer = FALSE;
    while(i < turnMoves(game,currentTurn(game))) {
        if (pastMove(game, currentTurn(game), i).action == SAY_TRIO) {
            answer = TRUE;
        }
        i++;
    }
    if (length == 3 && answer == FALSE) {
        isValid = TRUE;
    }
    return isValid;
}

static int doIHaveACardToPlay(Game game, Card topCard) {
    int answer = FALSE;
    if (findMatchingCardSuit(game,cardSuit(topCard)) != NOT_FOUND) {
        answer = TRUE;
    } else if (findMatchingCardColor(game,cardColor(topCard)) != NOT_FOUND) {
        answer = TRUE;
    } else if (findMatchingCardValue(game,cardValue(topCard)) != NOT_FOUND) {
        answer = TRUE;
    }
    return answer;
}
//Check if I have played a card before in the current turn.
static int didIPlayCard(Game game){
    int answer = FALSE;
    int i = 0;
    int thisTurn = currentTurn(game);
    int moveInThisTurn = turnMoves(game,currentTurn(game));
    while(i < moveInThisTurn && answer == FALSE) {
        if(pastMove(game, thisTurn, i).action == PLAY_CARD) {
            answer = TRUE;
        }
        i++;
    }
    return answer;
}

static int didIDrawCard(Game game){
    int answer = FALSE;
    int i = 0;
    int thisTurn = currentTurn(game);
    int moveInThisTurn = turnMoves(game,currentTurn(game));
    while(i < moveInThisTurn && answer == FALSE) {
        if(pastMove(game, thisTurn, i).action == DRAW_CARD) {
            answer = TRUE;
        }
        i++;
    }
    return answer;
}

static color declareColor (Game game) {

    int playerNumber = 0;
    int handCardNumber = 0;
    int red = 0;
    int blue = 0;
    int green = 0;
    int yellow = 0;
    int purple = 0;
    playerNumber = currentPlayer(game);
    handCardNumber = playerCardCount(game,playerNumber);
    int i = 0;
    while(i<handCardNumber){
        Card curr = handCard(game,i);
        if(cardColor(curr) == RED){
            red++;
        } else if(cardColor(curr) == BLUE){
            blue++;
        }
        i++;
    }
    return 0;
}

static color previouslyDeclaredColor (Game game) {
    int previousTurn = currentTurn(game) -1;
    int move = turnMoves(game, previousTurn);
    int i = 0;
    color old = cardColor(topDiscard(game));
    playerMove lastMove;
    while (i<move && lastMove.action != PLAY_CARD) {
        lastMove= pastMove(game, previousTurn, i);
        i++;
    }
    color new = lastMove.nextColor;
    if (new != BLUE && new != RED && new!= PURPLE && new != GREEN && new != YELLOW) {
        new=old;
    }
    return new;
}

