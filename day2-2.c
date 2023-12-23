#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum color{
    red,
    green,
    blue,
}color;

typedef struct ball{
    color clr;
    int qty;
}ball;

ball maxballs[] = {{red, 12}, {green, 13}, {blue, 14}};
char *colors[] = {"red", "green", "blue"};
int maxn[] = {12, 13, 14};

bool validgame(char *line){
    char colorbuffer[10] = {0};
    size_t colorbufindex = 0;
    char numbuffer[4] = {0};
    size_t numbufindex = 0;
    int qty;
    while(*line != ':'){
        line++;
    }
    while(*line != '\0'){
        
        if(isdigit(*line)){
            numbuffer[numbufindex++] = *line;
            numbuffer[numbufindex] = '\0';
        }
        else if(*line == ' '){
            qty = atoi(numbuffer);
            numbufindex = 0;
        }
        else if(*line == ';' || *line == '\n' || *line == ','){
            for(int i = 0; i < 3; i++){
                if(strcmp(colorbuffer, colors[i]) == 0){
                    if(qty > maxn[i]){
                        return false;
                    }
                    break;
                }
            }
            colorbufindex = 0;
            numbufindex = 0;
            qty = 0;
        }
        else if(isalpha(*line)){
            colorbuffer[colorbufindex++] = *line;
            colorbuffer[colorbufindex] = '\0';
        }
        line++;
    }
    return true;
}

int main(void){
    printf("day two!\n");
    FILE *fp = fopen("input2.txt", "r");
    if(fp == NULL){
        fprintf(stderr, "nem sikerült megnyitni a fájlt.\n");
        return 1;
    }

    int sum = 0;
    char line[256] = {'\0'};
    int game = 1;

    while (fgets(line, 256, fp) != NULL) {
        if(validgame(line)){
            sum+=game;
        }
        game++;
    }

    printf("a masodik osszeg: %d\n", sum);

    fclose(fp);
    return 0;
}