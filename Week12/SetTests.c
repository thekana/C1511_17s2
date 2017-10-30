#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <assert.h>
#include "Set.h"
#define TRUE (1==1)
#define FALSE (!TRUE)

void set1Tests();
void printSet(Set a);
int setLength(Set a);
int main (int argc, char *argv[]) {
    set1Tests();
    return EXIT_SUCCESS;
}

void set1Tests () {
    Set set1 = newSet();
    setAdd(set1, 1);
    setAdd(set1, 2);
    setAdd(set1, 3);
    setAdd(set1, 4);
    printSet(set1);
    setRemove(set1, 1);
    printSet(set1);
    setAdd(set1, 1);
    printf("Length %d\n",setLength(set1));
    assert(setContains(set1,1)==TRUE);
    assert(setContains(set1,2)==TRUE);
    assert(setContains(set1,4)==TRUE);
    setAdd(set1,10);
    setRemove(set1,10);
    setRemove(set1,2);
    printSet(set1);
    Set set2 = newSet();
    setAdd(set2, 3);
    setAdd(set2, 4);
    setAdd(set2, 1);
    Set setU = setUnion(set1,set2);
    printSet(setU);
    Set setI = setIntersection(set1,set2);
    printf("Length %d\n",setLength(setI));
    printSet(setI);
    Set emptySet = newSet();
    Set emptySet1 = newSet();
    assert(setSubset(setI,set1) == TRUE);
    assert(setSubset(emptySet,set1) == TRUE);
    assert(setSubset(emptySet1,emptySet) == TRUE);
    assert(setSubset(set2,emptySet) == FALSE);
    assert(setSubset(set2,set1) == TRUE);
    setAdd(set2,6);
    assert(setSubset(set2,set1) == FALSE);
    assert(setEqual(emptySet1,emptySet)== TRUE);
    assert(setEqual(set2,set1) == FALSE);
    assert(setEqual(set2,set2) == TRUE);
    Set set4 = newSet();
    setAdd(set4,1);setAdd(set4,3);setAdd(set4,4);setAdd(set4,6);
    printSet(set4);
    assert(setEqual(set2,set4) == TRUE);
    destroySet(set1);
    destroySet(set2);
}


