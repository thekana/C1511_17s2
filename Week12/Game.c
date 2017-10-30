// Creates the game final card down
// Created by: ... (z0000000)
//             ... (z0000000)
//             Jack Gifford (z5160408)
//             Jasvir Singh Boparoy (z5165068)
// Lab: (F09A)(fri10-sitar)
// Tutor: Zain Afzal
// Lab Assistant: Anna Zhang
// Created 2017-09-27 - 2017-10-27


// Library Definitions
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

// File Definitions
#include "Game.h"
#include "Card.h"

// #DEFINES
#define PLAYER_COUNT 4

// Structures Used Internally
typedef struct _list *List;
typedef struct _node *Node;

typedef struct _list {
    Node head;
} list;

typedef struct _node {
    Node next;
    Card value;
} node;

typedef struct _player {
    List hand;
    int hasDrawnCard;
    int hasPlayedCard;

} player;

typedef struct _game {
    int initialDeckLength;
    Card *initialDeck;
    
    List pickUpPile;
    List discardPile;

    player players[PLAYER_COUNT];

    direction direction;
    int currentPlayer;
    int currentTurn;
    int skipped;
    color currentColor;
    value currentValue;
    suit currentSuit;

} game;

// Helper Prototypes

static int validateClaimCard (player currPlayer); 
// Helpers for checking
static int isCardValid(Game, Card);
static int validateCallout(player);
// Helpers for shifting cards

static void removeCard (List l, Card val);
static int assertCard(Card c1, Card c2);


// Helpers for playMove (Game game , playerMove move)
static void playCardEventHandler(Game g, playerMove moveAction);

static void HandleAdvance(Game g);
static void HandleDrawTwo(Game g);
static void HandleContinue(Game g);
static void HandleBackwards(Game g);
static void HandleDeclare(Game g, color newColor);


// Helpers for construction of a newGame
static void generatePlayers (Game game);
static void generatePlayersStartingHands(Game game);
static void setInitialStarts(Game game);

// Helpers for a linked list
static List newList (void);
static Node newNode(Card value);
static int getLength (List l);
static Card getNthElement (List l, int n);
static void insertNthElement (List l, int n, Card value);
static void removeNthElement (List l, int n);

// Create a new game engine.
//
// This creates a game with a deck of the given size
// and the value, color, and suit of each card to be taken from
// each of the arrays in order.
//
// Your game will always have 4 players. Each player starts with a hand
// of 7 cards. The first card from the deck is given to player 0, the
// second to player 1, the third to player 2, the fourth to player 3,
// the fifth to player 0, and so on until each player has 7 cards.
Game newGame(int deckSize, value values[], color colors[], suit suits[]) {
    Game newGame = calloc(1, sizeof(game));

    // This is intentional, we want an array of pointers!
    newGame->initialDeck = calloc(deckSize, sizeof(Card *));

    if (newGame->initialDeck == NULL) {
        errx(EXIT_FAILURE, "Failed to create the deck!");
    }
    // Perform null pointers check

    int i = 0;
    while (i < deckSize) {
        newGame->initialDeck[i] = newCard(values[i], colors[i], suits[i]);
        i++;
    }

    newGame->initialDeckLength = deckSize;
    newGame->discardPile = newList();
    newGame->pickUpPile = newList();
    newGame->skipped = FALSE;
    generatePlayers(newGame);
    setInitialStarts(newGame); 
    
    return newGame;
}


static void setInitialStarts(Game game) {

    Card startingCard = getNthElement(game->pickUpPile, 0);
    removeCard(game->pickUpPile, startingCard);

    insertNthElement(game->discardPile, 0, startingCard);

    game->currentColor = cardColor(startingCard);
    game->currentSuit = cardSuit(startingCard);
    game->currentValue = cardValue(startingCard);

}

// Generates a player struct with an empty hand
static void generatePlayers (Game game) {
    int i = 0;

    while (i < PLAYER_COUNT) {
        player new = {
            .hand = newList(),
            .hasDrawnCard = FALSE,
            .hasPlayedCard = FALSE
        };

        game->players[i] = new;

        i++;
    }

    generatePlayersStartingHands(game);
}


static void generatePlayersStartingHands(Game game) {
    int currentRound = 0;

    while (currentRound < 7) {
        insertNthElement(game->players[0].hand, 0, game->initialDeck[currentRound * 4]);
        insertNthElement(game->players[1].hand, 0, game->initialDeck[(currentRound * 4) + 1]);
        insertNthElement(game->players[2].hand, 0, game->initialDeck[(currentRound * 4) + 2]);
        insertNthElement(game->players[3].hand, 0, game->initialDeck[(currentRound * 4) + 3]);

        currentRound++;
    }

    int i = game->initialDeckLength - 1;

    while (i >= 28) {
        insertNthElement(game->pickUpPile, 0, game->initialDeck[i]);
        i--;
    }

}

// Destroy an existing game.
void destroyGame(Game game) {
    free(game);
}

// Get the number of cards that were in the initial deck.
int numCards(Game game) {
    return game->initialDeckLength;
}

// Get the number of cards in the initial deck of a particular suit.
int numOfSuit(Game game, suit suit) {
    int i = 0;
    int counter = 0;

    while (i < game->initialDeckLength) {
        if (cardSuit(game->initialDeck[i]) == suit) {
            counter++;
        }

        i++;
    }

    return counter;
}

// Get the number of cards in the initial deck of a particular color.
int numOfColor(Game game, color color) {
    int i = 0;
    int count = 0;

    while (i < game->initialDeckLength) {
        if(cardColor(game->initialDeck[i]) == color) {
            count++;
        }
        i++;
    }

    return count;
}

// Get the number of cards in the initial deck of a particular value.
int numOfValue(Game game, value value) {
    int i = 0;
    int counter = 0;

    while (i < game->initialDeckLength) {
        if (cardValue(game->initialDeck[i]) == value) {
            counter++;
        }

        i++;
    }

    return counter;
}

// Get the number of the player whose turn it is.
int currentPlayer(Game game) {
    return game->currentPlayer;
}

// Get the current turn number.
//
// The turn number increases after a player ends their turn.
// The turn number should start at 0 once the game has started.
int currentTurn(Game game) {
    return game->currentTurn;
}

// Get the number of points for a given player.
// Player should be between 0 and 3.
//
// This should _not_ be called by a player.
int playerPoints(Game game, int player) {
    return playerCardCount(game, player);
}

// Get the current direction of play.
direction playDirection(Game game) {
    return game->direction;
}

// This function returns the number of turns that have occurred in the
// game so far including the current turn.
// When using either the turnMoves or pastMove function,
// the turn number should be less than the number of moves that this
// function returns.
// (i.e. on turn 0 of the game, this should return 1, as there has been
// 1 turn so far including the current turn; if you called pastMove you
// would need to call it on turn 0, as this is the only possible value
// less than 1.)
int numTurns(Game game) {
    return currentTurn(game) + 1;
}

// Get the number of moves that happened on a turn.
//
// A turn may consist of multiple moves such as drawing cards,
// playing cards, and ending the turn.
int turnMoves(Game game, int turn) {

    return 0;

}

// Look at a previous move from a specified turn.
playerMove pastMove(Game game, int turn, int move) {
    playerMove move1 = {
        .action = DRAW_CARD,
        .nextColor = RED,
        .card = newCard(ZERO, RED, HEARTS)
    };

    return move1;
}

// Get the number of cards in a given player's hand.
int playerCardCount(Game game, int player) {
    int count;
    if (player >= 0 && player <= PLAYER_COUNT) {
        count = getLength(game->players[player].hand);
    } else {
        errx(EXIT_FAILURE, "Player provided was out of range!\n");
    }

    return count;
}

// Get the number of cards in the current player's hand.
int handCardCount(Game game)  {
    return getLength(game->players[game->currentPlayer].hand);
}

// View a card from the current player's own hand.
//
// The player should not need to free() this card,
// so you should not allocate or clone an existing card
// but give a reference to an existing card.
Card handCard(Game game, int card) {\
    if (card -1 > playerCardCount(game, game->currentPlayer)) {
        errx(EXIT_FAILURE, "Supplied card was out of range\n");
    }

    List l = game->players[game->currentPlayer].hand;
    return getNthElement (l, card);
}

// Check if a given move is valid.
//
// If the last player played a 2 (DRAW_TWO),
// the next player must either play a 2
// or draw 2 cards.
// Otherwise, the player must play a card that is either a ZERO
// or that has the same color, value, or suit as the card on the top
// of the discard pile.
//
// If the player plays an ADVANCE, the next player's turn is skipped.
// If the player plays a BACKWARDS, the direction of play is reversed.
// If the player plays a CONTINUE, they may play another card.
// If the player plays a DECLARE, they must also state which color
// the next player's discarded card should be.
//
// A player can only play cards from their hand.
// A player may choose to draw a card instead of discarding a card.
// A player must draw a card if they are unable to discard a card.
//
// This check should verify that:
// * The card being played is in the player's hand
// * The player has played at least one card before finishing their turn,
//   unless a draw-two was played, in which case the player may not
//   play a card, and instead must draw the appropriate number of cards.
int isValidMove(Game game, playerMove move) {
    
    player currPlayer = game->players[currentPlayer(game)];
    Card previousCard = topDiscard(game);

    int isValidMove = FALSE;

    if (move.action == PLAY_CARD) {
        if (currPlayer.hasPlayedCard == FALSE && currPlayer.hasDrawnCard == FALSE) {
            if (isCardValid(game, move.card)) {
                isValidMove = TRUE;
            }    
        } 
       
        // We need additonal checks to make sure the player isn't taking advantage of prev player continue, or
        // spamming
        else if (isCardValid(game, move.card) && cardValue(previousCard) == CONTINUE) {
            isValidMove = TRUE;
        }
        
    } else if (move.action == DRAW_CARD) {
        if (currPlayer.hasPlayedCard == FALSE && currPlayer.hasDrawnCard == FALSE) {
            // In this case the user has not made a move yet. So it's valid
            isValidMove = TRUE;
        }  
       
        // This logic isn't quite right, as it lets a player spam draw card
        else if (cardValue(previousCard) == DRAW_TWO) {
            isValidMove = TRUE;
        }
   
    } else if (move.action == SAY_UNO || move.action == SAY_DUO || move.action == SAY_TRIO) {
        if ( validateCallout(currPlayer)) {
            isValidMove = TRUE;
        }

        else if (validateClaimCard(currPlayer)) {
            isValidMove = TRUE;
        }

    } else if (move.action == END_TURN) {
        if (currPlayer.hasPlayedCard || currPlayer.hasDrawnCard) {
            isValidMove = TRUE;
        }
    }

    return isValidMove;
}

static int validateClaimCard (player currPlayer) {
    int isClaimCard = FALSE;
    
    if (currPlayer.hasPlayedCard == TRUE && currPlayer.hasDrawnCard == FALSE) {
        isClaimCard = TRUE;
    }
    
    return isClaimCard;
}

static int validateCallout (player currPlayer) {
    int isCallout = FALSE;
    
    if (currPlayer.hasPlayedCard == FALSE && currPlayer.hasDrawnCard == FALSE) {
        isCallout = TRUE;
    }
    
    return isCallout;
}

// For a card to be valid it must match either the color, value, or suit
// Are there any exceptions?
static int isCardValid(Game game, Card cardToValidate) {
    int isValid = FALSE;

    if (cardValue(cardToValidate) == game->currentValue) {
        isValid = TRUE;
    }

    if (cardSuit(cardToValidate) == game->currentSuit) {
        isValid = TRUE;
    }

    if (cardColor(cardToValidate) == game->currentColor) {
        isValid = TRUE;
    }
    
    return isValid;

}

static void SetCurrentPlayer(Game game) {
    if (game->direction == CLOCKWISE) {
        game->currentPlayer++;
    } else {
        game->currentPlayer--;
    }

    if (game->currentPlayer > 3) {
        game->currentPlayer = 0;
    } else if (game->currentPlayer < 0) {
        game->currentPlayer = 3;
    }
}

static void playCardEventHandler (Game game, playerMove moveAction) {


    // Step remove from player hand
    int player = game->currentPlayer;
    
    List playerHand = game->players[player].hand;


    removeCard (playerHand, moveAction.card);
    insertNthElement(game->discardPile, 0, moveAction.card);

    value currentValue = cardValue(moveAction.card);

    // In all cases the new states should be set
    game->currentColor = cardColor(moveAction.card);
    game->currentSuit = cardSuit(moveAction.card);
    game->currentValue = cardValue(moveAction.card);
    
    if (currentValue == DRAW_TWO) {
        HandleDrawTwo(game);
    } else if (currentValue == ADVANCE) {
        HandleAdvance(game);
    } else if (currentValue == BACKWARDS) {
        HandleBackwards(game);
    } else if (currentValue == CONTINUE) {
        HandleContinue(game);
    } else if (currentValue == DECLARE) {
        HandleDeclare(game, moveAction.nextColor);
    }
}

static void HandleDrawTwo(Game game) {
    // TODO: Determine, and assign this statement to the next player
    
    game->players[currentPlayer(game)];
}

static void HandleAdvance (Game game) {
    game->skipped = TRUE;
    //Maybe return a status code?
}

static void HandleBackwards (Game game) {
    game->direction = !game->direction;
}

static void HandleContinue (Game game) {
    game->players[currentPlayer(game)].hasPlayedCard = FALSE;
}

static void HandleDeclare (Game game, color newColor) {
    game->currentColor = newColor;
}

// Play the given action for the current player
//
// If the player makes the END_TURN move, their turn ends,
// and it becomes the turn of the next player.
//
// This should _not_ be called by the player AI.
void playMove(Game game, playerMove move){
    // If this passes we can be sure player has made a valid move
    if (isValidMove(game, move) == FALSE) {
        errx(EXIT_FAILURE, "Invalid move submitted!\n");
    }
    
    if (move.action == PLAY_CARD) {
        playCardEventHandler(game, move);
        game->players[currentPlayer(game)].hasPlayedCard = TRUE;

    } else if (move.action == DRAW_CARD) {
        Card drawCard = getNthElement(game->pickUpPile, 0);
        removeCard(game->pickUpPile, drawCard);
        insertNthElement(game->players[currentPlayer(game)].hand, 0, drawCard);
        game->players[currentPlayer(game)].hasDrawnCard = TRUE;
    
    } else if (move.action == SAY_UNO) {

    } else if (move.action == SAY_DUO) {

    } else if (move.action == SAY_TRIO) {

    } else if (move.action == END_TURN) {
        //Reset the players turn counter to = 1
        game->players[currentPlayer(game)].hasPlayedCard = FALSE;
        game->players[currentPlayer(game)].hasDrawnCard = FALSE;
        
        if (game->skipped) {
            game->skipped = FALSE;
            SetCurrentPlayer(game);
        }
        // Move onto the next player
        SetCurrentPlayer(game);
    }
}

// Check the game winner.
//
// Returns NOT_FINISHED if the game has not yet finished,
// 0-3, representing which player has won the game, or
// NO_WINNER if the game has ended but there was no winner.
int gameWinner(Game game) {
    int winner = NOT_FINISHED;

    //NO_WINNER is called when there are no cards left to draw, and the discard pile has only one card in it.

    if (getLength(game->pickUpPile) == 0 && getLength(game->discardPile) == 1) {
        winner = NO_WINNER;
    } else {
        // There might be a bug here, but more likely I think my test 
        // was just consuming this wrong
        
        int i = 0;
        while (i < 4) {
            List playerList = game->players[i].hand;
            if (getLength(playerList) == 0) {
                winner = i;
            }

            i++;
        } 
    }

    return winner;
}

// Get the card that is on the top of the discard pile.
Card topDiscard(Game game) {
    if (game->discardPile->head == NULL) {
        errx(EXIT_FAILURE, "No cards on the discard pile");
    }

    return game->discardPile->head->value;
}

static List newList (void) {
    List new = calloc(1, sizeof(list));

    if (new == NULL) {
        errx(EXIT_FAILURE, "Failed to create the list\n");
    }

    return new;
}

static int getLength (List l) {
    int length = 0;

    Node curr = l->head;

    while (curr != NULL) {
        curr = curr->next;
        length++;
    }


    return length;
}

static Card getNthElement (List l, int n) {
    int i = 0;
    Node curr = l->head;

    while (i < n) {
        curr = curr->next;

        i++;
    }

    return curr->value;

}

// Warning!!! This does not free anything, you need to keep track of the returned node
// Otherwise you have a memory leak!
static void removeNthElement (List l, int n) {
    if (l->head == NULL) {

    } else if (n == 0) {
        Node newStart = l->head->next;
        free(l->head);
        l->head = newStart;
    } else {
        Node curr = l->head;

        int i = 0;

        while (i < n-1) {
            curr = curr->next;
            i++;
        }

        //We might not want to free this
        Node nodeToBeFreed = curr->next;
        curr->next = curr->next->next;
        free(nodeToBeFreed);
    }
}


// WARNING!!! This doesn't free anything. Make sure the card is added to a new list before it leaves scope
// otherwise you've lost a card and we're fucked
static void removeCard (List l, Card val) {
    if (l->head != NULL) {
        if (assertCard(l->head->value, val)) {
            Node temp = l->head->next;
            
            l->head = temp; 
        } else {
            Node curr = l->head;
            Node next = curr->next;
            while (curr != NULL && curr->next != NULL) {
                if (assertCard(next->value, val)) {
                    printf("removed card\n");
                     curr->next = next->next;
                }
                
                curr = next;
                next = next->next;
            }
        }
    }
}

static int assertCard (Card c1, Card c2) {
    int equality = TRUE;

    if (cardValue(c1) != cardValue(c2)) {
        equality = FALSE;
    }

    if (cardSuit(c1) != cardSuit(c2)) {
        equality = FALSE;
    }

    if (cardColor(c1) != cardColor(c2)) {
        equality = FALSE;
    }

    return equality;
}

static void insertNthElement (List l, int n, Card val) {
    if (l->head == NULL) {
        l->head = newNode(val);

    } else if (n == 0) {
        Node start = l->head;
        Node new = newNode(val);
        l->head = new;
        new->next = start;
    } else {

        Node curr = l->head;

        int i = 0;

        while (i < n -1) {
            curr = curr->next;
            i++;
        }

        Node new = newNode(val);

        new->next = curr->next;
        curr->next = new;

    }
}

static Node newNode (Card value) {
    Node new = calloc(1, sizeof(node));

    if (new == NULL) {
        errx(EXIT_FAILURE, "failed to create a new node\n");
    }

    new->value = value;
    new->next = NULL;

    return new;
}

// This can probably be removed. It's only here because it needs to know about the implementation
void displayList (Game g, int player) {
    List l = g->players[player].hand;
    
    Node curr = l->head;

    while (curr != NULL) {
        printf("-> %d", cardValue(curr->value));
        curr = curr->next;
    }

    printf("-> x\n");
}