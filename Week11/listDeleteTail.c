#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void listDeleteTail (List l) {
    Node curr = l->head;
    if (l->head == NULL ) {
    } else if (curr->next==NULL) {
        free(curr);
        l->head = NULL;
    } else {
        while(curr->next->next!= NULL) {
            curr = curr->next;
        }
        Node tbf = curr->next;
        curr->next= NULL;
        free(tbf);
    }
}


