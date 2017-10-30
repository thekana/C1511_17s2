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
#define NOT_FOUND -1

// Find a card in the player's hand that matches
// if such a card exists.
// Returns the card index, or NOT_FOUND if no matching card was found
// Helper functions to find the index
static int findMatchingCardColor (Game game, color color);
static int findMatchingCardSuit (Game game, suit suit);
static int findMatchingCardValue (Game game, value value);
static int findMatchingCard(Game game, Card topCard);
static int findMatchingDeclaredCard(Game game, Card topCard, color declared);
static int findSpecialCard(Game game);
static int isSpecialCard(Card card);
static int doIHaveACardToPlay(Game game, Card topCard);
static int doIHaveAZeroCard(Game game);


//Helper functions to give the AI more knowledge of the current game state
static int didIPlayCard(Game game);
static int didIDrawCard(Game game);
static color declareColor(Game game);
static color previouslyDeclaredColor (Game game);
static int shouldICallOut(Game game);
static int previousHandCount(Game game);
static color whichIsLargest(int red, int blue, int green , int yellow, int purple);


// Do two cards match on either value, color, or suit?
// Returns TRUE if they match any of the above features, and
// FALSE if they don't match on any of the above features.
static int doCardsMatch (Card first, Card second);

// Determine whether the player can currently draw a card.
// If they can't draw a card, they should probably end their turn.
static int canDrawCard (Game game);

// Determine whether the current player should SAY_UNO.
static int shouldSayUNO (Game game);

// Determine whether the current player should SAY_DUO.
static int shouldSayDUO (Game game);

// Determine whether the current player should SAY_TRIO.
static int shouldSayTRIO (Game game);


// This function is to be implemented by the A.I.
// It will be called when the player can make an action on their turn.
playerMove decideMove(Game game) {
    // Start out by making a move struct, to say what our move is.
    playerMove move;
    move.action = END_TURN;
    // Retrieve the top card from the discard pile
    Card topCard = topDiscard(game);

    int lastCardCount = previousHandCount(game);

    // If it's not valid to end turn, we must need to make some other actions
    // Checking callouts
    if(!isValidMove(game, move)){
        if(lastCardCount == 3){
            if (shouldICallOut(game)){
                move.action = SAY_TRIO;
            }
        } else if(lastCardCount == 2){
            if (shouldICallOut(game)){
                move.action = SAY_DUO;
            }
        } else if(lastCardCount == 1){
            if (shouldICallOut(game)){
                move.action = SAY_UNO;
            }
        }
    }
    // Play card action
    // I do not want to search for anycard if I dont have a card to play
    // I do not want to search for a card if I have drawn a card.
    // This is here to prevent weird bug associated with continue.
    if(didIDrawCard(game) != TRUE) {
        if (!isValidMove(game, move) || cardValue(topCard) == CONTINUE) {
            // Checking if we have anything on hand that matches
            if(doIHaveACardToPlay(game,topCard)) {
                int index = NOT_FOUND;
                if(currentTurn(game) != 0 && cardValue(topCard) == DECLARE) {
                    // Because declared color may be different from the card color
                    // the color value needs to be replaced.
                    color declared = previouslyDeclaredColor(game);
                    index = findMatchingDeclaredCard(game, topCard, declared);
                } else {
                    index = findMatchingCard(game, topCard);
                }
                // Another checking station if I really have a card to play
                if(index == NOT_FOUND) {
                    move.action = DRAW_CARD;
                } else {
                    move.action = PLAY_CARD;
                    move.card = handCard(game,index);
                }
                // If the card I play is DECLARE, I need to choose a color
                if(cardValue(move.card) == DECLARE){
                    // declareColor will select the most common color we have on hand
                    move.nextColor = declareColor(game);
                }
                // We might have a card that is valid to play like ZERO which may not match the discard card value
                // We will check for that here.
            } else if(findSpecialCard(game)!= NOT_FOUND) {
                int index = findSpecialCard(game);
                Card curr = handCard(game,index);
                if(cardValue(curr)==DECLARE){
                    move.action = PLAY_CARD;
                    move.card = handCard(game,index);
                    move.nextColor = declareColor(game);
                } else {
                    move.action = PLAY_CARD;
                    move.card = handCard(game,index);
                }
            }
        }
    }

    // Saying stuff after we have played a card (NOT callout)
    if(handCardCount(game) == 3 && didIPlayCard(game)) {
        if(shouldSayTRIO(game)) {
            move.action = SAY_TRIO;
        }
    } else if (handCardCount(game) == 2 && didIPlayCard(game)) {
        if(shouldSayDUO(game)) {
            move.action = SAY_DUO;
        }
    } else if (handCardCount(game) == 1 && didIPlayCard(game)) {
        if(shouldSayUNO(game)) {
            move.action = SAY_UNO;
        }
    }

    // If all else invalid, we should draw a card
    if (!isValidMove(game, move)) {
        move.action = DRAW_CARD;
    }
    // Here to prevent the bot from drawing the card again if the top card is continue
    if(!doIHaveACardToPlay(game,topCard) && cardValue(topCard) == CONTINUE && didIPlayCard(game)) {
        move.action = END_TURN;
    }
    return move;
}


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

//Because the declared color may be different from the card color
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
static int shouldSayUNO (Game game) {
    int isValid = FALSE;
    int length = handCardCount(game);
    //Checking if I have said it before
    int i = 0;
    int answer = FALSE;
    int times = 0;
    while(i < turnMoves(game,currentTurn(game))) {
        if (pastMove(game, currentTurn(game), i).action == SAY_UNO) {
            times++;
        }
        i++;
    }
    if (times == 2) {
        answer = TRUE;
    } else if (times == 1) {
        answer = TRUE;
    }
    if (length == 1 && answer == FALSE) {
        isValid = TRUE;
    }
    return isValid;
}

// Determine whether the current player should SAY_DUO.
static int shouldSayDUO (Game game) {
    int isValid = FALSE;
    int length = handCardCount(game);
    //Checking if I have said it before
    int i = 0;
    int answer = FALSE;
    int times = 0;
    while(i < turnMoves(game,currentTurn(game))) {
        if (pastMove(game, currentTurn(game), i).action == SAY_DUO) {
            times++;
        }
        i++;
    }
    if (times == 2) {
        answer = TRUE;
    } else if (times == 1) {
        answer = TRUE;
    }
    if (length == 2 && answer == FALSE) {
        isValid = TRUE;
    }
    return isValid;
}

// Determine whether the current player should SAY_UNO.
static int shouldSayTRIO (Game game) {
    int isValid = FALSE;
    int length = handCardCount(game);
    //Checking if I have said it before
    int i = 0;
    int answer = FALSE;
    int times = 0;
    while(i < turnMoves(game,currentTurn(game))) {
        if (pastMove(game, currentTurn(game), i).action == SAY_TRIO) {
            times++;
        }
        i++;
    }
    if (times == 2) {
        answer = TRUE;
    } else if (times == 1) {
        answer = TRUE;
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
    color result = 0;
    while(i<handCardNumber){
        Card curr = handCard(game,i);
        if(cardColor(curr) == RED){
            red++;
        } else if(cardColor(curr) == BLUE){
            blue++;
        } else if(cardColor(curr) == GREEN){
            green++;
        } else if(cardColor(curr) == YELLOW){
            yellow++;
        } else if(cardColor(curr) == purple){
            purple++;
        }
        i++;
    }
    result = whichIsLargest(red, blue, green, yellow, purple);
    return result;
}


// Compare all the color and choose the largest one
static color whichIsLargest(int red, int blue, int green , int yellow, int purple) {

    color result = 0;
    if(red >= blue && red >= green && red >= yellow && red >= PURPLE){
        result = RED;
    }else if(blue >= red && blue >= green && blue >= yellow && blue >= purple){
        result = BLUE;
    }else if(green >= red && green >= blue && green >= yellow && green >= purple){
        result = GREEN;
    }else if(yellow >= red && yellow >= blue && yellow >= green && yellow >= purple){
        result = YELLOW;
    }else if(purple >= red && purple >= blue && purple >= green && purple >= yellow){
        result = PURPLE;
    }
    return result;
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

static int findSpecialCard(Game game){
    int playerNumber = 0;
    int handCardNumber =0;
    playerNumber = currentPlayer(game);
    handCardNumber = playerCardCount(game,playerNumber);
    int i = 0;
    int index = NOT_FOUND;
    int foundWorkingCard = FALSE;
    playerMove checker;
    while(i<handCardNumber && foundWorkingCard == FALSE){
        Card curr = handCard(game,i);
        if(isSpecialCard(curr)==TRUE){
            index = i;
            checker.action = PLAY_CARD;
            checker.card = handCard(game,index);
            if (isValidMove(game,checker)) {
                foundWorkingCard = TRUE;
            }
        }
        i++;
    }
    return index;
}

static int isSpecialCard(Card card){
    int i = FALSE;
    if(cardValue(card)==ZERO){
        i = TRUE;
    }else if(cardValue(card)==DRAW_TWO){
        i = TRUE;
    }else if(cardValue(card)==ADVANCE){
        i = TRUE;
    }else if(cardValue(card)==BACKWARDS){
        i = TRUE;
    }else if (cardValue(card)==CONTINUE){
        i = TRUE;
    }else if (cardValue(card)==DECLARE){
        i = TRUE;
    }
    return i;
}

static int doIHaveAZeroCard(Game game){
    int playerNumber = 0;
    int handCardNumber =0;
    playerNumber = currentPlayer(game);
    handCardNumber = playerCardCount(game,playerNumber);
    int foundZeroCard = FALSE;
    int i = 0;
    while(i<handCardNumber && foundZeroCard == FALSE){
        Card curr = handCard(game,i);
        if(cardValue(curr)==ZERO){
            foundZeroCard = TRUE;
        }
        i++;
    }
    return foundZeroCard;
}
// If they draw a card last turn, we should not call out. If not check if they claim card.
static int shouldICallOut(Game game){
    int i = 0;
    int result = TRUE;
    while (i < turnMoves(game, currentTurn(game)-1)) {
        if(pastMove(game, currentTurn(game)-1, i).action == DRAW_CARD) {
            result = FALSE;
        }
        i++;
    }
    i = 0;
    while (i < turnMoves(game, currentTurn(game)-1) && result == TRUE){
        if(pastMove(game, currentTurn(game)-1, i).action == SAY_TRIO){
            result = FALSE;
        }
        i++;
    }
    i = 0;
    while (i < turnMoves(game, currentTurn(game)-1) && result == TRUE){
        if(pastMove(game, currentTurn(game)-1, i).action == SAY_DUO){
            result = FALSE;
        }
        i++;
    }
    i = 0;
    while (i < turnMoves(game, currentTurn(game)-1) && result == TRUE){
        if(pastMove(game, currentTurn(game)-1, i).action == SAY_UNO){
            result = FALSE;
        }
        i++;
    }
    return result;
}
//Previous player hand count
static int previousHandCount(Game game){
    int handCount = 0;
    if(playDirection(game) == CLOCKWISE){
        if(cardValue(topDiscard(game)) == ADVANCE) {
            if(currentPlayer(game) == 0 || currentPlayer(game) == 1) {
                handCount = playerCardCount(game, currentPlayer(game) + 2);
            } else {
                handCount = playerCardCount(game, currentPlayer(game) - 2);
            }
        } else {
            if(currentPlayer(game) == 0){
                handCount = playerCardCount(game, 3);
            } else {
                handCount = playerCardCount(game, currentPlayer(game) - 1);
            }
        }
    } else {
        if(cardValue(topDiscard(game)) == ADVANCE) {
            if(currentPlayer(game) == 0 || currentPlayer(game) == 1) {
                handCount = playerCardCount(game, currentPlayer(game) + 2);
            } else {
                handCount = playerCardCount(game, currentPlayer(game) - 2);
            }
        } else {
            if(currentPlayer(game) == 3){
                handCount = playerCardCount(game, 0);
            } else {
                handCount = playerCardCount(game, currentPlayer(game) + 1);
            }
        }
    }
    return handCount;
}
