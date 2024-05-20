#include "random_generator.h" // also includes all the other necessary libraries
//#include "quick_sort.h"
//#include "bubble_sort.h"
#include "merge_sort.h"

#define BUFFER_SIZE 64

void print_list(int* list, int length) {
    for (int i=0; i<length; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int create_data(int amount, char* path) {
    clock_t start, end;
    double cpu_time_used;

    int counter=0, number;
    //int unsorted_list[amount];
    int* unsorted_list = (int*) malloc(amount * sizeof(int));

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

    //quick_sort(unsorted_list, 0, amount, amount);   
    //bubble_sort(unsorted_list, amount);
    unsorted_list = merge_sort(unsorted_list, amount);  // returns a sorted list.

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    file = fopen(path, "a");

    if (file == NULL) {
        printf("[-] data_generator.h/create_data() - average_time.data could not be opened.\n");
        printf("[*] data_generator.h/create_data() - Attempting fix. Creating average_time.data\n");
        
        file = fopen(path, "w");
        if (file == NULL) {
            printf("[-] data_generator.h/create_data() - Fix failed. Could not create average_time.data\n");
            return -1;
        }
    }

    fprintf(file, "%d,%f\n", amount, cpu_time_used);

    fclose(file);
    free(unsorted_list);

    return 0;
}

int remove_data(char* path) {
    if (remove(path) == 0) {
        return 0;
    }
    printf("[-] data_generator.h/remove_data() - average_time.data could not be deleted.\n");
    printf("[*] data_generator.h/remove_data() - Attempting fix. Creating average_time.data.\n");

    FILE* file = fopen(path, "w");
    if (file != NULL) {
        printf("[+] data_generator.h/remove_data() - average_time.data successfuly created.\n");
        fclose(file);
        return 0;
    }
    
    printf("[-] data_generator.h/remove_data() - average_time.data could not be created.\n");

    return -1;
}