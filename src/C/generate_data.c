#include "quick_sort.h"

int main(int argc, char** argv) {

    if (argc != 4) {
        printf("Usage: ./generate_data <from which amount> <up to which amount> <(y|n) y - delete existing data>\n");
        return 1;
    }

    if (strcmp(argv[3], "y") == 0) {
        printf("[*] generate_data/main() - Deleting time_complexity.data ...\n");
        remove_data();
    }

    int from = atoi(argv[1]);
    int upTo = atoi(argv[2]);
    int checkError;

    for (int i=from+1; i<upTo; i++) {
        checkError = create_data(i);
        if (checkError != 0) {  // undefined error on opening the list.txt
            return -1;  // time complexity data remains non-corrupted, re start the program with its corresponding last input.
        }
    }

    return 0;
}