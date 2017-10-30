// An initial A.I. player for Final Card-Down.
//
// By King z5176970,
//    Quinn z5142018
//
// Written on 2017-10-??
// Tutor (dayHH-lab)

#include "Game.h"
#include "player.h"
#include "Card.h"

#define NOT_FOUND -1

// Find a card in the player's hand that matches the specified color,
// if such a card exists.
// Returns the card index, or NOT_FOUND if no matching card was found.
static int findMatchingCardColor (Game game, color color);
static int findMatchingCardSuit (Game game, suit suit);
static int findMatchingCardValue (Game game, value value);

// Do two cards match on either value, color, or suit?
// Returns TRUE if they match any of the above features, and
// FALSE if they don't match on any of the above features.
static int doCardsMatch (Card first, Card second);

// Determine whether the player can currently draw a card.
// If they can't draw a card, they should probably end their turn.
static int canDrawCard (Game game);


// Might need this.
static int canEndTurn (Game game);

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
    //At the start, say UNO/DUO/TRIO
    if(shouldSayUNO(game)){
        move.action = SAY_UNO;
    } else if(shouldSayDUO(game)) {
        move.action = SAY_DUO;
    } else if(shouldSayTRIO(game)) {
        move.action = SAY_TRIO;
    } else {
        // Set our move to be END_TURN, and check whether that's
        // a valid move -- if it is, then just end our turn (for now).
        move.action = END_TURN;
    }

    // If it's not valid to end turn, we must need to make
    // some other action...
    //
    // What actions are valid at this point?
    if (!isValidMove(game, move)) {

        // Retrieve the top card from the discard pile
        Card topCard = topDiscard(game);
        //***Need to check for declare draw 2 and other special cards for now just simple matching
        // Checking if we have anything on hand that matches
        int index = NOT_FOUND;
        if(findMatchingCardColor(game,cardColor(topCard)) != NOT_FOUND) {
            index = findMatchingCardColor(game,cardColor(topCard));
            move.action = PLAY_CARD;
            move.card = handCard(game,index);
        } else if (findMatchingCardSuit(game,cardSuit(topCard)) != NOT_FOUND) {
            index = findMatchingCardSuit(game,cardSuit(topCard));
            move.action = PLAY_CARD;
            move.card = handCard(game,index);
        } else if (findMatchingCardValue(game,cardValue(topCard)) != NOT_FOUND) {
            index = findMatchingCardValue(game,cardValue(topDiscard(game)));
            move.action = PLAY_CARD;
            move.card = handCard(game,index);
        } else {
            move.action = DRAW_CARD;
        }
        /*if(index==-1){
        // Valid actions include:
        //   - play a card,
        //   - draw a card,
        //   - call the previous play out for forgetting to SAY_UNO etc.
        //
        // The easiest thing here is to draw a card, since we don't
        // need to try to work out if we have a valid card, etc.
        move.action = DRAW_CARD;
        }*/
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
    return index; // TODO: replace this with your code.
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
    return index; // TODO: replace this with your code.
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
    return index; // TODO: replace this with your code.
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
    return match; // TODO: replace this with your code.
}

// Determine whether the player can currently draw a card.
// If they can't draw a card, they should probably end their turn.
static int canDrawCard (Game game) {
    playerMove move;
    move.action = DRAW_CARD;
    int isValid = FALSE;
    if(isValidMove(game,move)){
        isValid = TRUE;
    }
    return isValid; // TODO: replace this with your code.
}
/*static int canEndTurn (Game game) {
    int turn = 0;
    int tMoves = 0;
    int i = 0;
    int end = TRUE;

    turn = numTurns(game);
    tMoves= turnMoves(game,turn);
    while(i<tMoves && end == FALSE){
        if((pastMove(game,turn,i)).action !=PLAY_CARD ||(pastMove(game,turn,i)).action !=DRAW_CARD){
            i++;
            end == FALSE;
        }else{
            i++;
        }
    }


    return end; // TODO: replace this with your code.
}
*/
// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_UNO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayUNO (Game game) {
    int turn = 0;
    int tMoves = 0;
    turn = numTurns(game);
    tMoves= turnMoves(game,turn);
    int say = FALSE;
    if(tMoves == 0){
    }
    playerMove move1;
    move1 = pastMove(game,turn,tMoves);

    if(move1.action ==PLAY_CARD){
        if(handCardCount(game)==1){
            say = TRUE;
        }
    }
    return say; // TODO: replace this with your code.
}

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_DUO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayDUO (Game game) {
    int turn = 0;
    int tMoves = 0;
    turn = numTurns(game);
    tMoves= turnMoves(game,turn);
    int say = FALSE;
    if(tMoves == 0){
    }
    playerMove move1;
    move1 = pastMove(game,turn,tMoves);

    if(move1.action ==PLAY_CARD){
        if(handCardCount(game)==2){
            say = TRUE;
        }
    }
    return say; // TODO: replace this with your code.
}

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_TRIO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayDUO (Game game) {
    int turn = 0;
    int tMoves = 0;
    turn = numTurns(game);
    tMoves= turnMoves(game,turn);
    int say = FALSE;
    if(tMoves == 0){
    }
    playerMove move1;
    move1 = pastMove(game,turn,tMoves);

    if(move1.action ==PLAY_CARD){
        if(handCardCount(game)==3){
            say = TRUE;
        }
    }
    return say; // TODO: replace this with your code.
}

