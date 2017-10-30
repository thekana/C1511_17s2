#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int a,b,sum;
    printf("Please enter two positive integers: \n");
    scanf("%d %d",&a,&b);
    sum=a+b;
    printf("%0#4x + %0#4x = %0#4x\n",a,b,sum);
    
    return EXIT_SUCCESS;
  }
  