#include "data_generator.h"

int main(int argc, char** argv) {

    if (argc != 5) {
        printf("Usage: ./generate_data <sorting alg.> <from which amount> <up to which amount> <(y|n) y - delete existing data>\n");
        return 1;
    }

    char* path = (char*) malloc(100 * sizeof(char));
    if (strcmp(argv[1], "bubble_sort") == 0) {
        strcpy(path, "../data/bubble_sort_data/average_time.data");

    } else if (strcmp(argv[1], "merge_sort" == 0)) {
        strcpy(path, "../data/merge_sort_data/average_time.data");

    } else {
        printf("[-] Error. Invalid sorting method.\n");
        printf("[*] Available sorting methods:\n");
        printf("[*] bubble_sort\n");
        printf("[*] merge_sort\n");
        return 1;
    }


    if (strcmp(argv[4], "y") == 0) {
        printf("[*] generate_data/main() - Deleting average_time.data ...\n");
        remove_data(path);
    }

    int from = atoi(argv[1]);
    int upTo = atoi(argv[2]);
    int checkError;

    for (int i=from+1; i<upTo; i++) {
        checkError = create_data(i, path);
        if (checkError != 0) {  // undefined error on opening the list.txt
            return -1;  // data remains non-corrupted, re start the program with its corresponding last input.
        }
    }

    free(path);

    return 0;
}