#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>

List newList(void);
void reverse (List l);
Node newNode(int value);
void printList(List l);
List reverse1 (List l);
void reverse2 (List l);
void orderedDelete (List l);
void frontBackSplit (List sourceList, List frontList, List backList);
int numItems (List l);

int main () {
    int array[20] = {0,5,2,3,4,5,6,7,100,9,15,78,300,302,412,13,78,412,48,2};
    int i=1;
    List l = newList();
    Node curr = newNode(array[0]);
    l->head = curr;
    while(i<20) {
        curr->next= newNode(array[i]);
        curr = curr->next;
        i++;
    }
    //printf("Largest = %d\n", listFindLargest(l));
    printList(l);
    reverse2(l);
    printList(l);
    List l1 = reverse1(l);
    printList(l1);
    orderedDelete(l);
    printList(l);
    List f = newList();
    List b = newList();
    List a = newList();
    a->head = newNode(1);
    a->head->next = newNode(2);
    a->head->next->next = newNode(3);
    a->head->next->next->next = newNode(4);
    a->head->next->next->next->next = newNode(5);
    a->head->next->next->next->next->next = newNode(6);
    printf("Source List is ");
    frontBackSplit(a,f,b);
    printList(a);
    printList(f);
    printList(b);
}

List newList(void) {
    List new = calloc(1,sizeof(list));
    if (new == NULL) {
        fprintf(stderr, "error: unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    return new;
}

Node newNode(int value) {
    Node new = calloc(1,sizeof(node));
    if (new == NULL) {
        fprintf(stderr, "error: unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    new->value = value;
    new->next = NULL;
    return new;
}

void printList(List l) {
    Node curr = l->head;
    while (curr!= NULL) {
        printf("%d->",curr->value);
        curr = curr->next;
    }
    printf("X\n");
}

List reverse1 (List l) {
    Node curr = l->head;
    List output = newList();
    while (curr != NULL) {
        Node temp1 = newNode(curr->value);
        temp1->next = output->head;
        output->head = temp1;
        curr = curr->next;
    }
    return output;
}

void reverse2 (List l) {
    Node prev = NULL;
    Node curr = l->head;
    Node curr_head;
    while(curr != NULL) {
        Node next = curr->next;
        curr->next = prev;
        curr_head = curr;
        prev = curr;
        curr = next;
    }
    l->head = curr_head;
}

void orderedDelete (List l) {
    Node curr = l->head;
    while(curr->next!=NULL) {
        if(curr->value > curr->next->value) {
            Node temp = curr->next;
            curr->next = curr->next->next;
            free(temp);
        } else {
            curr=curr->next;
        }
    }
}

int numItems (List l) {
    int length = 0;
    Node current = l->head;
    while (current != NULL){
        length++;
        current = current->next;
    }
    return length;
}

void frontBackSplit (List sourceList, List frontList, List backList) {
    int length = numItems(sourceList);
    int b = length/2;
    int a = length -b;
    int i = 1;
    printList(sourceList);
    Node curr = sourceList->head;
    frontList->head = curr;
    Node currF = frontList->head;
    while(i < a) {
        currF = currF->next;
        curr = curr->next;
        i++;
    }
    curr = curr->next;
    backList->head = curr;
    i=0;
    Node currB = backList->head;
    while(i < b){
        currB = currB->next;
        curr = curr->next;
        i++;
    }
    currF ->next= NULL;
    sourceList->head = NULL;
    printList(frontList);
    printList(backList);
    printList(sourceList);
}
