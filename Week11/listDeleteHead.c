#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void listDeleteHead (List l) {
    Node curr = l->head;
    if (curr != NULL) {
        l->head = curr->next;
        free(curr);
    }
}
