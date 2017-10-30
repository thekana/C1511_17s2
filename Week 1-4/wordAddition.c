// Add words to words CHALLENGE
// Kanadech Jirapongtanavech(z5176970)
// Tutor: Zain Afzal(F09A)
// Created on 2017/8/4
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    int a=0,b=0,c=0;
    printf("Please enter two integers: ");
    scanf("%d %d",&a,&b);
    c=a+b;
    if(abs(a)>10){
        printf("%d ",a);
    }
    else if(a<0){
        printf("negative ");
    }
    if(abs(a)==0){
        printf("zero");
    }
    else if(abs(a)==1){
        printf("one ");
    }
    else if(abs(a)==2){
        printf("two ");
    }
    else if(abs(a)==3){
        printf("three ");
    }
    else if(abs(a)==4){
        printf("four ");
    }
    else if(abs(a)==5){
        printf("five ");
    }
    else if(abs(a)==6){
        printf("six ");
    }
    else if(abs(a)==7){
        printf("seven ");
    }
    else if(abs(a)==8){
        printf("eight ");
    }
    else if(abs(a)==9){
        printf("nine ");
    }
    else if(abs(a)==10){
        printf("ten ");
    }
    printf("+ ");

    if(abs(b)>10){
        printf("%d ",b);
    }
    else if(b<0){
        printf("negative ");
    }
    if(abs(b)==0){
        printf("zero");
    }
    else if(abs(b)==1){
        printf("one ");
    }
    else if(abs(b)==2){
        printf("two ");
    }
    else if(abs(b)==3){
        printf("three ");
    }
    else if(abs(b)==4){
        printf("four ");
    }
    else if(abs(b)==5){
        printf("five ");
    }
    else if(abs(b)==6){
        printf("six ");
    }
    else if(abs(b)==7){
        printf("seven ");
    }
    else if(abs(b)==8){
        printf("eight ");
    }
    else if(abs(b)==9){
        printf("nine ");
    }
    else if(abs(b)==10){
        printf("ten ");
    }
    printf("= ");

    if(abs(c)>10){
        printf("%d\n",c);
    }
    else if(c<0){
        printf("negative ");
    }
    if(abs(c)==0){
        printf("zero\n");
    }
    else if(abs(c)==1){
        printf("one\n");
    }
    else if(abs(c)==2){
        printf("two\n");
    }
    else if(abs(c)==3){
        printf("three\n");
    }
    else if(abs(c)==4){
        printf("four\n");
    }
    else if(abs(c)==5){
        printf("five\n");
    }
    else if(abs(c)==6){
        printf("six\n");
    }
    else if(abs(c)==7){
        printf("seven\n");
    }
    else if(abs(c)==8){
        printf("eight\n");
    }
    else if(abs(c)==9){
        printf("nine\n");
    }
    else if(abs(c)==10){
        printf("ten\n");
    }
    return EXIT_SUCCESS;
}
