#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("szoveg:\n");
    int c;
    int i = 0;
    while(c = getchar() != '\n' && c != EOF){
        i++;
    }
    printf("%d karakter volt.\n", i);
}