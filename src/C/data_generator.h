#include "random_generator.h" // also includes all the other necessary libraries
#include "quick_sort.h"

#define BUFFER_SIZE 64

void print_list(int* list, int length) {
    for (int i=0; i<length; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int create_data(int amount) {
    clock_t start, end;
    double cpu_time_used;


    int counter=0, number;
    int unsorted_list[amount];


    if (generate_list_file(-10000, 10000, amount) != 0) {
        return -1;
    }

    char buffer[BUFFER_SIZE];
    FILE* file = fopen("../tmp/list.txt", "r");

    if (file == NULL) {
        printf("[-] data_generator.h/create_data() - list.txt could not be opened/read.\n");
        return -1;
    }
    
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        if (sscanf(buffer, "%d", &number) == 1) {
            unsorted_list[counter] = number;
            counter++;
        } else {
            printf("[-] Error: Non-integer character detected.\n");
            return -2;
        }
    }
    fclose(file);


    start = clock();

    quick_sort(unsorted_list, 0, amount, amount);   

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    file = fopen("../data/time_complexity.data", "a");

    if (file == NULL) {
        printf("[-] data_generator.h/create_data() - time_complexity.data could not be opened.\n");
        return -1;
    }

    fprintf(file, "%d,%f\n", amount, cpu_time_used);

    fclose(file);

    return 0;
}

int remove_data() {
    if (remove("../data/time_complexity.data") == 0) {
        return 0;
    }
    printf("[-] data_generator.h/remove_data() - time_complexity.data could not be deleted.\n");
    printf("[*] data_generator.h/remove_data() - Attempting fix. Creating time_complexity.data.\n");

    FILE* file = fopen("../data/time_complexity.data", "w");
    if (file != NULL) {
        printf("[+] data_generator.h/remove_data() - time_complexity.data successfuly created.\n");
        fclose(file);
        return 0;
    }
    fclose(file);
    printf("[-] data_generator.h/remove_data() - time_complexity.data could not be created.\n");

    return -1;
}