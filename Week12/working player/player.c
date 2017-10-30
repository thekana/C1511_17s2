#include<stdlib.h>
#include<stdio.h>
#include"player.h"
#include "Game.h"
#include "Card.h"
#define NOT_FOUND -1
// Find a card in the player's hand that matches the specified color,
// if such a card exists.
// Returns the card index, or NOT_FOUND if no matching card was found.
static int findMatchingCard(Game game, Card top);

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
static int DidIfindValidCard (Game game, Card top);
static int LookOverMyLastMove(Game game);
static int CanIPlayCard(Game game);

//Check the handcount for previous player and check whether they have said the corrsbonding action then call the action out by SAY_XXX;



static int GetPreviousHandCount(Game game);
static int CanICallThemOut(Game game);
//Get the valid card from current player's hand
// This function is to be implemented by the AI.

// It will be called when the player can take an action on their turn.
// The function is called repeatedly until they make the action
// END_TURN.
// If the player's turn is skipped, this funciton is not called for that
// player.
playerMove decideMove(Game game) {
    // Start out by making a move struct, to say what our move is.
    playerMove move;
    int PreviousCount = GetPreviousHandCount(game);
    //================================================================================================
    Card top = topDiscard(game);
    
    move.action = END_TURN;
    
    // Set our move to be END_TURN, and check whether that's
    // a valid move -- if it is, then just end our turn (for now).
    // ig .If the previous number is 3 which is skeptical!!!!!!
    
    if(!isValidMove(game, move)){
        if(CanIPlayCard(game) == TRUE){
            if(DidIfindValidCard (game,top) == TRUE){     
                int index = findMatchingCard (game, top);
                Card toPlay = handCard(game, index);
                move.action = PLAY_CARD;
                move.card = toPlay;
                
            }
        }
    }
    if(!isValidMove(game, move)){
        if(PreviousCount == 3){
            //Can I call them out now at this stage????
            if (CanICallThemOut(game) == TRUE){
                move.action = SAY_TRIO;
            }   
        }else if(PreviousCount == 2){
            if (CanICallThemOut(game) == TRUE){
                move.action = SAY_DUO;
            }
        }else if(PreviousCount == 1){
            if (CanICallThemOut(game) == TRUE){
                move.action = SAY_UNO;
            }
        }
    }
    
    
    
    
    if(handCardCount(game) == 1){
        if(CanIPlayCard(game) == FALSE){       
            if(LookOverMyLastMove(game) == TRUE){
                if(shouldSayUNO (game) == TRUE){
                    move.action = SAY_UNO;
                }
            }
        }
    }else if(handCardCount(game) == 2){
        if(CanIPlayCard(game) == FALSE){       
            if(LookOverMyLastMove(game) == TRUE){
                if(shouldSayDUO (game) == TRUE){
                    //move.action = SAY_DUO;
                }
            }
        }
    }else if(handCardCount(game) == 3){
        if(CanIPlayCard(game) == FALSE){
            if(LookOverMyLastMove(game) == TRUE){
                if(shouldSayTRIO (game) == TRUE){
                    move.action = SAY_TRIO;
                }
            }
        }
    }
    
    // If it's not valid to end turn, we must need to make
    // some other action...
    //
    // What actions are valid at this point?
    if(!isValidMove(game, move)){
        move.action = DRAW_CARD;
        
    }
    
    // Valid actions include:
    //   - play a card,
    //   - draw a card,
    //   - call the previous play out for forgetting to SAY_UNO etc.
    //
    // The easiest thing here is to draw a card, since we don't
    // need to try to work out if we have a valid card, etc.
    return move;
}
    
  
// Find a card in the player's hand that matches the specified color,
// if such a card exists.
// Returns the card index, or NOT_FOUND if no matching card was found.
static int findMatchingCard (Game game, Card top) {
    int index = 0;
    int i = 0;
    int handCount = handCardCount(game);
    while(i < handCount){
        if(doCardsMatch (handCard(game, i), top) ==  TRUE ){
            index = i;
        }
        i++;
    }
    return index; 
    // TODO: replace this with your code.
}

// Do two cards match on either value, color, or suit?
// Returns TRUE if they match any of the above features, and
// FALSE if they don't match on any of the above features.
static int doCardsMatch (Card first, Card second) {
    int result = FALSE;
    if(cardValue(first) == cardValue(second)){
        result = TRUE;
    }else if(cardColor(first) == cardColor(second)){
        result = TRUE;
    }else if(cardSuit(first) == cardSuit(second)){
        result = TRUE;
    }
    return result; 
    // TODO: replace this with your code.
}

// Determine whether the player can currently draw a card.
// If they can't draw a card, they should probably end their turn.
static int canDrawCard (Game game) {
    int result = FALSE;
    playerMove valid;
    valid.action = DRAW_CARD;
    //Becasue is valid move function will verify the situations eg. DRAW_TWO was played? 
    if(isValidMove(game , valid)){
        result = TRUE;
    }
    return result; // TODO: replace this with your code.
}

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_UNO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayUNO (Game game) {
    int result = FALSE;
    int length = playerCardCount(game, currentPlayer(game));
    if(length == 1 && LookOverMyLastMove(game) == TRUE){
        result = TRUE;
    }
    return result; // TODO: replace this with your code.
}

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_DUO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayDUO (Game game) {
    int result = FALSE;
    int length = playerCardCount(game, currentPlayer(game));
    if(length == 2 && LookOverMyLastMove(game) == TRUE){
        result = TRUE;
    }
    return result; 
    //TODO: replace this with your code.
}

// Determine whether the current player should SAY_UNO.
// There are two different situations where it could be a
// valid move to SAY_TRIO.
// For now, just deal with the simple situation: "claim card".
// Note: there are several possible ways to determine this.
static int shouldSayTRIO (Game game) {
    int result = FALSE;
    int length = playerCardCount(game, currentPlayer(game));
    //LookOverfuntion helps me to determine whether i have said trio before in this turn 
    //return TRUE if i have 3 cards and have not said it, return false if have 3 cards but i have said.
    if(length == 3 && LookOverMyLastMove(game) == TRUE){
        result = TRUE;
    }
    return result; 
    // TODO: replace this with your code.
}
static int DidIfindValidCard (Game game, Card top){
    int i = 0;
    int result = FALSE;
    int handCount = handCardCount(game);
    while(i < handCount){
        if(doCardsMatch (handCard(game, i), top) ==  TRUE ){
            result = TRUE;
        }
        i++;
    }
    return result;    
}
static int LookOverMyLastMove(Game game){
    int i = 0;
    int result = TRUE;
    while(i < turnMoves(game, currentTurn(game))){
        if(pastMove(game, currentTurn(game), i).action == SAY_TRIO){
            result = FALSE;
        }else if(pastMove(game, currentTurn(game), i).action == SAY_DUO){
            result = FALSE;
        }else if(pastMove(game, currentTurn(game), i).action == SAY_UNO){
            result = FALSE;
        }
        i++;
    }
    return result;
}
static int CanIPlayCard(Game game){
    int i = 0;
    while(i < turnMoves(game, currentTurn(game))){
        if(pastMove(game, currentTurn(game), i).action == PLAY_CARD){
            return FALSE;
        }
        i++;
    }
    return TRUE;
}
static int GetPreviousHandCount(Game game){
    int HandCount = 0;
    if(playDirection(game) == CLOCKWISE){
        if(currentPlayer(game) == 0){
            HandCount = playerCardCount(game, 3);
        }else if(currentPlayer(game) == 1){
            HandCount = playerCardCount(game, 0);
        }else if(currentPlayer(game) == 2){
            HandCount = playerCardCount(game,1);
        }else if(currentPlayer(game) == 3){
            HandCount = playerCardCount(game,2);
        }
    
    }else if(playDirection(game) == ANTICLOCKWISE){
        if(currentPlayer(game) == 0){
            HandCount = playerCardCount(game, 1);
        }else if(currentPlayer(game) == 1){
            HandCount = playerCardCount(game, 2);
        }else if(currentPlayer(game) == 2){
            HandCount = playerCardCount(game,3);
        }else if(currentPlayer(game) == 3){
            HandCount = playerCardCount(game,0);
        }
    }
    return HandCount;
}
//Since the handcards for previous playe have been checked !!!!!!!!!!!!!!
//Check why they got this numbers of cards (Drawn? Played?)
static int CanICallThemOut(Game game){
    int i = 0;
    int result = TRUE;
    
    while (i < turnMoves(game, currentTurn(game)-1)){
        if(pastMove(game, currentTurn(game)-1, i).action == SAY_TRIO ||
            pastMove(game, currentTurn(game)-1, i).action == DRAW_CARD){
            result = FALSE;
        }
        i++;
    }
    i = 0;
    while (i < turnMoves(game, currentTurn(game)-1)){
        if(pastMove(game, currentTurn(game)-1, i).action == SAY_DUO ||
            pastMove(game, currentTurn(game)-1, i).action == DRAW_CARD){
           result = FALSE;
        }
        i++;
    }
    i = 0;
    while (i < turnMoves(game, currentTurn(game)-1)){
        if(pastMove(game, currentTurn(game)-1, i).action == SAY_UNO ||
            pastMove(game, currentTurn(game)-1, i).action == DRAW_CARD){
            result = FALSE;
        }
        i++;
    }
    return result;
}

