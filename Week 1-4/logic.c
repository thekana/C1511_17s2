#include <stdio.h>
#include <stdlib.h>
int main (void) {
  printf("true and true is %d\n",(1&&1));
  printf("true and false is %d\n",(1&&0));
  printf("false and false is %d\n",(1&&0));
  printf("true or true is %d\n",(1||1));
  printf("true or false is %d\n",(0||1));
  printf("false or false is %d\n",(0||0));
}