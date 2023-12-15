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

typedef struct NodePointer {
    Node *node;
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
    
    //build linked list of nodes whiches name ends with A
    //we will be advancing every node (struct member) in this list until we reach a point where every node in the list ends with Z.
    NodePointer *starters = NULL;

    while(fgets(line, 18, fp) != NULL){
        nodes[index] = ParseNode(line);
        if(nodes[index].name[2] == 'A' ){
            Insert(&starters, &nodes[index]);
            printf("Added %s to starters\n", nodes[index].name);
        }
        index++;
    }

    size_t steps = 0;
    bool cont = true;
    while(cont && steps < 9999999){
        cont = false;
        char dir = direction(instructions, len-1, steps);
        steps++;
        printf("Step %d: %c\n", steps, dir);
        if(dir == 'L'){
            for(NodePointer *current = starters; current != NULL; current = current->next){
                printf("Moved from %s to %s\n", current->node->name, current->node->left);
                current->node = lookup(current->node->left, nodes, nodecount);
                if(current->node->name[2] != 'Z'){
                    cont = true;
                }
            }
            
        } else if (dir == 'R'){
            for(NodePointer *current = starters; current != NULL; current = current->next){
                printf("Moved from %s to %s\n", current->node->name, current->node->right);
                current->node = lookup(current->node->right, nodes, nodecount);
                if(current->node->name[2] != 'Z'){
                    cont = true;
                }
            }
        }
    }

    printf("Steps required: %d\n", steps);
    
    fclose(fp);
    return 0;
}