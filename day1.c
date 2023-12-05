#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

const char* szamok[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int FirstFromLine(char *line, bool CountStr){
    size_t slen = strlen(line);
    char buffer[slen+1];
    buffer[0] = '\0';
    size_t bufindex = 0U;
    int first;
    for(size_t i = 0; i < slen; i++){
        if(line[i] >= 0x30 && line[i] <= 0x39){ //ha a karakter szám akkor TALÁLTUNK EGY SZÁMOT.
            first = line[i]-0x30;
            return first;
        } else if(CountStr){ //ha nem szám, akkor hozzáadjuk a bufferhez.
            buffer[bufindex++] = line[i];
            buffer[bufindex] = '\0';
            //ha az így keletkezett buffer egy szám leírása betűvel, akkor TALÁLTUNK EGY SZÁMOT.
            #pragma omp parallel for schedule(dynamic, 2)
            for(int szamindex = 1; szamindex <= 9; szamindex++){
                if(strstr(buffer, szamok[szamindex-1])){
                    first = szamindex;
                    return first;
                }
            }
        }
    }
}

void insert_char_at_beginning(char *str, char c) {
    int len = strlen(str);
    for(int i = len; i >= 0; i--) {
        str[i+1] = str[i];
    }
    str[0] = c;
}

int LastFromLine(char *line, bool CountStr){
    size_t slen = strlen(line);
    char buffer[slen+1];
    buffer[0] = '\0';
    int first;
    for(size_t i = slen; i >= 0; i--){
        if(line[i] >= 0x30 && line[i] <= 0x39){ //ha a karakter szám akkor TALÁLTUNK EGY SZÁMOT.
            first = line[i]-0x30;
            return first;
        } else if(CountStr){ //ha nem szám, akkor hozzáadjuk a bufferhez.
            insert_char_at_beginning(buffer, line[i]);
            //ha az így keletkezett buffer egy szám leírása betűvel, akkor TALÁLTUNK EGY SZÁMOT.
            #pragma omp parallel for schedule(dynamic, 2)
            for(int szamindex = 1; szamindex <= 9; szamindex++){
                if(strstr(buffer, szamok[szamindex-1])){
                    first = szamindex;
                    return first;
                }
            }
        }
    }
}

int main(){
    printf("day one!\n");
    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL){
        fprintf(stderr, "nem sikerült megnyitni a fájlt.\n");
        return 1;
    }

    int sum12 = 0;
    char *line = NULL;
    size_t len = 64;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != EOF) {
        sum12 += 10*FirstFromLine(line, false) + LastFromLine(line, false);
    }

    printf("az elso osszeg: %d\n", sum12);
    fclose(fp);
    
    //part 2
    fp = fopen("input.txt", "r");
    if(fp == NULL){
        fprintf(stderr, "nem sikerült megnyitni a fájlt.\n");
        return 1;
    }
    
    int sum2 = 0;
    line = NULL;
    len = 64;

    while ((read = getline(&line, &len, fp)) != EOF) {
        sum2 += 10*FirstFromLine(line, true) + LastFromLine(line, true);
    }

    printf("a masodik osszeg: %d\n", sum2);

    fclose(fp);
    if (line)
        free(line);
    return 0;
}