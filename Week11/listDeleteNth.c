// Inserts a node at the nth spot
// Jack G (z5160408)
// Jasvir B (z5165068)
// Sitar-Fri10 Zain Afzal
// Created on 2017-10-13

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

Node newNode(int value);

void listDeleteNth (List l, int n) {
    if (l->head == NULL) {
        // Probably not much we can do here
    } else if (n == 0) {
        Node newStart = l->head->next;
        free (l->head);
        l->head = newStart;
    } else {
        Node curr = l->head;
        int i = 0;
        while (i < n - 1) {
            curr = curr->next;
            i++;
        }
        Node nodeToBeFreed = curr->next;
        curr->next = curr->next->next;
        free(nodeToBeFreed);
    }
}


Node newNode(int value) {
    Node new = calloc(1, sizeof(node));
    if (new == NULL) {
        errx(EXIT_FAILURE, "newNode calloc failed to allocate memory");
    }
    
    new->value = value;
    new->next = NULL;
    return new;
}
