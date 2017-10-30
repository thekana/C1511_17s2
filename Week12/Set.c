//Set.c
//King z5176970, Quinn z5142018
//2018-10-28 Zain F09A

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "Set.h"
#define TRUE (1==1)
#define FALSE (!TRUE)

typedef struct _node *Node;

typedef struct _set {
    Node head;
} set;

typedef struct _node {
    item value;
    Node next;
} node;

int setLength(Set a);
void printSet(Set a);

Node newNode(item value);
// Create a new `Set`.
Set newSet (void) {
    Set new = calloc(1, sizeof(struct _set));

    if (new == NULL) {
        fprintf(stderr, "error: unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    return new;
}

Node newNode(item value) {
    Node new = calloc(1, sizeof(node));
    if (new == NULL) {
        errx(EXIT_FAILURE, "newNode calloc failed to allocate memory");
    }
    
    new->value = value;
    new->next = NULL;
    return new;
}

// Release all resources associated with a `Set`.
void destroySet (Set s) {
    Node iterate = s->head;

    while(iterate!=NULL) {
        Node toFree = iterate;
        iterate = iterate->next;
        free(toFree);
    }
    free(s);
}

// Add an `item` to the `Set`.
void setAdd (Set s, item a) {
    Node new = newNode(a);
    if(s->head == NULL) {
        s->head = new;
    } else if (setContains(s,a)) {
    } else {
        Node temp = s->head;
        s->head = new;
        new->next = temp;
    }
}

// Remove an `item` from the `Set`.
void setRemove (Set s, item a){
    Node curr = s->head;
    int index = -1;
    int i=0;
    //printf("Head is %d\n",s->head->value);
    if(setContains(s,a)){
        if(s->head->value == a) {
            Node tmp = s->head;
            s->head = curr->next;
            free(tmp);
        } else {
            while(curr->next!= NULL && index == -1) {
                if(curr->next->value == a) {
                    index=i+1;
                }
                if(index == -1) {
                    curr=curr->next;
                }
                i++;}
                //printf("Here %d\n",index);
            
/*            if (index==setLength(s)) {
                printf("In IF\n");
                free(curr->next);
                curr->next = NULL;
            }*/ 
                printf("In else\n");
                Node toBeFree = curr->next;
                curr->next = curr->next->next;
                free(toBeFree);
            
        }
    }
}

// Does the `Set` contain this `item`?
bool setContains (Set s, item a) {

    Node curr = s->head;
    bool itemExists=FALSE;
    //Find the item
    while(curr != NULL && itemExists == FALSE){
        if(curr->value==a) {
            itemExists = TRUE;
        }
        curr = curr->next;
    }

    return itemExists;
}

// Take the union of two sets (a ∪ b).
Set setUnion (Set a, Set b) {
    Set new = newSet();
    Node currA = a->head;
    Node currB = b->head;
    while(currA != NULL) {
        setAdd(new,currA->value);
        currA = currA->next;
    }
    while(currB != NULL) {
        setAdd(new,currB->value);
        currB = currB->next;
    }
    return new;
}

// Take the intersection of two sets (a ∩ b).
Set setIntersection (Set a, Set b) {
    Set new = newSet();
    Node currA = a->head;
    Node currB = b->head;
    while(currA != NULL){
        if(setContains(b,currA->value)){
            setAdd(new,currA->value);
        }
        currA=currA->next;
    }
    return new;
}

// Is `a` a subset of `b` (a ⊆ b)?
bool setSubset (Set a, Set b) {

    Node currA= a->head;
    Node currB= b->head;
    bool answer = FALSE;
    int flag=0;
    if(currB==NULL && currA==NULL){
        answer = TRUE;
    } else if (currA==NULL){
        answer = TRUE;
    } else {
        answer = FALSE;
        while(currA != NULL && answer == FALSE){
            if(setContains(b,currA->value)){
                flag++;
            }
            currA = currA->next;
        }
        if(flag == setLength(a)){
            printf("Flag = %d\n", flag);
            answer = TRUE;
        }
    }
    return answer;
}

int setLength (Set a) {
    Node curr = a->head;
    int count = 0;
    while(curr!= NULL){
        curr = curr->next;
        count++;
    }
    return count;
}


void printSet(Set a){
    Node curr = a->head;
    while(curr!=NULL){
        printf("%d->",curr->value);
        curr= curr->next;
    }
    printf("X\n");
}
// Is `a` equal to `b` (where a ⊆ b and b ⊆ a, a == b).
bool setEqual (Set a, Set b){
    return (setSubset(a,b) && setSubset(b,a));
}

