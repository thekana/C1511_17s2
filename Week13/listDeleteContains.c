//Delete the contained value in a list;
//Quinn xia z5142018
//king z5176970
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void listDeleteContains (List l, int val) {
    int largest = val;
    int found = 0;
    Node curr = l->head;

    if (curr->value == val) {
        l->head = curr->next;
        free(curr);
    } else {
        while (curr->next != NULL && found == 0) {
            if(curr->next->value == val) {
                Node delete = curr->next;
                curr->next = curr->next->next;
                free(delete);
                found = 1;
            }
            if (found == 0) {
                curr = curr->next;
            }
        }
    }
}
