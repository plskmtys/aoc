#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <unistd.h>
#include "advent.h"

//functions
typedef struct {
    char name[4];
    char left[4];
    char right[4];
} Node;

typedef struct NodePointer {
    Node *node;
    int steps;
    struct NodePointer *next;
} NodePointer;

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

void Insert(NodePointer **list, Node *node){
    NodePointer *newNode = (NodePointer*)malloc(sizeof(NodePointer));
    newNode->node = node;
    newNode->next = NULL;
    if(*list == NULL){
        *list = newNode;
    }else{
        NodePointer *current = *list;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
}

int LCM(int a, int b){
    int max = a > b ? a : b;
    int min = a < b ? a : b;
    int i = 1;
    while((max * i) % min != 0){
        i++;
    }
    return max * i;
}

int main(){
    FILE *fp;
    fp = fopen("input8-2.txt", "r");
    
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
    
    //build linked list of nodes whiches name ends with A
    //we will be advancing every node (struct member) in this list until we reach a point where every node in the list ends with Z.
    NodePointer *starters = NULL;

    while(fgets(line, 18, fp) != NULL){
        nodes[index] = ParseNode(line);
        if(nodes[index].name[2] == 'A' && strcmp(nodes[index].name, "VMA") == 0){
            Insert(&starters, &nodes[index]);
            printf("Added %s to starters\n", nodes[index].name);
        }
        index++;
    }

    size_t steps = 0;
    for(NodePointer *current = starters; current != NULL; current = current->next){
        printf("Starting with %s\n", current->node->name);
        while(current->node->name[2] != 'Z'){
            if(direction(instructions, len, current->steps) == 'R'){
                current->node = lookup(current->node->right, nodes, nodecount);
            }else{
                current->node = lookup(current->node->left, nodes, nodecount);
            }
            printf("next direction: %c\n", direction(instructions, len, current->steps));
            printf("current: %s\n", current->node->name);
            sleep(1);

            current->steps++;
        }
        printf("Finished with %s\n", current->node->name);
    }

    //find the least common multiple of all the steps
    int lcm = 1;
    for(NodePointer *current = starters; current != NULL; current = current->next){
        lcm = LCM(lcm, current->steps);
    }
    printf("LCM: %d\n", lcm);

    printf("Steps required: %d\n", lcm);
    
    fclose(fp);
    return 0;
}