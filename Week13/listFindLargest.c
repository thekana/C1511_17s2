//Quinn xia z5142018
//king z5176970
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int listFindLargest (List l) {
    Node curr = l->head;
    int largest = 0;
    while (curr != NULL) {
        if (curr->value > largest) {
            largest = curr->value;
        }
        curr = curr->next;
    }
    return largest;
}
