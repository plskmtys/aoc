#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include "advent.h"

//functions
typedef struct {
    char name[4];
    char left[4];
    char right[4];
} Node;

char direction(char *list, size_t len, size_t index){
    return list[index%len];
}

Node *lookup(char needle[4], Node* list, size_t length){
    for(size_t i = 0; i < length ; i++){
        if(strcmp(needle, list[i].name) == 0){

            return &list[i];
        }
    }
    return NULL;
}

Node ParseNode(char line[18]){
    Node ret;
    sscanf(line, "%3s = (%3s, %3s)", ret.name, ret.left, ret.right);
    return ret;
}

int main(){
    FILE *fp;
    fp = fopen("input8.txt", "r");
    
    char instructions[300];
    instructions[0] = '\0';
    fgets(instructions, 300, fp);
    size_t len = strlen(instructions);
    char line[18];
    size_t nodecount = 766;
    Node nodes[nodecount];
    
    size_t index = 0;
    //skip empty line when reading
    fgets(line, 18, fp);
    while(fgets(line, 18, fp) != NULL){
        //string feldolgozása
        nodes[index] = ParseNode(line);
        index++;
    }

    char startsequence[4] = "AAA";
    char endsequence[4] = "ZZZ";
    size_t steps = 0;
    Node *start = lookup(startsequence, nodes, nodecount);
    Node *end = lookup(endsequence, nodes, nodecount);
    Node *current = start;
    while(current != end){
        printf("current: %s\n", current->name);
        char dir = direction(instructions, len-1, steps);
        printf("next direction: %c\n", dir);
        steps++;
        if(dir == 'L'){
            printf("left: %s\n", current->left);
            current = lookup(current->left, nodes, nodecount);
        }else if(dir == 'R'){
            printf("right: %s\n", current->right);
            current = lookup(current->right, nodes, nodecount);
        }
    }

    printf("Steps required from AAA to ZZZ: %d\n", steps);
    
    fclose(fp);
    return 0;
}
