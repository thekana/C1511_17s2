//List count favourite
// King z5176970
// Quinn z5142018
//Zain F09A 2017-10-13

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int listCountFavourite (List l) {
    Node curr = l->head;
    int counter = 0;
    while (curr != NULL) {
        if(curr->value%17==0) {
            counter++;
        }
        curr=curr->next;
    }
    return counter;
}
