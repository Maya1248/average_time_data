#include "random_generator.h"

#define BUFFER_SIZE 64

void print_list(int* list, int length) {
    for (int i=0; i<length; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

void shift_swap(int* list, int low, int high) {
    int tmp = list[high];

    for (int i=high; i>low; i--) {
        list[i] = list[i-1];
    }
    list[low] = tmp;
}

void quick_sort(int* list, int low, int high, int length) {
    int pivot_index = low;

    // if only 1 element is left; OR if only 2 elements are left, they are sured to be already sorted from previous iteration
    if (high - low == 0 || high - low == 1) return;

    for (int i=low; i<high; i++) {
        if (list[pivot_index] > list[i]) {
            shift_swap(list, pivot_index, i);
            pivot_index++;
        }
    }
    
    //print_list(list,length);
    quick_sort(list, low, pivot_index, length);  // left of pivot
    quick_sort(list, pivot_index+1, high, length); // right of pivot
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
        printf("[-] quick_sort.h/create_data() - list.txt could not be opened/read.\n");
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
        printf("[-] quick_sort.h/create_data() - time_complexity.data could not be opened.\n");
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
    printf("[-] quick_sort.h/remove_data() - time_complexity.data could not be deleted.\n");
    return -1;
}