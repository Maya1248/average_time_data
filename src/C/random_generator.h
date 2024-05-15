#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int generate_number(int low, int high) {
    time_t seconds;
    time(&seconds);
    srand((unsigned) seconds);

    return (rand() % (high - low + 1)) + low;
}

int generate_list_file(int low, int high, int amount) {
    FILE* file = fopen("../tmp/list.txt", "w");
    if (file == NULL) {
        printf("[-] random_generator.h/generate_list_file() - list.txt could not be created/opened.\n");
        return -1;
    }

    for (int i=0; i<amount; i++) {
        fprintf(file, "%d\n", generate_number(low, high));
    }
    fclose(file);

    return 0;
}