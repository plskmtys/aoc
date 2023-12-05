#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum color{
    red,
    green,
    blue,
}color;

typedef struct ball{
    color clr;
    int qty;
}ball;

ball max[] = {{red, 12}, {green, 13}, {blue, 14}};
char *colors[] = {"red", "green", "blue"};
int maxn[] = {12, 13, 14};

bool validgame(char *line){
    char *token = strtok(line, ";");
    while(token != NULL){
        char *innertoken = strtok(token, " ,");
        while(innertoken != NULL){
            ball read;
            read.clr = 0;
            read.qty = 0;
            char colorstr[6] = {'\0'};
            sscanf(innertoken, "%d %s", &read.qty, colorstr);
            for(int i = 0; i < 3; i++){
                if(strcmp(colorstr, colors[i]) == 0) {
                    read.clr = i;
                    break;
                }
            }
            if(read.qty > maxn[read.clr]){
                return false;
            }
            innertoken = strtok(NULL, " ,");
        }
        token = strtok(NULL, ";");
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
    char *line = NULL;
    size_t len = 100;
    ssize_t read;
    int game = 1;

    while ((read = getline(&line, &len, fp)) != EOF) {
        char gameline[len];
        sscanf(line, "Game %d: %[^\n]", &game, gameline);
        if(validgame(gameline)){
            sum+=game;
        }
        game++; // Increment game number
    }

    printf("az elso osszeg: %d\n", sum);

    fclose(fp);
    if (line)
        free(line);
    return 0;
}