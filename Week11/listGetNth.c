#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int listGetNth (List l, int n) {
    int i=0;
    int answer;
    Node curr = l->head;
    while (i != n+1) {
        answer = curr->value;
        i++;
        curr = curr->next;
    }
    return answer;
}
