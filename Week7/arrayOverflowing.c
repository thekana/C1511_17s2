// Experiment with exploring off the end of an array.
// Note: Don't forget to compile with gcc, NOT dcc!
// Completed by
//  Jasvir Boparoy z5165068
//  Kanadech (King) z5176970
// Commpleted on 2017-09-08
// Zain F09A

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    int canaryA = 42;
    int testArray[10] = {0,1,2,3,4,5,6,7,8,9};
    int canaryB = 99;

    // Note: Modify the code below to include a while loop,
    // so you can repeatedly test values without having to
    // run the program multiple times.
    while(2>1) {
        int index;
        printf ("Enter an array index between 0 and 9\n");
        scanf ("%d", &index);
        printf ("testArray[%d]=%d\n",index, testArray[index]);
    }

    return EXIT_SUCCESS;
}
