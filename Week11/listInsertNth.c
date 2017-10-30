// Inserts a node at the nth spot
// Jack G (z5160408)
// Jasvir B (z5165068)
// Sitar-Fri10 Zain Afzal
// Created on 2017-10-13

#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "list.h"

Node newNode(int value);

void listInsertNth (List l, int n, int val) {
    // If there is no head to the list we just create one
    if (l->head == NULL) {
        l->head = newNode(val);
        // If we want to append at the start we also need to insert a new head.
    } else if (n == 0) {
        Node start = l->head;
        Node new = newNode(val);
        l->head = new;
        new->next = start;
    } else {
        Node curr = l->head;
        int i = 0;
        while (i < n -1) {
            curr = curr->next;
            i++;
        }
        Node new = newNode(val);
        new->next = curr->next;
        curr->next = new;
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
