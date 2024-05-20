#include "data_generator.h"

int main(int argc, char** argv) {

    if (argc != 5) {
        printf("Usage: ./generate_data <sorting alg.> <from which amount> <up to which amount> <(y|n) y - delete existing data>\n");
        return 1;
    }

    char* data_path = (char*) malloc(100 * sizeof(char));
    int sorter;
    if (strcmp(argv[1], "bubble_sort") == 0) {
        strcpy(data_path, "../data/bubble_sort_data/average_time.data");
        sorter = 0;

    } else if (strcmp(argv[1], "merge_sort") == 0) {
        strcpy(data_path, "../data/merge_sort_data/average_time.data");
        sorter = 1;

    } else {
        printf("[-] Error. Invalid sorting method.\n");
        printf("[*] Available sorting methods:\n");
        printf("[*] bubble_sort\n");
        printf("[*] merge_sort\n");
        return 1;
    }


    if (strcmp(argv[4], "y") == 0) {
        printf("[*] generate_data/main() - Deleting average_time.data ...\n");
        remove_data(data_path);
    }

    int from = atoi(argv[2]);
    int upTo = atoi(argv[3]);
    int checkError;

    if (from < 2) {
        printf("generate_data.c/main() - Invalid argument <from>\n");
        return -1;
    }
    if (upTo <= from) {
        printf("generate_data.c/main() - Invalid argument <upTo>\n");
        return -1;
    }

    printf("[*] Generating data...\n");

    for (int i=from; i<upTo; i++) {
        checkError = create_data(i, data_path, sorter);

        if (checkError != 0) {  // undefined error on opening the list.txt
            printf("[-] generate_data.c/main() - Undefined error occured\n");
            return -1;  // data remains non-corrupted, re start the program with its corresponding last input.
        }
    }

    free(data_path);

    return 0;
}