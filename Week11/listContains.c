#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int listContains (List l, int val) {
    int answer = FALSE;
    Node curr = l->head;
    while (curr != NULL) {
        if(curr->value == val) {
            answer = TRUE;
        }
        curr = curr->next;
    }
    return answer;
}


