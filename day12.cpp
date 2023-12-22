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
? = unknown (wildcard)
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

#define MAXLEN 128
#define MAXNUM 32
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
    char line[MAXLEN];
    size_t len;
    size_t wildcards;
    char numbers[MAXNUM];
}Line;

__uint128_t wildcardmask(Line *line){
    __uint128_t ret = 0ULL;
    for(int i = 0; i < line->len; i++){
        if(line->line[i] == '?'){
            ret |= (1 << i);
        }
    }
    return ret;
}

char* Merge(Line* line, __uint128_t mask, __uint128_t value){
    char *ret = (char*)malloc(MAXLEN * sizeof(char));
    size_t j = 0;
    for(size_t i = 0U; i < line->len; i++){
        if(mask & (1 << i)){
            if(value & (1 << j)){
                ret[i] = '#';
            } else {
                ret[i] = '.';
            }
            j++;
        } else {
            ret[i] = line->line[i];
        }
    }
    ret[line->len] = '\0';
    return ret;
}

void printnumbers(char *numbers){
    int i = 0;
    for(; numbers[i+1] != '\0'; i++){
        printf("%d,", numbers[i]);
    }
    printf("%d", numbers[i]);
    printf("\n");
}

void ParseNumbers(Line *line){
    int j = 0;
    int num = 0;
    for(int i = 0; line->numbers[i] != '\0'; i++) {
        if(isdigit(line->numbers[i])){
            num = num * 10 + (line->numbers[i] - '0');
        } else if(line->numbers[i] == ',') {
            line->numbers[j] = num;
            num = 0;
            j++;
        }
    }
    line->numbers[j] = num;
    j++;
    line->numbers[j] = '\0';
} //out: {1,1,5,1,'\0'}

bool MatchNumbers(char* cmp1, char* cmp2){ //cmp1: {1, 1, 5, 1, '\0'} cmp2: {1, 1, 5, 1, '\0'}
    return strcmp(cmp1, cmp2) == 0 ? true : false;
}

void ParseLine(char *line, Line *dest){
    sscanf(line, "%s %s", dest->line, dest->numbers);
    ParseNumbers(dest);
    dest->len = strlen(dest->line);
}

Line UnfoldLine(Line *line){ //input: line->line: ".#"; line->len = 2; line->numbers = {'1', '\0'};
    Line ret;
    int j = 0;
    int n = 0;
    for(int i = 0; i<5; i++){
        for(int k = 0; k < line->len; k++){
            ret.line[j] = line->line[k];
            j++;
        }
        ret.line[j] = '?';
        j++;

        for(int k = 0; line->numbers[k] != '\0'; k++){
            ret.numbers[n] = line->numbers[k];
            n++;
        }
    }
    ret.line[j-1] = '\0';
    ret.len = strlen(ret.line);
    ret.numbers[n] = '\0';
    return ret;
} //output: line->line: ".#?.#?.#?.#?.#"; line->len = 10; line->numbers = {'1', '1', '1', '1', '1', '\0'}; (the whole line is repeated 5 times separated by '?'. the numbers are repeated 5 times.)

bool MatchPattern(char* target, char* pattern, char wildcard){ //pattern: ..#.##.###...###. target: .?#??#??#?.???##? wildcard: '?' -> true
    size_t len = strlen(target);
    for(int i = 0; i < len; i++){
        if(pattern[i] == wildcard) continue;
        if(pattern[i] != target[i]) return false;
    }
    return true;
} //returns true if target matches pattern, where wildcard is '?'

char* NumbersFromString(char *string){ //string: ..#.##.###...###. ret: {1, 2, 3, 3, '\0'} (number of #s between .s)
    int j = 0;
    int count = 0;
    char *ret = (char*)malloc(MAXNUM * sizeof(char));
    for(int i = 0; string[i] != '\0'; i++){
        if (string[i] == '#'){
            count++;
        } else if (string[i] == '.'){
            if(count > 0){
                ret[j] = count;
                j++;
                count = 0;
            }
        }
    }
    if(count > 0){
        ret[j] = count;
        j++;
    }
    ret[j] = '\0';
    return ret;
}

int PossibleVariatons(Line *line){
    //generate all possible layouts that are the same length and check if they match the given numbers and the given pattern.
    //only generate layouts that only differ in the wildcard positions.
    //if they do, increment the counter
    //return the counter

    //bit pattern for keeping track of permutations
    //1 = #, 0 = .
    //the first bit is the leftmost char
    //the last bit is the rightmost char
    //the number of bits is the length of the line
    //the number of permutations is 2^len
    //the number of permutations is the number of possible layouts
    //the number of possible layouts is the number of possible layouts that match the given numbers and the given pattern

    __uint128_t var = 0ULL;
    char generated[line->len + 1];
    char *numbers;
    int count = 0;
    int i = 0;
    __uint128_t limit = 1ULL << line->len;
    while(var < limit){
        //generate layout
        for(int j = 0; j < line->len; j++){
            if(var & (1 << j)){
                generated[j] = '#';
            } else {
                generated[j] = '.';
            }
        }
        generated[line->len] = '\0';
        //check if it matches the given numbers
        numbers = NumbersFromString(generated);
        //printf("%s ", generated);
        //printnumbers(numbers);
        if(MatchNumbers(numbers, line->numbers)){
            //check if it matches the given pattern
            if(MatchPattern(generated, line->line, '?')){
                count++;
            }
        }
        free(numbers);
        var++;
    }
    return count;
}

int PossibleVariatons2(Line *line){
    __uint128_t var = 0ULL;
    char *generated;
    char *numbers;
    int count = 0;
    int i = 0;
    __uint128_t limit = 1ULL << line->len;
    while(var < limit){
        //generate layout
        generated = Merge(line, wildcardmask(line), var);
        //check if it matches the given numbers
        numbers = NumbersFromString(generated);
        printf("%s ", generated);
        printnumbers(numbers);
        if(MatchNumbers(numbers, line->numbers)){
            //check if it matches the given pattern
            if(MatchPattern(generated, line->line, '?')){
                count++;
            }
        }
        free(numbers);
        var++;
    }
    return count;
}

int main(){
    FILE *fp;
    fp = fopen("sample12.txt", "r");
    if(fp == NULL){
        perror("Error opening file");
        return(-1);
    }

    char line[64];
    int sum = 0;
    while(fgets(line, 64, fp) != NULL){
        Line parsed, unfolded;
        ParseLine(line, &parsed);
        unfolded = UnfoldLine(&parsed);
        printf("generating layouts for: %s ", unfolded.line);
        sum += PossibleVariatons2(&unfolded);
        printf("%s ", unfolded.line);
        printnumbers(unfolded.numbers);
    }

    printf("The sum is: %d\n", sum);
    

    fclose(fp);
    return 0;
}