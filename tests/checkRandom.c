#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int returnRandomNumber(int x, int y){
    srand(time(NULL));
    return rand() % (x + y);
}

int main(){for(int i = 0; i > -1; i++){printf("%d",returnRandomNumber(0,3));}}