#include <stdio.h>
#include <stdlib.h>
#define MIN_DRIVING_AGE 16

int main(void){

	printf("How old are you\n");
int age=0;

	scanf("%d",&age);
	if (age>MIN_DRIVING_AGE) 
	  printf("You can drive\n");
	  else printf("You cannot\n");
	  
	  return EXIT_SUCCESS;
}


