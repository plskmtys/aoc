#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct {
    int winners[10];
    int tips[25];
    int matches;
    int amount;
} Card;

void matches (Card *card){
    int m = 0;
    for(size_t i = 0; i < 10; i++){
        for (size_t j = 0; j < 25; j++){
            if(card->winners[i] == card->tips[j]) m += 1;
        }
    }
    card->matches = m;
}

void printlist(int *list, size_t size){
    for(size_t i = 0; i<size-1; i++){
        printf("%d, ", list[i]);
    }
    printf("%d\n", list[size-1]);
}

int buffertoint(char *buffer){
    int num = 0;
    int i = 0;
    while(buffer[i] != '\0'){
        num = num*10 + (buffer[i] - '0');
        i++;
    }
    return num;
}

void getnums(char *line, Card *card){
    char buffer[3];
    buffer[0] = '\0';
    while(*line != ':'){
        line++;
    }
    line++;
    int listindex = 0;
    int bufferindex = 0;
    while(*line != '|'){
        if(*line == ' '){
            line++;
            if(buffer[0] != '\0'){
                card->winners[listindex] = buffertoint(buffer);
                buffer[0] = '\0';
                bufferindex = 0;
                listindex++;
            }
            continue;
        }
        if(isdigit(*line)){
            buffer[bufferindex] = *line;
            buffer[bufferindex+1] = '\0';
            bufferindex++;
        }
        line++;
    }
    listindex = 0;
    bufferindex = 0;
    while(*line != '\0'){
        if(*line == ' '){
            if(buffer[0] != '\0'){
                card->tips[listindex] = buffertoint(buffer);
                buffer[0] = '\0';
                bufferindex = 0;
                listindex++;
            }
        }
        if(isdigit(*line)){
            buffer[bufferindex] = *line;
            buffer[bufferindex+1] = '\0';
            bufferindex++;
        }
        line++;
    }
    if(buffer[0] != '\0'){
        card->tips[listindex] = buffertoint(buffer);
    }
}

int main(){
    FILE *fp = fopen("input4.txt", "r");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    size_t size = 193;
    Card allcards[size];
    for(size_t i = 0; i < size; i++){
        allcards[i].amount = 1;
    }
    size_t cardindex = 0;
    int numberofcards = 0;
    char line[128];
    Card *currentcard;
    while(fgets(line, 128, fp) != NULL){
        currentcard = &allcards[cardindex];
        getnums(line, currentcard);
        matches(currentcard);
        //processing current card
        for(size_t i = cardindex+1; i < size && i <= cardindex+currentcard->matches; i++){
            allcards[i].amount += currentcard->amount;
        }
        numberofcards += currentcard->amount;
        cardindex++;
    }
    fclose(fp);
    printf("Number of cards: %d\n", numberofcards);
}