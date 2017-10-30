// Testing Sets

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Set.h"

void bulkAddSet(Set, item *, int);
void bulkRemoveSet(Set, item *, int);
void verifySetContains(Set, item *, int, bool);
void verifySetUnion(void);
void verifySetIntersection(void);
void handleZeros(void); 

int main (int argc, char *argv[]) {

    Set firstSet = newSet();
    item arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("Created set\n");

    bulkAddSet(firstSet, arr, 10);
    printf("Bulk added items to set\n");
    
    bulkRemoveSet(firstSet, arr, 10);
    printf("Removed items from set\n");
    
    destroySet(firstSet);
    printf("Destroyed Set\n");

    verifySetUnion();
    printf("Verified Set Union\n");

    verifySetIntersection();
    printf("Verified Set intersection\n");

    handleZeros();
    printf("Handled cases were sets are empty\n");

    printf("All tests ran! \n");

    return EXIT_SUCCESS;
}

// Adds 10 items to a set, and then checks they are in the sets.
void bulkAddSet(Set set, item arr[], int elementsLength) {
    int i = 0;
    while (i < elementsLength) {
        setAdd (set, arr[i]);
        i++;
    }

    verifySetContains(set, arr, elementsLength, true);
}

// Removes 10 items from the set, and then checks they have been removed
void bulkRemoveSet(Set set, item arr[], int elementsLength) {
    int i = 0;
    while (i < elementsLength) {
        setRemove(set, arr[i]);
        i++;
    }

    verifySetContains(set, arr, 10, false);
}

void verifySetContains (Set set, item elements[], int elementsLength, bool expectedCondition) {
    int i = 0;

    while (i < elementsLength) {
        assert(setContains(set, elements[i]) == expectedCondition);
        i++;
    }
}

void verifySetUnion () {
    item setAElems[] = {0, 1, 2, 3, 4};
    item setBElems[] = {5, 6, 7, 8, 9};

    Set setA = newSet();
    bulkAddSet(setA, setAElems, 5);

    Set setB = newSet();
    bulkAddSet(setB, setBElems, 5);

    Set setUn = setUnion(setA, setB);

    item arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    verifySetContains(setUn, arr, 10, true);

    destroySet(setA);
    destroySet(setB);
    destroySet(setUn);
}

void verifySetIntersection () {
    item setAElems[] = {0, 1, 2, 3, 4, 5};
    item setBElems[] = {3, 4, 5, 6, 7, 8};

    item intersection[] = {3, 4, 5};

    Set setA = newSet();
    bulkAddSet(setA, setAElems, 6);

    Set setB = newSet();
    bulkAddSet(setB, setBElems, 6);

    Set setIntersect = setIntersection(setA, setB);

    verifySetContains(setIntersect, intersection, 3, true);

    destroySet(setA);
    destroySet(setB);
    destroySet(setIntersect);

}

void handleZeros() {
    Set setA = newSet();
    Set setB = newSet();

    Set setIntersect = setIntersection(setA, setB);

    destroySet(setIntersect);

    Set setUn = setUnion(setA, setB);
    destroySet(setUn);

    destroySet(setA);
    destroySet(setB);

}
