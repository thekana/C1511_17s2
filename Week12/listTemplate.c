// Basic linked list demo
// Andrew Bennett <andrew.bennett@unsw.edu.au>
// 2017-10-09

#include <stdio.h>
#include <stdlib.h>


// We need to typedef this first
typedef struct _node *Node;
typedef struct _list *List;

// The list struct -- holds a pointer to the "head" of the list
// (the first node).
typedef struct _list {
    Node head;
} list;

// The node struct -- holds some value, and a pointer to the next
// node in the list.
typedef struct _node {
    int value;
    Node next;
} node;

// Allocate memory for a new list / node.
List newList (void);
Node newNode (int value);

// Makes a list with some values in it.
List makeList (void);

// Print a list.
void printList (List list);


int main (int argc, char *argv[]) {

    // ????

    return EXIT_SUCCESS;
}


void printList (List list) {
    Node curr = list->head;

    while (curr != NULL) {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
    printf("X\n");
}

// Make a list to work with for the demo.
List makeList () {
    List list = newList();
    list->head = newNode(1);
    list->head->next = newNode(2);
    list->head->next->next = newNode(3);
    list->head->next->next->next = newNode(4);
    list->head->next->next->next->next = newNode(5);
    list->head->next->next->next->next->next = NULL;

    return list;
}

// Allocate memory for a new list.
List newList(void) {
    // Allocate memory
    List list = calloc(1, sizeof(struct _list));

    // check that it worked
    if (list == NULL) {
        fprintf(stderr, "error: unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    return list;
}

// Create a new node.
Node newNode(int value) {
    Node node = calloc(1, sizeof(struct _node));
    if (node == NULL) {
        fprintf(stderr, "error: unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = NULL;
    return node;
}
Node newNode (int value) {
    Node new = calloc(1, sizeof(struct _node));
    new->value = value;
    return new;
}

