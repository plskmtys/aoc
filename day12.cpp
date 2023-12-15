#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include "advent.h"

/*
input txt representing machines row by row. saple row: 
.#??..??#..###...?##. 2,2,3,3

??????#??#?? 1,1,5,1
.#.#.#####.# 1,1,5,1
dothashmatch(1, 2) = true

. = operational
# = broken
? = unknown
numbers on the right are the number of broken machines in the row, grouped if there are no operational machines between them.
how many possible layouts are there, if the numbers are correct (and are correctly grouped)?
*/

/*
next state table
//
//    current    .                        #                   ?
last
.            do nothing                 new list item       new list item and increment
#                                       do nothing          new list item and increment
?            do not increment           do nothing          increment current list item 
//        given list item anymore

*/

typedef enum {
    OPN,
    BKN,
    UKN
} MachineState;

MachineState ParseState(char c){
    switch(c){
        case '.': return OPN;
        case '#': return BKN;
        case '?': return UKN;
        default: return UKN;
    }
}

typedef struct Line{
    char line[21]; //each line's string part is max 20 chars long + '\0'
    size_t len;
    char broken[7]; //there are max 6 positive numbers + '\0'
}Line;

void ParseBroken(Line *line){ //in: 1,1,5,1
    int j = 0;
    for(int i = 0; line->broken[i] != '\0'; i++) {
        if(isdigit(line->broken[i])){
            line->broken[j] = line->broken[i];
            j++;
        }
    }
    line->broken[j] = '\0';
} //out: 1151

void ParseLine(char *line, Line *dest){
    sscanf(line, "%s %s", dest->line, dest->broken);
    ParseBroken(dest);
    dest->len = strlen(dest->line);
}

char *GenerateLayout(Line *line){

}

bool MatchPattern(char* target, char* pattern, char wildcard){
    size_t len = strlen(target);
    for(int i = 0; i < len; i++){
        if(pattern[i] == wildcard) continue;
        if(pattern[i] != target[i]) return false;
    }
    return true;
}

char* LayoutFromString(char *string){
    char ret[7] = {'\0'};
    char current = '0';
    size_t currentindex = 0;
    for(int i = 0; string[i] != '\0'; i++){
        switch(string[i]){
            case '.':{
                if(current != '0'){
                    ret[currentindex] = current;
                    currentindex++;
                    ret[currentindex] = '\0';
                    current = '0';
                }
            }
            case '#':{
                current++;
            }
        }
        ret[currentindex+1] = '\0';
        return ret;
    }
    
}

int main(){
    FILE *fp;
    fp = fopen("sample12.txt", "r");
    
    char line[128];
    int sum = 0;
    while(fgets(line, 128, fp) != NULL){
        //string feldolgozása
    }

    printf("The sum is: %d\n", sum);
    
    fclose(fp);
    return 0;
}
