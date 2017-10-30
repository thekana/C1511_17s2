//Quinn xia z5142018
//king z5176970
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int listFindLargest (List l){
    Node curr = l->head;
    int largest = 0;
    while(curr != NULL) {
        if (curr->value > largest) {
            largest = curr->value;
        }
        curr = curr->next;
    }
    return largest;
}
void listDeleteLargest (List l) {
    int largest = listFindLargest(l);
    int found = 0;
    Node curr = l->head;

    if (curr->value == largest) {
        l->head = curr->next;
        free(curr);
    } else {
        while (curr->next != NULL && found == 0) {
            if(curr->next->value == largest) {
                Node del = curr->next;
                curr->next = curr->next->next;
                free(del);
                found = 1;
            }
            if (found == 0) {
                curr = curr->next;
            }
        }
    }
}
