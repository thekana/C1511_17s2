//List is ordered
// King z5176970
// Quinn z5142018
//Zain F09A 2017-10-13

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int listIsOrdered (List l) {
    Node curr = l->head;
    int result = TRUE;
    if(curr == NULL) {
        result = TRUE;
    } else {
        while (result == TRUE && curr->next!= NULL) {
            if (curr->next->value >= curr->value){
                result = TRUE;
            } else {
                result = FALSE;
            }
            curr = curr->next;
        }
    }
    return result;
}
