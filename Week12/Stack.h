// COMP1511 17s2 -- a Stack ADT
// Maintains a stack, a last-in-first-out structure.
//
// 2011-04-01   Richard Buckland <richardb@cse.unsw.edu.au>
// 2017-09-18   Jashank Jeremy <{jashankj,z5017851}@cse.unsw.edu.au>
// licensed under Creative Commons

#ifndef _STACK_H_
#define _STACK_H_

// Will determine how big stackData will be.
#define STACK_SIZE 1000

// An ADT, at last!
typedef struct _stack *Stack;

// create a new Stack
Stack newStack (void);

// destroy a stack
void destroyStack (Stack s);

// this is our add function, 'char elt' = character element.
void stackPush (Stack s, char elt);

// returns the topmost element
char stackTop (Stack s);

// this is our pop function -- takes an element off.
char stackPop (Stack s);

#endif // !defined(_STACK_H_)
