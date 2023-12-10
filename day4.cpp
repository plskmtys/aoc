#include <stdlib.h>
#include <iostream>

u_int8_t matches(unsigned int arr1[10], unsigned int arr2[25]){
    u_int8_t m = 0;
    for(u_int8_t i = 0; i < 10; i++){
        for (u_int8_t j = 0; j < 25; j++){
            if(arr1[i] == arr2[j]) m += 1;
        }
    }
    return m;
}

unsigned int power(unsigned int base, unsigned int exp){

    if (exp == 0)
        return 1;
    int temp = power(base, exp/2);
    if (exp%2 == 0)
        return temp*temp;
    else
        return base*temp*temp;
}

int main(){
    FILE *fp = fopen("input4.txt", "r");
    unsigned int winners[10];
    unsigned int tips[25];
    unsigned int sum = 0;
    unsigned int card = 0;
    unsigned int m = 0;

    size_t size = 120;
    char *line = (char*) malloc(sizeof(char)*size);
    line[0] = '\0';

    unsigned int i = 0;
    while(getline(&line, &size, fp) && i<194){
        printf("reading line %u\n", i++);
        sscanf(line, "Card%*[^ ] %u:%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] |%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u%*[^ ] %u\n", &card, winners[0], winners[1],winners[2],winners[3],winners[4],winners[5],winners[6],winners[7],winners[8],winners[9], tips[0], tips[1], tips[2], tips[3], tips[4], tips[5], tips[6], tips[7], tips[8], tips[9], tips[10], tips[11], tips[12], tips[13], tips[14], tips[15], tips[16], tips[17], tips[18], tips[19], tips[20], tips[21], tips[22], tips[23], tips[24]);
        m = matches(winners, tips);
        sum += m*(1<<(m-1));
        std::cout << sum << std::endl;
    }
    printf("the sum is: %u", sum);
}