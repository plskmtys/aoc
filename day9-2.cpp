#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>

int PrevDigitOfPattern(int pattern[], size_t length){
    int difflist[length-1];
    bool allzero = true;
    for(int i = 0; i < length-1; i++){
        difflist[i] = pattern[i+1] - pattern[i];
        if(difflist[i] != 0){
            allzero = false;
        }
    }
    if(allzero){
        return pattern[0];
    } else {
        return pattern[0] - PrevDigitOfPattern(difflist, length-1);
    }
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

void getnums(char *line, int *list, size_t size){
    char buffer[10];
    buffer[0] = '\0';
    int listindex = 0;
    int bufferindex = 0;

    while(*line != '\0'){
        if(*line == ' '){
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

int main(){
    FILE *fp;
    fp = fopen("input9.txt", "r");
    int pattern[21];
    char line[128];
    int sum = 0;
    while(fgets(line, 128, fp) != NULL){
        getnums(line, pattern, 21);
        sum += PrevDigitOfPattern(pattern, 21);
    }

    printf("The sum is: %d\n", sum);
    
    fclose(fp);
    return 0;
}