#include "random_generator.h" // also includes all the other necessary libraries
//#include "quick_sort.h"
#include "bubble_sort.h"
#include "merge_sort.h"

#define BUFFER_SIZE 64

int create_data(int amount, char* path, int sorter) {
    clock_t start, end;
    double cpu_time_used;

    int counter=0, number;
    int* unsorted_list = (int*) malloc(amount * sizeof(int));
    int* sorted_list; // necessary so we can free both the unsorted list and the sorted list that is returned. fixes memory leak...

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
            *(unsorted_list+counter) = number;
            counter++;
        } else {
            printf("[-] Error: Non-integer character detected.\n");
            return -2;
        }
    }
    fclose(file);

    int returned_void = 0;
    start = clock();

    if (sorter == 0) {
        bubble_sort(unsorted_list, amount);  // returns void...
        sorted_list = unsorted_list;
        returned_void = 1;
    } else if (sorter == 1) {
        sorted_list = merge_sort(unsorted_list, amount);  // returns a sorted list.
    }
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    if (check_if_sorted(sorted_list, amount) != 0) {
        return 1;
    }
    
    file = fopen(path, "a");
    if (file == NULL) {
        printf("[-] data_generator.h/create_data() - Unable to open average_time.data\n");
        printf("[*] data_generator.h/create_data() - Attempting quick fix\n");
        
        file = fopen(path, "w");
        if (file == NULL) {
            printf("[-] data_generator.h/create_data() - Unable to create the file...\n");
            return -1;
        }

        return -1;
    }

    fprintf(file, "%d,%f\n", amount, cpu_time_used);
    fclose(file);

    if (unsorted_list == sorted_list) { // if no merged lists are created because the unsorted list is extremely small, size of 2 or so... this condition flips. to evade double free();
        free(sorted_list);
        return 0;
    } else {
        free(unsorted_list);
        free(sorted_list);
    }

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