#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>

#ifndef ADVENT_H
#define ADVENT_H

void printlist(int *list, size_t size){
    for(size_t i = 0; i<size-1; i++){
        printf("%d, ", list[i]);
    }
    printf("%d\n", list[size-1]);
}

int buffertoint(char *buffer){
    int num = 0;
    int i = 0;
    bool negative = false;
    if(buffer[0] == '-'){
        negative = true;
        i++;
    }
    while(buffer[i] != '\0'){
        num = num*10 + (buffer[i] - '0');
        i++;
    }
    if(negative) num *= -1;
    return num;
}

/// @brief Read numbers separated by a given character from a string into a list, up to a given character.
/// @param line input line string, has to end with '\0'.
/// @param list output list.
/// @param size output list size.
/// @param delim what character to read up to and not including.
/// @param sep the character which separates numbers in the string. one or more occurences supported.
void getnums(char *line, int *list, size_t size, char delim, char sep){
    char buffer[16];
    buffer[0] = '\0';
    int listindex = 0;
    int bufferindex = 0;

    while(*line != delim){
        if(*line == sep){
            if(buffer[0] != '\0'){
                list[listindex] = buffertoint(buffer);
                buffer[0] = '\0';
                bufferindex = 0;
                listindex++;
            }
        }
        if(isdigit(*line) || *line == '-'){
            buffer[bufferindex] = *line;
            buffer[bufferindex+1] = '\0';
            bufferindex++;
        }
        line++;
    }
    if(buffer[0] != '\0'){
        list[listindex] = buffertoint(buffer);
    }
}

void split(char *line, char **list, size_t size, char delim, char sep){
    char buffer[16];
    buffer[0] = '\0';
    int listindex = 0;
    int bufferindex = 0;

    while(*line != delim){
        if(*line == sep){
            if(buffer[0] != '\0'){
                strcpy(list[listindex], buffer);
                buffer[0] = '\0';
                bufferindex = 0;
                listindex++;
            }
        } else {
            buffer[bufferindex] = *line;
            buffer[bufferindex+1] = '\0';
            bufferindex++;
        }
        line++;
    }
    if(buffer[0] != '\0'){
        strcpy(list[listindex], buffer);
    }
}


#endif