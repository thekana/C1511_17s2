// COMP1511 17s2 -- a Stack ADT
// Maintains a stack, a last-in-first-out structure.
//
// 2017-09-18   Jashank Jeremy <{jashankj,z5017851}@cse.unsw.edu.au>

#include <err.h>
#include <stdlib.h>

#include "Stack.h"

typedef struct _stack {
    char elements[STACK_SIZE];
    int size;
    int items;
} stack;

Stack newStack (void) {
    Stack s = calloc (1, sizeof (stack));
    if (s == NULL) {
        err (EXIT_FAILURE, "couldn't allocate memory");
    }
    s->size = STACK_SIZE;
    return s;
}

void destroyStack (Stack s) {
    free (s);
}

// this is our add function, 'char elt' = character element.
void stackPush (Stack s, char elt) {
    if (s == NULL) {
        errx (EXIT_FAILURE, "no stack?");
    }
    if (! (s->items < s->size)) {
        errx (EXIT_FAILURE, "pushing onto full stack");
    }

    s->items++;
    s->elements[s->items] = elt;
}

// returns the topmost element
char stackTop (Stack s) {
    if (s == NULL) {
        errx (EXIT_FAILURE, "no stack?");
    }

    return s->elements[s->items];
}

// this is our pop function:
// takes an element off, returns a new stack
char stackPop (Stack s) {
    if (s == NULL) {
        errx (EXIT_FAILURE, "no stack?");
    }
    if (s->items == 0) {
        errx (EXIT_FAILURE, "popping off empty stack");
    }

    char top = s->elements[s->items];
    s->elements[s->items] = 0;
    s->items--;

    return top;
}
