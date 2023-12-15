#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct {
    int num;
    int winners[10];
    int tips[25];
    int matches;
    int amount;
} Card;

int matches(const int arr1[10], const int arr2[25]){
    int m = 0;
    for(size_t i = 0; i < 10; i++){
        for (size_t j = 0; j < 25; j++){
            if(arr1[i] == arr2[j]) m += 1;
        }
    }
    return m;
}

void matches2 (Card *card){
    int m = 0;
    for(size_t i = 0; i < 10; i++){
        for (size_t j = 0; j < 25; j++){
            if(card->winners[i] == card->tips[j]) m += 1;
        }
    }
    card->matches = m;
}

int twotothe(int exp){
    return 1<<exp;
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

void getnums(char *line, int *list1, size_t size1, int *list2, size_t size2){
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
                list1[listindex] = buffertoint(buffer);
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
                list2[listindex] = buffertoint(buffer);
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
    } //q: why is the last number not added to the list? a: because the last number is not followed by a space q: how to fix? a: add a space at the end of the line
    if(buffer[0] != '\0'){
        list2[listindex] = buffertoint(buffer);
    }
}

int main(){
    FILE *fp = fopen("input4.txt", "r");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }
    //parse numbers from a line of the file like this:
    //Card n: winner1, winner2, winner3, ... winner10 | tip1, tip2, tip3, ... tip25
    //where n is the card number, winner1 is the first winner, etc.
    //and tip1 is the first tip, etc.
    //the numbers are separated by spaces
    
    
    int winner[10];
    int tip[25];
    char line[128];
    //how to count sum if m is the number of matches? sum += 2^(m-1)
    int sum = 0;
    int m = 0;
    while(fgets(line, 128, fp) != NULL){
        getnums(line, winner, 10, tip, 25);
        m = matches(winner, tip);
        if(m != 0) sum += twotothe(m-1);
        //printlist(winner, 10);
        //printlist(tip, 25);
        //printf("Matches: %d\n", matches(winner, tip));
    }
    printf("The first sum is: %d\n", sum);
}