#include <stdio.h>
#include <stdlib.h>

int isLeapYear(int year);

int main(int argc, char *argv[]){
  int year;
  printf("Enter a year after 1582: ");
  scanf("%d",&year);
  if(year<1582){
    printf("%d is before 1582.\n",year);
  }
  else if(isLeapYear(year)){
    printf("%d is a leap year.\n",year);
  }
  else{
    printf("%d is not a leap year.\n",year);
  }
  
  return EXIT_SUCCESS;
}

int isLeapYear(int m){
  int n;
  if(m%4==0){
    if(m%100==0){
      if(m%400==0){
        n=1;
      }
      else{
        n=0;
      }
    }
    else{
      n=1;
    }
  }
  else{
    n=0;
  }
  return n;
}
