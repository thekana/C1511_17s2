//List get middle
// King z5176970
// Quinn z5142018
//Zain F09A 2017-10-13

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int listGetLength(List l) {

    Node curr = l->head;
    int length = 0;
    while(curr != NULL){
        length++;
        curr = curr->next;
    }
    return length;
}

int listGetMiddle (List l) {
    Node curr = l->head;
    int middle = listGetLength(l) / 2;
    int result=0;
    int i =0;
    while(curr != NULL) {
        if(i==middle) {
            result = curr->value;
        }
        curr=curr->next;
        i++;
    }
    return result;
}


