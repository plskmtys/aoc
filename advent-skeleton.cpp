#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include "advent.h"

//functions

int main(){
    FILE *fp;
    fp = fopen("filename.txt", "r");
    
    char line[128];
    int sum = 0;
    while(fgets(line, 128, fp) != NULL){
        //string feldolgozása
    }

    printf("The sum is: %d\n", sum);
    
    fclose(fp);
    return 0;
}
